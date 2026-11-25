import sys,re,pefile,bisect,pickle,os
EXE=r"D:\SteamLibrary\steamapps\common\Bleeding Edge\Moblade\Binaries\Win64\MobladeClient-Win64-Shipping.exe"
cache=os.path.join(os.path.dirname(__file__),'pe.pkl')
if os.path.exists(cache):
    base,secs,data,funcs,leas=pickle.load(open(cache,'rb'))
else:
    pe=pefile.PE(EXE,fast_load=True); pe.parse_data_directories(directories=[3])
    base=pe.OPTIONAL_HEADER.ImageBase
    data=open(EXE,'rb').read()
    secs=[(s.Name.rstrip(b'\0').decode(),s.VirtualAddress,s.Misc_VirtualSize,s.PointerToRawData,s.SizeOfRawData) for s in pe.sections]
    funcs=sorted((e.struct.BeginAddress,e.struct.EndAddress) for e in pe.DIRECTORY_ENTRY_EXCEPTION)
    t=[s for s in secs if s[0]=='.text'][0]
    tb=data[t[3]:t[3]+t[4]]
    leas={}
    # rip-relative lea / mov / call / jmp: REX? 8D modrm(mod=00,rm=101)
    for m in re.finditer(rb'[\x48\x4c]\x8d[\x05\x0d\x15\x1d\x25\x2d\x35\x3d]',tb):
        o=m.start(); disp=int.from_bytes(tb[o+3:o+7],'little',signed=True)
        rva=t[1]+o; tgt=rva+7+disp
        leas.setdefault(tgt,[]).append(rva)
    pickle.dump((base,secs,data,funcs,leas),open(cache,'wb'))
def off2rva(off):
    for n,va,vs,pr,ps in secs:
        if pr<=off<pr+ps: return va+off-pr
def func_of(rva):
    i=bisect.bisect_right(funcs,(rva,1<<40))-1
    if i>=0 and funcs[i][0]<=rva<funcs[i][1]: return funcs[i]
    return None
if __name__=='__main__':
    for s in sys.argv[1:]:
        for enc in ('utf-16-le','ascii'):
            for m in re.finditer(re.escape(s.encode(enc)),data):
                rva=off2rva(m.start())
                refs=leas.get(rva,[])
                print(f"[{enc[:5]}] '{s}' str_rva={hex(rva)} refs={len(refs)}")
                for r in refs:
                    f=func_of(r); print(f"     ref {hex(base+r)} in pdata-frag {hex(base+f[0]) if f else None}-{hex(base+f[1]) if f else ''}")
