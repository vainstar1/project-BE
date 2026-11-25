import sys,os,re,numpy as np
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
tgt=np.load(os.path.join(os.path.dirname(__file__),'rel32tgt.npy'))
order=np.argsort(tgt,kind='stable'); st=tgt[order]
def refs(rva):
    i=np.searchsorted(st,rva); j=np.searchsorted(st,rva,side='right')
    return [0x1000+int(x)-1 for x in order[i:j]]   # opcode byte position for E8/E9 = disp_pos-1
def callers(func_rva):
    out=[]
    for p in refs(func_rva):
        o=p- 0x1000 + [s for s in secs if s[0]=='.text'][0][3]
        if data[o] in (0xE8,0xE9): out.append((p,'call' if data[o]==0xE8 else 'jmp'))
    return out
def fn(r):
    f=func_of(r); return f[0] if f else None
for name in sys.argv[1:]:
    for m in re.finditer(re.escape(name.encode('utf-16-le'))+b'\x00\x00',data):
        srva=off2rva(m.start())
        if data[m.start()-2:m.start()]!=b'\x00\x00' and 0x20<=data[m.start()-2]<0x7f: continue
        ls=leas.get(srva,[])
        for l in ls:
            f=fn(l)
            print(f"{name}: lea at {base+l:x} in func {base+f:x}" if f else f"{name}: lea {base+l:x}")
            if f:
                cs=callers(f)
                for c,k in cs[:12]: print(f"     {k}er {base+c:x} in {base+fn(c):x}" if fn(c) else f"     {k} {base+c:x}")
