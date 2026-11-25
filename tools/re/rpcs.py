import json,sys,collections
d=json.load(open(sys.argv[1]))
owner={}
for c in d['classes']:
    n=(c.get('name_candidates') or ['?'])[0]
    for f in c.get('functions',[]):
        owner[f['descriptor_va']]=n
FUNC_Net=0x40; NetReliable=0x80; NetMulticast=0x4000; NetServer=0x200000; NetClient=0x1000000
by=collections.defaultdict(list)
for f in d['functions']:
    fl=int(f['function_flags'],16)
    if fl & FUNC_Net:
        kind='Server' if fl&NetServer else 'Client' if fl&NetClient else 'Multicast' if fl&NetMulticast else 'Net?'
        rel='R' if fl&NetReliable else 'U'
        params=",".join(f"{p['name']}:{p['type']}" for p in f.get('properties',[]) if 'container_parent_va' not in p)
        by[owner.get(f['va'],'?')].append(f"{kind}/{rel} {f['name']}({params}) psize={f['parameter_struct_size']}")
tot=0
for k in sorted(by):
    print(f"== {k} ({len(by[k])})")
    for x in by[k]: print("   ",x)
    tot+=len(by[k])
print("TOTAL",tot)
