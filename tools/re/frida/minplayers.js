const p = VA(0x144f357b8); log('min players was', p.readS32()); Memory.protect(p, 4, 'rw-'); p.writeS32(2); log('now', p.readS32());
