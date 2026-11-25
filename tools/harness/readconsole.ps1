param([int]$ProcessId = (Get-Process -Name 'MobladeClient-Win64-Shipping' | Select-Object -First 1).Id, [int]$Lines = 300)
Add-Type @'
using System; using System.Runtime.InteropServices; using System.Text;
public static class ConRead {
  [DllImport("kernel32.dll")] static extern bool FreeConsole();
  [DllImport("kernel32.dll")] static extern bool AttachConsole(uint pid);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] static extern IntPtr CreateFile(string n, uint a, uint s, IntPtr sa, uint c, uint f, IntPtr t);
  [StructLayout(LayoutKind.Sequential)] struct COORD { public short X; public short Y; }
  [StructLayout(LayoutKind.Sequential)] struct SMALL_RECT { public short L, T, R, B; }
  [StructLayout(LayoutKind.Sequential)] struct CSBI { public COORD Size; public COORD Cursor; public short Attr; public SMALL_RECT Win; public COORD Max; }
  [DllImport("kernel32.dll")] static extern bool GetConsoleScreenBufferInfo(IntPtr h, out CSBI i);
  [DllImport("kernel32.dll", CharSet=CharSet.Unicode)] static extern bool ReadConsoleOutputCharacter(IntPtr h, StringBuilder b, uint len, COORD c, out uint read);
  [DllImport("kernel32.dll")] static extern bool CloseHandle(IntPtr h);
  public static string Read(uint pid, int lines) {
    FreeConsole();
    if (!AttachConsole(pid)) return "attach failed " + Marshal.GetLastWin32Error();
    IntPtr h = CreateFile("CONOUT$", 0xC0000000, 3, IntPtr.Zero, 3, 0, IntPtr.Zero);
    CSBI i; GetConsoleScreenBufferInfo(h, out i);
    var sb = new StringBuilder();
    int start = Math.Max(0, i.Cursor.Y - lines);
    for (int y = start; y <= i.Cursor.Y; y++) {
      var line = new StringBuilder(i.Size.X + 1); uint r;
      COORD c; c.X = 0; c.Y = (short)y;
      ReadConsoleOutputCharacter(h, line, (uint)i.Size.X, c, out r);
      sb.AppendLine(line.ToString().TrimEnd());
    }
    CloseHandle(h); FreeConsole();
    return sb.ToString();
  }
}
'@
[ConRead]::Read([uint32]$ProcessId, $Lines)
