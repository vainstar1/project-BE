import json,sys,re
d=json.load(open(sys.argv[1]))
pat=re.compile(sys.argv[2])
fn={f['va']:f for f in d['functions']}
for c in d['classes']:
    n=(c.get('name_candidates') or ['?'])[0]
    if not pat.fullmatch(n): continue
    print(f"=== {n} flags={c['class_flags']} config={c.get('config_name')}")
    for p in c.get('properties',[]):
        if 'container_parent_va' in p: continue
        print(f"   P {p['offset']:>6} {p['type']:<10} {p['name']}  pf={p['property_flags']}")
    for f in c.get('functions',[]):
        F=fn.get(f['descriptor_va'])
        if F:
            ps=",".join(f"{q['name']}:{q['type']}" for q in F.get('properties',[]) if 'container_parent_va' not in q)
            print(f"   F {F['function_flags']} {f['name']}({ps})")
        else: print(f"   F ? {f['name']}")
