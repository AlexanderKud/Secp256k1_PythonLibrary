import ctypes

secp256k1 = ctypes.CDLL('./secp256k1_lib.so')

secp256k1.Init()
secp256k1.check()
