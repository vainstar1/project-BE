for (const [va,n] of [[0x141037240,'A37240'],[0x141056980,'A56980'],[0x141056b90,'A56b90'],[0x1410f8f70,'Af8f70'],[0x1410f9640,'Af9640'],[0x141102a80,'A102a80'],[0x1411ea220,'A1ea220'],[0x1429f1290,'A9f1290'],[0x142a81890,'Aa81890'],[0x142a8eca0,'Aa8eca0']]) {
  hook(va, n, { onEnter(a) { log(n, a[0], a[1], a[2], a[3]); log('  BT ' + bt(this.context)); } });
}
// AddPlayer factory: log TeamId once the caller fills it (read on the next AddInputEvent)
hook(0x141030c00, 'AddPlayerFactory', { onLeave(r) { globalThis.lastAP = r; log('AddPlayer event created', r); } });
hook(0x1403f66d0, 'AddInputEvent', { onEnter(a) { if (globalThis.lastAP && a[1].equals(globalThis.lastAP)) { log('AddPlayer submitted pid=' + a[1].add(0x30).readS32() + ' team=' + a[1].add(0xd8).readS32()); globalThis.lastAP = null; } } });
log('addplayer hooks ready');
