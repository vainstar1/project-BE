// Text chat path on the host: ServerBroadcastChat exec/impl, the per-receiver filter, the per-receiver send.
hook(0x1413aa490, 'ServerBroadcastChat_exec', { onEnter(a) { log('exec ServerBroadcastChat pc=' + a[0]); } });
hook(0x1410c7910, 'ServerBroadcastChat_Impl', { onEnter(a) { log('impl ServerBroadcastChat pc=' + a[0] + ' channel=' + a[2].toInt32() + ' target=' + a[3].toInt32()); } });
hook(0x1410bdda0, 'ChatFilter', {
  onEnter(a) { this.out = a[4]; log('filter sender=' + a[0] + ' recv=' + a[1] + ' ch=' + a[2].toInt32()); },
  onLeave(r) { log('  filter -> ' + (r.toInt32() & 0xff) + ' muted=' + this.out.readU8()); }
});
hook(0x1413a3960, 'SendToReceiver', { onEnter(a) { log('deliver to pc=' + a[0] + ' talker=' + a[2].toInt32() + ' ch=' + a[3].toInt32()); } });
hook(0x1413a45b0, 'CallServerBroadcast', { onEnter(a) { log('client->server ServerBroadcastChat pc=' + a[0] + ' ch=' + a[2].toInt32()); } });
hook(0x1410c6710, 'SendChat', { onEnter(a) { log('SendChat pc=' + a[0] + ' ch=' + a[2].toInt32()); } });
hook(0x14103ed80, 'PlayfabPath', { onEnter(a) { log('playfab path ' + a[1].toInt32()); } });
