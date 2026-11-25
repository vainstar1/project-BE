import json,sys,os,bisect
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
V=json.load(open(os.path.join(os.path.dirname(__file__),'vtables.json'),encoding='utf-8-sig'))['objects']
def size(va):
    rva=int(va,16)-base; f=func_of(rva)
    return (f[1]-f[0]) if f and f[0]==rva else None
def diff(a,bases):
    A=V[a]['entries']; Bs=[V[b]['entries'] for b in bases]
    print(f"### {a.split('Default__')[1]} vs {[b.split('Default__')[1] for b in bases]}")
    for i,e in enumerate(A):
        inb=[ (i<len(B) and B[i]==e) for B in Bs]
        if not any(inb): print(f"  slot {i:3d} {e} size={size(e)}")
diff('/Script/NTRollbackEngine.Default__NTRollbackChannel',['/Script/Engine.Default__ControlChannel','/Script/Engine.Default__ActorChannel','/Script/Engine.Default__VoiceChannel'])
diff('/Script/NTRollbackEngine.Default__NTRollbackMachineGroupConnected',['/Script/NTRollbackEngine.Default__NTRollbackMachineGroupLocal'])
diff('/Script/NTRollbackEngine.Default__NTRollbackMachineGroupLocal',['/Script/NTRollbackEngine.Default__NTRollbackMachineGroupConnected'])
