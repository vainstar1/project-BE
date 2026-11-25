// Attach Frida to a running game process and load an agent script.
// usage: node attach.js <pid> <agent.js> [seconds]
// Agent scripts get a prelude with helpers: VA(x), fstr(ptr), bt(ctx), hook(va, name, {onEnter, onLeave}).
const fs = require('fs');
const FRIDA = 'C:/Users/andre/OneDrive/Desktop/big folder/bleeding-edge-rea-research/tools/rea/node_modules/frida';
const frida = require(FRIDA);
const pid = parseInt(process.argv[2]);
const agent = fs.readFileSync(process.argv[3], 'utf8');
const secs = parseInt(process.argv[4] || '0');
const prelude = `
const mod = Process.enumerateModules()[0];
function VA(x) { return mod.base.add(ptr(x).sub(ptr('0x140000000'))); }
function RVA(p) { return '0x' + p.sub(mod.base).add(ptr('0x140000000')).toString(16); }
function fstr(p) { try { const d = p.readPointer(); const n = p.add(8).readS32(); if (d.isNull() || n <= 0) return ''; return d.readUtf16String(n - 1); } catch (e) { return '<bad>'; } }
function bt(ctx) { return Thread.backtrace(ctx, Backtracer.FUZZY).slice(0, 10).map(a => { const m = Process.findModuleByAddress(a); return m && m.name === mod.name ? RVA(a) : (m ? m.name : a.toString()); }).join(' < '); }
function log(...a) { send(a.join(' ')); }
function hook(va, name, cb) {
  try { Interceptor.attach(VA(va), { onEnter(args) { this.args = args; if (cb && cb.onEnter) cb.onEnter.call(this, args); else log('>', name, args[0], args[1], args[2], args[3]); },
    onLeave(r) { if (cb && cb.onLeave) cb.onLeave.call(this, r); } }); }
  catch (e) { log('hook failed', name, e); }
}
`;
(async () => {
  const s = await frida.attach(pid);
  const sc = await s.createScript(prelude + agent);
  sc.message.connect(m => console.log(new Date().toISOString().substr(11, 12), m.type === 'send' ? m.payload : JSON.stringify(m)));
  await sc.load();
  console.log('agent loaded');
  if (secs > 0) { await new Promise(r => setTimeout(r, secs * 1000)); await s.detach(); process.exit(0); }
  s.detached.connect(() => process.exit(0));
})().catch(e => { console.error('ERR', e); process.exit(1); });
