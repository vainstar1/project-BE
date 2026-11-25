"""Decompile functions with the retained headless Ghidra project.
usage: python decomp.py OUTDIR addr[:label] [addr ...]
Bounds come from .pdata (with chained unwind fragments merged by scanning forward).
"""
import sys, os, subprocess, glob, shutil
sys.path.insert(0, os.path.dirname(__file__))
from xref import base, func_of, funcs
import bisect

REV = r"C:\Users\andre\OneDrive\Desktop\big folder\bleeding-edge-revival"
GH = r"C:\Users\andre\OneDrive\Desktop\big folder\bleeding-edge-rea-research\tools\ghidra_12.1.4_PUBLIC"
SCRIPTS = REV + r"\tools\research\ghidra"
PROJ = REV + r"\local\research\ghidra\projects"
SNAP = "41ab697b4edd3061baff37568de6e9501427374a859b048b3595f29297bfd306.exe"

def bound(va):
    rva = va - base
    f = func_of(rva)
    end = f[1] if f else rva + 0x400
    # extend over adjacent fragments until next function start that is called/known? keep generous window
    return base + max(end, rva + 0x40) + 0x800

out = os.path.abspath(sys.argv[1]); os.makedirs(out, exist_ok=True)
seeds = os.path.join(out, "seeds.tsv")
with open(seeds, "w") as f:
    for a in sys.argv[2:]:
        addr, _, label = a.partition(":")
        va = int(addr, 16)
        f.write(f"0x{va:X}\t0x{bound(va):X}\t{label or 'F_%X' % va}\n")
env = dict(os.environ, JAVA_HOME=r"C:\Program Files\Microsoft\jdk-21.0.10.7-hotspot", GHIDRA_HEADLESS_MAXMEM="8G")
args = [GH + r"\support\analyzeHeadless.bat", PROJ, "BleedingEdgeFocused_41ab697b4edd", "-noanalysis", "-scriptPath", SCRIPTS,
        "-postScript", "ExportFocusedPseudocode.java", seeds, out, SNAP[:-4], "-", "-", "-process", SNAP,
        "-log", os.path.join(out, "headless.log"), "-scriptlog", os.path.join(out, "script.log")]
r = subprocess.run(args, env=env, capture_output=True, text=True)
if r.returncode:
    print(r.stdout[-3000:], r.stderr[-3000:])
for c in sorted(glob.glob(os.path.join(out, "*.c"))):
    print("=" * 20, os.path.basename(c))
    print(open(c, encoding="utf-8", errors="replace").read())
