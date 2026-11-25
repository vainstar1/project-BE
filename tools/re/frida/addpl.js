hook(0x1410eee70, 'AddPl', { onEnter(a) { const s=a[2]; log('AddPl this=' + a[0] + ' idx=' + a[1].toInt32() + ' slot=[' + [0,4,8,12,16,20,24].map(o=>s.add(o).readS32()).join(',') + '] p4=' + a[3]); log('  BT ' + bt(this.context)); } });
log('addpl hook ready');
