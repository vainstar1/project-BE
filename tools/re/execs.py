"""Print native exec-wrapper VAs for class functions. usage: python execs.py <regex-class> [regex-func]"""
import json, sys, re, os, pickle
R = os.path.join(os.path.dirname(__file__), '..', '..', '..', 'bleeding-edge-revival', 'local', 'research', 'reflection', 'reflection-full.json')
cache = os.path.join(os.path.dirname(__file__), 'execs.pkl')
if os.path.exists(cache): idx = pickle.load(open(cache, 'rb'))
else:
    d = json.load(open(R)); idx = {}
    for c in d['classes']:
        n = (c.get('name_candidates') or ['?'])[0]
        b = c.get('native_bindings') or []
        if isinstance(b, list): idx[n] = [(x['name'], x['exec_wrapper_va']) for x in b]
    pickle.dump(idx, open(cache, 'wb'))
cp = re.compile(sys.argv[1]); fp = re.compile(sys.argv[2] if len(sys.argv) > 2 else '.*')
for n, fs in idx.items():
    if not cp.fullmatch(n): continue
    for f, va in fs:
        if fp.fullmatch(f): print(n, f, va)
