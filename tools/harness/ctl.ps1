param(
    [Parameter(Mandatory = $true)][ValidateSet('launch', 'inject', 'shot', 'kill', 'status', 'key', 'focus', 'post', 'click')][string]$Action,
    [string]$Out = "$PSScriptRoot\ue4ss\shot.png",
    [string]$Keys = '',
    [string]$ExtraArgs = '',
    [int]$TargetPid = 0,
    [string]$Dll = ''
)
$ErrorActionPreference = 'Stop'
$gameWin64 = 'D:\SteamLibrary\steamapps\common\Bleeding Edge\Moblade\Binaries\Win64'
$exe = Join-Path $gameWin64 'MobladeClient-Win64-Shipping.exe'
$dll = if ($Dll) { $Dll } else { Join-Path $PSScriptRoot 'ue4ss\UE4SS.dll' }

Add-Type -AssemblyName System.Windows.Forms, System.Drawing
if (-not ('W32' -as [type])) {
    Add-Type @'
using System; using System.Runtime.InteropServices;
public static class W32 {
  [DllImport("user32.dll")] public static extern bool SetForegroundWindow(IntPtr h);
  [DllImport("user32.dll")] public static extern bool ShowWindow(IntPtr h, int c);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr OpenProcess(uint a, bool i, int p);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr VirtualAllocEx(IntPtr p, IntPtr a, UIntPtr s, uint t, uint pr);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern bool WriteProcessMemory(IntPtr p, IntPtr b, byte[] buf, UIntPtr s, out UIntPtr w);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] public static extern IntPtr GetModuleHandle(string m);
  [DllImport("kernel32.dll", CharSet=CharSet.Ansi)] public static extern IntPtr GetProcAddress(IntPtr m, string n);
  [DllImport("kernel32.dll", SetLastError=true)] public static extern IntPtr CreateRemoteThread(IntPtr p, IntPtr a, UIntPtr s, IntPtr st, IntPtr pa, uint f, out uint id);
  [DllImport("kernel32.dll")] public static extern uint WaitForSingleObject(IntPtr h, uint ms);
  [DllImport("kernel32.dll")] public static extern bool GetExitCodeThread(IntPtr h, out uint c);
}
'@
}
if (-not ('GameWin' -as [type])) {
    Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class GameWin {
  public struct RECT { public int Left, Top, Right, Bottom; }
  delegate bool EnumProc(IntPtr h, IntPtr l);
  [DllImport("user32.dll")] static extern bool EnumWindows(EnumProc f, IntPtr l);
  [DllImport("user32.dll")] static extern uint GetWindowThreadProcessId(IntPtr h, out uint pid);
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] static extern int GetClassName(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] static extern bool IsWindowVisible(IntPtr h);
  [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr h, out RECT r);
  [DllImport("user32.dll")] public static extern bool PrintWindow(IntPtr h, IntPtr dc, uint f);
  [DllImport("user32.dll")] public static extern bool PostMessage(IntPtr h, uint m, IntPtr w, IntPtr l);
  [DllImport("user32.dll")] public static extern uint MapVirtualKey(uint c, uint t);
  public static void Key(IntPtr h, uint vk) {
    uint sc = MapVirtualKey(vk, 0);
    PostMessage(h, 0x0100, (IntPtr)vk, (IntPtr)(1 | (sc << 16)));
    System.Threading.Thread.Sleep(60);
    PostMessage(h, 0x0101, (IntPtr)vk, (IntPtr)(1 | (sc << 16) | (1u << 30) | (1u << 31)));
  }
  public static IntPtr Find(int pid) {
    IntPtr found = IntPtr.Zero;
    EnumWindows((h, l) => { uint p; GetWindowThreadProcessId(h, out p); var sb = new StringBuilder(256); GetClassName(h, sb, 256);
      if (p == (uint)pid && IsWindowVisible(h) && sb.ToString() == "UnrealWindow") { found = h; return false; } return true; }, IntPtr.Zero);
    return found;
  }
}
'@
}
function Get-Game { if ($TargetPid) { Get-Process -Id $TargetPid -ErrorAction SilentlyContinue } else { Get-Process -Name 'MobladeClient-Win64-Shipping' -ErrorAction SilentlyContinue } }
function Focus-Game { $p = Get-Game | Select-Object -First 1; if ($p -and $p.MainWindowHandle -ne 0) { [W32]::ShowWindow($p.MainWindowHandle, 9) | Out-Null; [W32]::SetForegroundWindow($p.MainWindowHandle) | Out-Null } }

