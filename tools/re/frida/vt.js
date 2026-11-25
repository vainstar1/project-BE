const o=ptr('0x1ADB9CD99A0'); const vt=o.readPointer(); log('vt', RVA(vt), 'validate', RVA(vt.add(0xe20).readPointer()), 'impl', RVA(vt.add(0xe28).readPointer()));
