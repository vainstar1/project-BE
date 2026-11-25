const path = require('path');
const frida = require(process.argv[2]);
const exe = 'D:/SteamLibrary/steamapps/common/Bleeding Edge/Moblade/Binaries/Win64/MobladeClient-Win64-Shipping.exe';
const src = `
const mod = Process.getModuleByName('MobladeClient-Win64-Shipping.exe');
function bt(ctx){ return Thread.backtrace(ctx, Backtracer.ACCURATE).slice(0,14).map(a=>{const m=Process.findModuleByAddress(a); return m? m.name+'+0x'+a.sub(m.base).toString(16) : a.toString();}).join(' <- '); }
for (const [m,f] of [['kernel32.dll','ExitProcess'],['ntdll.dll','NtTerminateProcess'],['kernel32.dll','TerminateProcess'],['ucrtbase.dll','exit'],['ucrtbase.dll','_exit']]) {
  try { const a = Process.getModuleByName(m).getExportByName(f);
    Interceptor.attach(a,{onEnter(args){ send(f+' code='+args[0]+' :: '+bt(this.context)); }}); } catch(e) { send('nohook '+f+' '+e); }
}
send('hooks installed base='+mod.base);
`;
(async () => {
  const pid = await frida.spawn([exe,'-log','-windowed'], {cwd: path.dirname(exe)});
  const s = await frida.attach(pid);
  const sc = await s.createScript(src);
  sc.message.connect(m => console.log(m.type==='send'? m.payload : JSON.stringify(m)));
  await sc.load();
  await frida.resume(pid);
  await new Promise(r => setTimeout(r, 25000));
  try { await s.detach(); } catch(e){}
  process.exit(0);
})().catch(e=>{console.error('ERR',e); process.exit(1);});
