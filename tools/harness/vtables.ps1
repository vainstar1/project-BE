param([string]$AddrFile = "$PSScriptRoot\ue4ss\cdo_addrs.txt", [int]$Slots = 160, [string]$Out = "$PSScriptRoot\ue4ss\vtables.json")
Add-Type @'
using System; using System.Runtime.InteropServices;
public static class Mem {
  [DllImport("kernel32.dll")] public static extern IntPtr OpenProcess(uint a, bool i, int p);
  [DllImport("kernel32.dll")] public static extern bool ReadProcessMemory(IntPtr h, IntPtr a, byte[] b, IntPtr n, out IntPtr r);
  public static ulong Q(IntPtr h, ulong a) { var b = new byte[8]; IntPtr r; ReadProcessMemory(h, (IntPtr)(long)a, b, (IntPtr)8, out r); return BitConverter.ToUInt64(b, 0); }
}
'@
$p = Get-Process -Name 'MobladeClient-Win64-Shipping' | Select-Object -First 1
$m = $p.MainModule; $base = [uint64]$m.BaseAddress.ToInt64(); $end = $base + [uint64]$m.ModuleMemorySize
$h = [Mem]::OpenProcess(0x0010, $false, $p.Id)
$result = [ordered]@{ base = ('0x{0:X}' -f $base); objects = [ordered]@{} }
foreach ($line in Get-Content $AddrFile) {
    if ($line -notmatch 'ADDR (\S+) (0x[0-9A-F]+)') { continue }
    $name = $Matches[1]; $addr = [Convert]::ToUInt64($Matches[2].Substring(2), 16)
    $vt = [Mem]::Q($h, $addr)
    $entries = @()
    for ($i = 0; $i -lt $Slots; $i++) {
        $e = [Mem]::Q($h, $vt + [uint64](8 * $i))
        if ($e -lt $base -or $e -ge $end) { break }
        $entries += ('0x{0:X}' -f ($e - $base + 0x140000000))
    }
    $result.objects[$name] = [ordered]@{ vtable = ('0x{0:X}' -f ($vt - $base + 0x140000000)); entries = $entries }
}
$result | ConvertTo-Json -Depth 5 | Set-Content -Encoding utf8 $Out
"wrote $Out"
