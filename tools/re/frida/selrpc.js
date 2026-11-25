for (const [va, n] of [[0x1413aa250,'SelectCharacterOnServer'],[0x1413ac3c0,'SetSelectingCharacterOnServer'],[0x1413ac6d0,'SubmitChangePlayerClassInputEventOnServer'],[0x1413ad910,'ViewingCharacterOnServer'],[0x1413a9710,'NotifyCharacterSelectReceived']]) {
  hook(va, n, { onEnter(a) { log('RPC', n, 'obj=' + a[0]); log('  BT ' + bt(this.context)); } });
}
log('rpc hooks ready');
