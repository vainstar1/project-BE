import sys,numpy as np,os
sys.path.insert(0,os.path.dirname(__file__))
from xref import *
t=[s for s in secs if s[0]=='.text'][0]
tb=np.frombuffer(data[t[3]:t[3]+t[4]],dtype=np.uint8)
n=len(tb)-4
d=(tb[0:n].astype(np.int64)|(tb[1:n+1].astype(np.int64)<<8)|(tb[2:n+2].astype(np.int64)<<16)|(tb[3:n+3].astype(np.int64)<<24))
d=np.where(d>=2**31,d-2**32,d)
tgt=d+np.arange(n,dtype=np.int64)+4+t[1]
np.save(os.path.join(os.path.dirname(__file__),'rel32tgt.npy'),tgt)
