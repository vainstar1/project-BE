import sys,re,mmap,json
exe=sys.argv[1]; out=sys.argv[2]
data=open(exe,'rb').read()
res=[]
for m in re.finditer(rb'[\x20-\x7e]{6,}',data): res.append((m.start(),'A',m.group().decode()))
for m in re.finditer(rb'(?:[\x20-\x7e]\x00){6,}',data): res.append((m.start(),'U',m.group().decode('utf-16-le')))
res.sort()
with open(out,'w',encoding='utf-8') as f:
    for o,k,s in res: f.write(f"{o:08x} {k} {s}\n")
print(len(res))
