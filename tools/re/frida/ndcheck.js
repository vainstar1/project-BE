const eng = VA(0x14558F8B0).readPointer();
const ctxs = eng.add(0xbb8).readPointer(), n = eng.add(0xbc0).readS32();
for (let i = 0; i < n; i++) { const w = ctxs.add(i*8).readPointer().add(0x288).readPointer(); if (w.isNull()) continue;
  const nd = w.add(0x38).readPointer(); if (nd.isNull()) { log('world', w, 'no netdriver'); continue; }
  log('netdriver', nd, 'vt', RVA(nd.readPointer()), 'passthrough', nd.add(0x568).readU8(), 'steamSocket', nd.add(0x550).readPointer()); }
