import sys,os
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
import capstone
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_64); md.detail=False
def rva2off(rva):
    for n,va,vs,pr,ps in secs:
        if va<=rva<va+ps: return pr+rva-va
def fsize(rva):
    f=func_of(rva); return f
def disasm(va,maxlen=0x1200,show=True):
    rva=va-base; o=rva2off(rva); code=data[o:o+maxlen]; calls=[]; out=[]
    for i in md.disasm(code,va):
        out.append(f"{i.address:x}: {i.mnemonic} {i.op_str}")
        if i.mnemonic=='call' and i.op_str.startswith('0x'): calls.append(int(i.op_str,16))
        if i.mnemonic=='int3' and len(out)>3 and out[-2].endswith('int3'): break
    if show: print('\n'.join(out))
    return calls,out
if __name__=='__main__':
    va=int(sys.argv[1],16); n=int(sys.argv[2],16) if len(sys.argv)>2 else 0x1200
    calls,out=disasm(va,n,show='-q' not in sys.argv)
    print('CALLS:')
    for c in dict.fromkeys(calls):
        f=func_of(c-base); print(f"  {c:x} size={(f[1]-f[0]) if f and f[0]==c-base else '?'}")
