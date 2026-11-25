param(
    [Parameter(Mandatory = $true)][ValidateSet('launch', 'inject', 'shot', 'kill', 'status', 'key', 'focus', 'post', 'click', 'boot', 'dismiss', 'hold')][string]$Action,
    [string]$Out = '',
    [string]$Keys = '',
    [string]$ExtraArgs = '',
    [int]$TargetPid = 0,
    [string]$Dll = '',
    [int]$Instance = 1,
    [switch]$NoNative,
    [string]$Url = ''
)
$ErrorActionPreference = 'Stop'
$gameWin64 = 'D:\SteamLibrary\steamapps\common\Bleeding Edge\Moblade\Binaries\Win64'
$exe = Join-Path $gameWin64 'MobladeClient-Win64-Shipping.exe'
# Instance 2+ runs through a hard link with a different exe name (the game kills same-named duplicates).
$procName = if ($Instance -eq 1) { 'MobladeClient-Win64-Shipping' } else { "BEInstance$Instance-Win64-Shipping" }
$runExe = Join-Path $gameWin64 "$procName.exe"
$ue4ssDir = if ($Instance -eq 1) { Join-Path $PSScriptRoot 'ue4ss' } else { Join-Path $PSScriptRoot "ue4ss$Instance" }
$dll = if ($Dll) { $Dll } else { Join-Path $ue4ssDir 'UE4SS.dll' }
$nativeDll = Join-Path $PSScriptRoot '..\..\build\be1v1.dll'
if (-not $Out) { $Out = Join-Path $ue4ssDir 'shot.png' }

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
  [DllImport("user32.dll", CharSet=CharSet.Unicode)] static extern int GetWindowText(IntPtr h, StringBuilder s, int n);
  [DllImport("user32.dll")] static extern bool EnumChildWindows(IntPtr p, EnumProc f, IntPtr l);
  [DllImport("user32.dll")] static extern int GetDlgCtrlID(IntPtr h);
  // Presses the default/OK button of any message-box dialog owned by the process (no focus change). Returns a description.
  public static string DismissDialogs(int pid) {
    var outp = new StringBuilder();
    EnumWindows((h, l) => { uint p; GetWindowThreadProcessId(h, out p); var cls = new StringBuilder(64); GetClassName(h, cls, 64);
      if (p == (uint)pid && IsWindowVisible(h) && cls.ToString() == "#32770") {
        var title = new StringBuilder(256); GetWindowText(h, title, 256);
        var text = new StringBuilder(); IntPtr btn = IntPtr.Zero; int btnId = 1;
        EnumChildWindows(h, (c, l2) => { var cc = new StringBuilder(64); GetClassName(c, cc, 64); var t = new StringBuilder(512); GetWindowText(c, t, 512);
          if (cc.ToString() == "Static") text.Append(t.ToString()).Append(' ');
          if (cc.ToString() == "Button" && btn == IntPtr.Zero) { btn = c; btnId = GetDlgCtrlID(c); }
          return true; }, IntPtr.Zero);
        PostMessage(h, 0x0111, (IntPtr)(btnId & 0xFFFF), btn);   // WM_COMMAND(BN_CLICKED) from the first button
        outp.Append("dismissed dialog '" + title + "': " + text.ToString().Trim() + "\n");
      }
      return true; }, IntPtr.Zero);
    return outp.ToString();
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
function Get-Game { if ($TargetPid) { Get-Process -Id $TargetPid -ErrorAction SilentlyContinue } else { Get-Process -Name $procName -ErrorAction SilentlyContinue } }
function Focus-Game { $p = Get-Game | Select-Object -First 1; if ($p -and $p.MainWindowHandle -ne 0) { [W32]::ShowWindow($p.MainWindowHandle, 9) | Out-Null; [W32]::SetForegroundWindow($p.MainWindowHandle) | Out-Null } }
function Inject-Dll([string]$path) {
    $p = Get-Game | Select-Object -First 1
    if (-not $p) { throw 'Game not running' }
    $leaf = Split-Path $path -Leaf
    if ($p.Modules | Where-Object { $_.ModuleName -eq $leaf }) { return "already has $leaf" }
    $h = [W32]::OpenProcess(0x1F0FFF, $false, $p.Id)
    $bytes = [Text.Encoding]::Unicode.GetBytes([IO.Path]::GetFullPath($path) + "`0")
    $mem = [W32]::VirtualAllocEx($h, [IntPtr]::Zero, [UIntPtr][uint64]$bytes.Length, 0x3000, 0x04)
    $w = [UIntPtr]::Zero
    [W32]::WriteProcessMemory($h, $mem, $bytes, [UIntPtr][uint64]$bytes.Length, [ref]$w) | Out-Null
    $ll = [W32]::GetProcAddress([W32]::GetModuleHandle('kernel32.dll'), 'LoadLibraryW')
    $tid = 0
    $t = [W32]::CreateRemoteThread($h, [IntPtr]::Zero, [UIntPtr]::Zero, $ll, $mem, 0, [ref]$tid)
    [W32]::WaitForSingleObject($t, 60000) | Out-Null
    $code = 0; [W32]::GetExitCodeThread($t, [ref]$code) | Out-Null
    "injected $leaf pid=$($p.Id) loadlibrary=0x{0:X}" -f $code
}
function Dismiss($p) { $r = [GameWin]::DismissDialogs($p.Id); if ($r) { Write-Output $r.Trim(); Add-Content (Join-Path $PSScriptRoot 'dialogs.log') "$(Get-Date -Format s) inst$Instance $($r.Trim())" } }
function Start-Game {
    if (Get-Game) { throw "Instance $Instance already running" }
    if ($Instance -ne 1) {
        if (-not (Test-Path $runExe)) { New-Item -ItemType HardLink -Path $runExe -Target $exe | Out-Null }
        if (-not (Test-Path (Join-Path $ue4ssDir 'UE4SS.dll'))) {
            New-Item -ItemType Directory -Force $ue4ssDir | Out-Null
            foreach ($f in 'UE4SS.dll', 'UE4SS-settings.ini', 'MemberVariableLayout.ini') { Copy-Item -Force (Join-Path $PSScriptRoot "ue4ss\$f") $ue4ssDir }
            Copy-Item -Recurse -Force (Join-Path $PSScriptRoot 'ue4ss\Mods') $ue4ssDir
            Copy-Item -Recurse -Force (Join-Path $PSScriptRoot 'ue4ss\UE4SS_Signatures') $ue4ssDir
        }
        # Always resync the probe script, pointing it at this instance's folder.
        $src = [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'ue4ss\Mods\BEProbe\Scripts\main.lua'))
        [IO.File]::WriteAllText((Join-Path $ue4ssDir 'Mods\BEProbe\Scripts\main.lua'), $src.Replace('tools\harness\ue4ss\]]', "tools\harness\ue4ss$Instance\]]"))
    }
    $a = "-windowed -ResX=960 -ResY=540 $ExtraArgs"
    if ($NoNative) {
        $p = Start-Process -FilePath $runExe -ArgumentList $a -WorkingDirectory $gameWin64 -PassThru
        "launched instance $Instance pid=$($p.Id)"
    } else {
        # The dev launcher loads a fresh copy of be1v1.dll before the game's entry point (logs: build\run\be1v1-<pid>.log).
        $runDir = Join-Path $PSScriptRoot '..\..\build\run'; New-Item -ItemType Directory -Force $runDir | Out-Null
        $copy = Join-Path $runDir ("be1v1_{0}.dll" -f (Get-Date -Format 'HHmmssfff'))
        Copy-Item $nativeDll $copy
        $launcher = Join-Path $PSScriptRoot '..\..\build\devlaunch.exe'
        $gpid = & $launcher $runExe $copy @(@($Url) | Where-Object { $_ }) -windowed -ResX=960 -ResY=540 @($ExtraArgs -split ' ' | Where-Object { $_ })
        "launched instance $Instance pid=$gpid (native)"
    }
}

