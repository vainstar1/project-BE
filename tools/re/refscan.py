import sys,re,os,numpy as np
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
tgt=np.load(os.path.join(os.path.dirname(__file__),'rel32tgt.npy'))
order=np.argsort(tgt); st=tgt[order]
def refs(rva):
    i=np.searchsorted(st,rva); j=np.searchsorted(st,rva,side='right')
    return [0x1000+int(x)-3 for x in order[i:j]]
pat=re.compile(sys.argv[1],re.I)
seen=set()
for m in re.finditer(rb'(?:[\x20-\x7e]\x00){5,}',data):
    s=m.group().decode('utf-16-le')
    if not pat.search(s): continue
    rva=off2rva(m.start())
    if rva is None: continue
    r=refs(rva)
    key=s
    fs=sorted({hex(base+func_of(x)[0]) if func_of(x) else '?' for x in r})
    print(f"{len(r):2d} {hex(base+rva)} {s[:110]!r} {' '.join(fs[:4])}")
