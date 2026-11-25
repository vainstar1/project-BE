// Client-side join trace.
hook(0x1425c4570, 'Browse', {
  onEnter(a) { this.url = a[2]; log('BT ' + bt(this.context)); if (globalThis.PNG) log('pending err=' + fstr(globalThis.PNG.add(0xb8)) + ' / ' + fstr(globalThis.PNG.add(0xc8))); log('Browse host=' + fstr(a[2].add(0x10)) + ' port=' + a[2].add(0x20).readS32() + ' map=' + fstr(a[2].add(0x28))); },
  onLeave(r) { log('Browse ->', r.toInt32() & 0xff); }
});
hook(0x14242aee0, 'PendingNetGame::InitNetDriver', {
  onEnter(a) { this.p = a[0]; globalThis.PNG = a[0]; log('InitNetDriver pending=' + a[0]); },
  onLeave(r) { log('InitNetDriver done netdriver=' + this.p.add(0x30).readPointer()); }
});
hook(0x140803E70, 'SteamNetDriver::InitConnect', {
  onEnter(a) { this.err = a[3]; log('Steam InitConnect url host=' + fstr(a[2].add(0x10))); },
  onLeave(r) { log('Steam InitConnect ->', r.toInt32() & 0xff, 'err=' + fstr(this.err)); }
});
hook(0x1404CBA60, 'IpNetDriver::InitConnect', {
  onEnter(a) { this.err = a[3]; log('Ip InitConnect'); },
  onLeave(r) { log('Ip InitConnect ->', r.toInt32() & 0xff, 'err=' + fstr(this.err)); }
});
hook(0x1425e17d0, 'MovePendingLevel', { onEnter(a) { log('MovePendingLevel'); } });
hook(0x1425def60, 'LoadMap', { onEnter(a) { log('LoadMap map=' + fstr(a[2].add(0x28)) + ' host=' + fstr(a[2].add(0x10))); }, onLeave(r) { log('LoadMap ->', r.toInt32() & 0xff); } });
log('join hooks ready');
