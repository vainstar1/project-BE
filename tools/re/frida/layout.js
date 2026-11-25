// Measures UStruct/UClass/UProperty layouts for the native reflection layer.
const GUObjectArray = VA('0x14507ff60');
const toStr = new NativeFunction(VA('0x14150ac20'), 'void', ['pointer', 'pointer']);
function nameOf(obj) {
  const out = Memory.alloc(16); out.writeU64(0); out.add(8).writeU64(0);
  toStr(obj.add(0x18), out); return fstr(out);
}
const objs = GUObjectArray.add(0x10);
const chunks = objs.readPointer(); const num = objs.add(0x14).readS32();
log('num objects', num, 'maxel', objs.add(0x10).readS32(), 'chunks', objs.add(0x1c).readS32());
function objAt(i) { const ch = chunks.add(8 * Math.floor(i / 65536)).readPointer(); return ch.add(0x18 * (i % 65536)).readPointer(); }
let found = {};
for (let i = 0; i < num; i++) {
  const o = objAt(i); if (o.isNull()) continue;
  const n = nameOf(o);
  if (['MBCustomGameManager', 'IsInCustomGameLobby', 'MemberList', 'Object', 'Class', 'MBCustomGameMember', 'GetTeamMaxPlayers', 'UniqueNetId'].includes(n)) {
    const c = o.add(0x10).readPointer(); const cn = nameOf(c);
    log(i, n, 'cls', cn, o);
    if (!found[n + cn]) { found[n + cn] = 1; log(hexdump(o, { length: 0xe0, header: false, ansi: false })); }
  }
}
