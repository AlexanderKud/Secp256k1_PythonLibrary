import ctypes

secp256k1 = ctypes.CDLL("./secp256k1_lib.so")

secp256k1.check.argtypes = None
secp256k1.check.restype = None

secp256k1.scalar_multiplication.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.scalar_multiplication.restype = None

secp256k1.Init()

def check():
    secp256k1.check()
    
def scalar_multiplication(pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.scalar_multiplication(pvk, res)
    return res
