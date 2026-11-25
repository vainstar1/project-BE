// Dumps ULevel candidates for the Actors TArray.
const eng = VA(0x14558F8B0).readPointer();
const ctxs = eng.add(0xbb8).readPointer(), nctx = eng.add(0xbc0).readS32();
for (let i = 0; i < nctx; i++) {
  const ctx = ctxs.add(i * 8).readPointer();
  const world = ctx.add(0x288).readPointer();
  if (world.isNull()) continue;
  const levels = world.add(0x160).readPointer(), nlev = world.add(0x168).readS32();
  log('world', world, 'levels', nlev, 'persistent', world.add(0x30).readPointer());
  for (let l = 0; l < Math.min(nlev, 3); l++) {
    const lev = levels.add(l * 8).readPointer();
    let s = 'level ' + l + ' ' + lev + ':';
    for (let o = 0x30; o < 0x200; o += 8) {
      try {
        const p = lev.add(o).readPointer(), n = lev.add(o + 8).readS32(), m = lev.add(o + 12).readS32();
        if (n > 0 && n <= m && m < 100000 && !p.isNull()) {
          // check first elements look like UObjects whose outer is the level
          const e0 = p.readPointer();
          let outer = e0.isNull() ? ptr(0) : e0.add(0x20).readPointer();
          s += ` [${o.toString(16)}: n=${n} m=${m} e0=${e0} outer=${outer}${outer.equals(lev) ? ' OUTER=LEVEL' : ''}]`;
        }
      } catch (e) {}
    }
    log(s);
  }
}
