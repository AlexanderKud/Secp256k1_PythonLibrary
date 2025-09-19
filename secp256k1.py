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

secp256k1.double_point.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.double_point.restype = None

secp256k1.negate_point.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
secp256k1.double_point.restype = None

secp256k1.add_points.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.add_points.restype = None

secp256k1.add_point_scalar.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.add_point_scalar.restype = None

secp256k1.subtract_points.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.add_points.restype = None

secp256k1.subtract_point_scalar.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.add_point_scalar.restype = None

secp256k1.point_multiplication.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.point_multiplication.restype = None

secp256k1.privatekey_to_hash160.argtypes = [ctypes.c_int, ctypes.c_bool, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.privatekey_to_hash160.restype = None

secp256k1.publickey_to_hash160.argtypes = [ctypes.c_int, ctypes.c_bool, ctypes.c_char_p, ctypes.c_char_p]
secp256k1.publickey_to_hash160.restype = None

N = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141
def multiplicative_inverse(x):
    return pow(x, N - 2, N)
    
secp256k1.Init()

def check():
    secp256k1.check()
    
def scalar_multiplication(pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.scalar_multiplication(pvk, res)
    return bytes(bytearray(res))

def point_to_upub(pBytes):
    res = (b'\x00') * 65
    secp256k1.point_to_upub(pBytes, res)
    return bytes(bytearray(res)).hex()
    
def point_to_cpub(pBytes):
    res = (b'\x00') * 33
    secp256k1.point_to_cpub(pBytes, res)
    return bytes(bytearray(res)).hex()

def double_point(pBytes):
    res = (b'\x00') * 65
    secp256k1.double_point(pBytes, res)
    return bytes(bytearray(res))

def negate_point(pBytes):
    res = (b'\x00') * 65
    secp256k1.negate_point(pBytes, res)
    return bytes(bytearray(res))

def add_points(p1, p2):
    res = (b'\x00') * 65
    secp256k1.add_points(p1, p2, res)
    return bytes(bytearray(res))

def add_point_scalar(p, pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.add_point_scalar(p, pvk, res)
    return bytes(bytearray(res))

def subtract_points(p1, p2):
    res = (b'\x00') * 65
    secp256k1.subtract_points(p1, p2, res)
    return bytes(bytearray(res))

def subtract_point_scalar(p, pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.subtract_point_scalar(p, pvk, res)
    return bytes(bytearray(res))

def point_multiplication(p, pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.point_multiplication(p, pvk, res)
    return bytes(bytearray(res))

def point_division(p, pk):
    pvk = str(multiplicative_inverse(pk)).encode('utf8')
    res = (b'\x00') * 65
    secp256k1.point_multiplication(p, pvk, res)
    return bytes(bytearray(res))

def privatekey_to_hash160(addr_type, compressed, pk):
    pvk = str(pk).encode('utf8')
    res = (b'\x00') * 20
    secp256k1.privatekey_to_hash160(addr_type, compressed, pvk, res)
    return bytes(bytearray(res)).hex()
    
def publickey_to_hash160(addr_type, compressed, pBytes):
    res = (b'\x00') * 20
    secp256k1.publickey_to_hash160(addr_type, compressed, pBytes, res)
    return bytes(bytearray(res)).hex()
