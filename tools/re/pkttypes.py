import sys,os,re,struct,collections
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
def rva2off(rva):
    for n,va,vs,pr,ps in secs:
        if va<=rva<va+ps: return pr+rva-va
def q(rva): o=rva2off(rva); return struct.unpack('<Q',data[o:o+8])[0]
def fn(r): f=func_of(r); return f[0] if f else None
R=[s for s in secs if s[0]=='.rdata'][0]
# 1) pure virtual stub for FNTRollbackPacket::GetPacketType
for nm in ['FNTRollbackPacket::GetPacketType','FNTRollbackRecordingPacket::GetPacketType']:
    for m in re.finditer(re.escape(nm.encode('utf-16-le'))+b'\x00\x00',data):
        s=off2rva(m.start())
        for l in leas.get(s,[]):
            f=fn(l); print(nm,'stub func',hex(base+f))
            # vtables containing f
            pat=struct.pack('<Q',base+f)
            for mm in re.finditer(re.escape(pat),data):
                p=off2rva(mm.start()); print('   base vtable slot at',hex(base+p))

# 2) base vtable start / slot index
slot_rva=0x14341ebf8-base
s=slot_rva
while 0x140001000<=q(s-8)<0x143300000: s-=8
idx=(slot_rva-s)//8
print('base vtable start',hex(base+s),'GetPacketType slot',idx, 'entries:',[hex(q(s+8*i)) for i in range(idx+3)])
# 3) every .rdata qword pointing to tiny "mov eax,imm;ret"/"mov al,imm;ret" functions inside NT rollback code range
lo,hi=0x1403e0000,0x140440000
cands=collections.defaultdict(list)
Ro,Rn=R[3],R[4]
blob=data[Ro:Ro+Rn]
for i in range(0,len(blob)-8,8):
    v=struct.unpack_from('<Q',blob,i)[0]
    if lo<=v<hi:
        o=rva2off(v-base); b=data[o:o+6]
        imm=None
        if b[0]==0xB8 and b[5]==0xC3: imm=struct.unpack('<I',b[1:5])[0]
        elif b[0]==0xB0 and b[2]==0xC3: imm=b[1]
        if imm is not None:
            vt=R[1]+i-8*idx
            cands[imm].append((base+R[1]+i,base+vt,v))
for imm in sorted(cands):
    for slotaddr,vt,f in cands[imm]:
        # sanity: vt start must be preceded by non-code ptr (RTTI col or other)
        ctor=[base+l for l in leas.get(vt-base,[])]
        cf=sorted({hex(base+fn(c-base)) for c in ctor if fn(c-base)})
        print(f"type {imm:2d}: GetPacketType fn {f:x} vtable {vt:x} ctor-refs {len(ctor)} in funcs {cf[:8]}")
