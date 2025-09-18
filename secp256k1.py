import ctypes

secp256k1 = ctypes.CDLL("./secp256k1_lib.so")

secp256k1.check.argtypes = None
secp256k1.check.restype = None

secp256k1.scalar_multiplication.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.scalar_multiplication.restype = None

secp256k1.point_to_upub.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.point_to_upub.restype = None

secp256k1.point_to_cpub.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.point_to_cpub.restype = None

secp256k1.privatekey_to_hash160.argtypes = [ctypes.c_int, ctypes.c_bool, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.privatekey_to_hash160.restype = None

secp256k1.publickey_to_hash160.argtypes = [ctypes.c_int, ctypes.c_bool, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.publickey_to_hash160.restype = None

secp256k1.Init()

def check():
    secp256k1.check()
    
def scalar_multiplication(pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.scalar_multiplication(pvk, res)
    return res

def point_to_upub(pBytes):
    res = (b'\x00') * 65
    secp256k1.point_to_upub(pBytes, res)
    return res.hex()
    
def point_to_cpub(pBytes):
    res = (b'\x00') * 33
    secp256k1.point_to_cpub(pBytes, res)
    return res.hex()

def privatekey_to_hash160(addr_type, compressed, pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 20
    secp256k1.privatekey_to_hash160(addr_type, compressed, pvk, res)
    return res.hex()
    
def publickey_to_hash160(addr_type, compressed, pBytes):
    res = (b'\x00') * 20
    secp256k1.publickey_to_hash160(addr_type, compressed, pBytes, res)
    return res.hex()