switch ($Action) {
    'launch' { Start-Game }
    'inject' { Inject-Dll $dll }
    'boot' {
        # launch, wait for the window, inject native DLL + UE4SS probe, wait for the probe to report in.
        Start-Game
        $deadline = (Get-Date).AddSeconds(120)
        do { Start-Sleep -Milliseconds 500; $p = Get-Game | Select-Object -First 1; if ($p) { Dismiss $p } } while ((-not $p -or [GameWin]::Find($p.Id) -eq [IntPtr]::Zero) -and (Get-Date) -lt $deadline)
        for ($i = 0; $i -lt 8; $i++) { Start-Sleep -Milliseconds 500; Dismiss $p }
        $log = Join-Path $ue4ssDir 'probe.log'
        Remove-Item $log -ErrorAction SilentlyContinue
        Inject-Dll $dll
        do { Start-Sleep -Milliseconds 500; Dismiss $p } while (-not ((Test-Path $log) -and (Select-String -Path $log -Pattern 'BEProbe loaded' -Quiet)) -and (Get-Date) -lt $deadline)
        for ($i = 0; $i -lt 10; $i++) { Start-Sleep -Milliseconds 500; Dismiss $p }
        if ((Get-Date) -ge $deadline) { throw 'boot timed out' }
        "ready"
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
        $small = New-Object System.Drawing.Bitmap $bmp, ([int]($w * 0.7)), ([int]($h * 0.7))
        $small.Save($Out, [System.Drawing.Imaging.ImageFormat]::Png)
        "saved $Out ($w x $h)"
    }
    'focus' { Focus-Game; 'focused' }
    'hold' {
        # -Keys "57,1500" holds a virtual key (hex) for N milliseconds via posted key-repeat messages
        $p = Get-Game | Select-Object -First 1
        $hwnd = [GameWin]::Find($p.Id)
        $vk = [Convert]::ToUInt32(($Keys -split ',')[0], 16); $ms = [int](($Keys -split ',')[1])
        $sc = [GameWin]::MapVirtualKey($vk, 0)
        $end = (Get-Date).AddMilliseconds($ms)
        while ((Get-Date) -lt $end) { [GameWin]::PostMessage($hwnd, 0x0100, [IntPtr]$vk, [IntPtr](1 -bor ($sc -shl 16))) | Out-Null; Start-Sleep -Milliseconds 40 }
        [GameWin]::PostMessage($hwnd, 0x0101, [IntPtr]$vk, [IntPtr](1 -bor ($sc -shl 16) -bor (1 -shl 30) -bor (1 -shl 31))) | Out-Null
        "held $Keys"
    }
    'dismiss' { $p = Get-Game | Select-Object -First 1; if ($p) { Dismiss $p }; 'checked' }
    'click' {
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
    'kill' {
        Get-Game | Stop-Process -Force
        if ($Instance -ne 1) { Start-Sleep 2; Remove-Item -Force $runExe -ErrorAction SilentlyContinue }
        'killed'
    }
    'status' {
        $p = Get-Game
        if (-not $p) { 'not running'; break }
        foreach ($x in $p) { "pid=$($x.Id) title='$($x.MainWindowTitle)' ws=$([int]($x.WorkingSet64/1MB))MB resp=$($x.Responding)"; ($x.Modules | Where-Object { $_.ModuleName -match 'UE4SS|be1v1' } | ForEach-Object ModuleName) -join ',' }
    }
}