switch ($Action) {
    'launch' {
        if (Get-Game) { throw 'Game already running' }
        $a = @('-log', '-forcelogflush', '-windowed', '-ResX=1280', '-ResY=720') + ($ExtraArgs -split ' ' | Where-Object { $_ })
        $p = Start-Process -FilePath $exe -ArgumentList $a -WorkingDirectory $gameWin64 -PassThru
        "launched pid=$($p.Id)"
    }
    'inject' {
        $p = Get-Game | Select-Object -First 1
        if (-not $p) { throw 'Game not running' }
        $mods = $p.Modules | Where-Object { $_.ModuleName -match 'UE4SS|ReShade' }
        if ($mods) { throw "Already has: $($mods.ModuleName -join ',')" }
        $h = [W32]::OpenProcess(0x1F0FFF, $false, $p.Id)
        $bytes = [Text.Encoding]::Unicode.GetBytes($dll + "`0")
        $mem = [W32]::VirtualAllocEx($h, [IntPtr]::Zero, [UIntPtr][uint64]$bytes.Length, 0x3000, 0x04)
        $w = [UIntPtr]::Zero
        [W32]::WriteProcessMemory($h, $mem, $bytes, [UIntPtr][uint64]$bytes.Length, [ref]$w) | Out-Null
        $ll = [W32]::GetProcAddress([W32]::GetModuleHandle('kernel32.dll'), 'LoadLibraryW')
        $tid = 0
        $t = [W32]::CreateRemoteThread($h, [IntPtr]::Zero, [UIntPtr]::Zero, $ll, $mem, 0, [ref]$tid)
        [W32]::WaitForSingleObject($t, 60000) | Out-Null
        $code = 0; [W32]::GetExitCodeThread($t, [ref]$code) | Out-Null
        "injected pid=$($p.Id) loadlibrary=0x{0:X}" -f $code
    }
    'shot' {
        # Game window only (never the user's desktop).
        $p = Get-Game | Select-Object -First 1
        if (-not $p) { throw 'Game not running' }
        $hwnd = [GameWin]::Find($p.Id)
        $r = New-Object GameWin+RECT
        [GameWin]::GetWindowRect($hwnd, [ref]$r) | Out-Null
        $w = $r.Right - $r.Left; $h = $r.Bottom - $r.Top
        $bmp = New-Object System.Drawing.Bitmap $w, $h
        $g = [System.Drawing.Graphics]::FromImage($bmp)
        $hdc = $g.GetHdc(); [GameWin]::PrintWindow($hwnd, $hdc, 2) | Out-Null; $g.ReleaseHdc($hdc)
        $small = New-Object System.Drawing.Bitmap $bmp, ([int]($w * 0.6)), ([int]($h * 0.6))
        $small.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
        "saved $Out ($w x $h)"
    }
    'focus' { Focus-Game; 'focused' }
    'click' {
        # -Keys "x,y" in client pixels
        $p = Get-Game | Select-Object -First 1
        $hwnd = [GameWin]::Find($p.Id)
        $xy = $Keys -split ','; $l = [IntPtr](([int]$xy[1] -shl 16) -bor ([int]$xy[0] -band 0xFFFF))
        [GameWin]::PostMessage($hwnd, 0x0200, [IntPtr]0, $l) | Out-Null; Start-Sleep -Milliseconds 150
        [GameWin]::PostMessage($hwnd, 0x0201, [IntPtr]1, $l) | Out-Null; Start-Sleep -Milliseconds 100
        [GameWin]::PostMessage($hwnd, 0x0202, [IntPtr]0, $l) | Out-Null
        "clicked $Keys"
    }
    'post' {
        # -Keys is a comma list of virtual-key codes in hex, e.g. "0D" (Enter), "20" (Space)
        $p = Get-Game | Select-Object -First 1
        $hwnd = [GameWin]::Find($p.Id)
        foreach ($k in ($Keys -split ',')) { [GameWin]::Key($hwnd, [Convert]::ToUInt32($k, 16)); Start-Sleep -Milliseconds 400 }
        "posted $Keys"
    }
    'key' { Focus-Game; Start-Sleep -Milliseconds 300; [System.Windows.Forms.SendKeys]::SendWait($Keys); "sent $Keys" }
    'kill' { Get-Game | Stop-Process -Force; 'killed' }
    'status' {
        $p = Get-Game
        if (-not $p) { 'not running'; break }
        foreach ($x in $p) { "pid=$($x.Id) title='$($x.MainWindowTitle)' ws=$([int]($x.WorkingSet64/1MB))MB resp=$($x.Responding)"; ($x.Modules | Where-Object { $_.ModuleName -match 'UE4SS|ReShade|be_' } | ForEach-Object ModuleName) -join ',' }
    }
}
