import ctypes

secp256k1 = ctypes.CDLL("./secp256k1_lib.so")
libc = ctypes.CDLL("libc.so.6")

print(libc.rand())
libc.printf(b"spam\n")
s = "Hello World"
str_obj = ctypes.c_wchar_p(s)
print(str_obj.value)
print(type(str_obj.value))

secp256k1.Init()
secp256k1.check()

#secp256k1.ret_str.argtypes = []
secp256k1.ret_str.restype = ctypes.c_char_p
s = secp256k1.ret_str()
pub = "0479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8"
print(s.decode() == pub)

N = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141
def fl(sstr, length=64):
    ''' Fill input to exact 32 bytes. If input is int or str the return is str. if input is bytes return is bytes'''
    if type(sstr) == int: fixed = hex(sstr % N)[2:].zfill(length)
    elif type(sstr) == str: fixed = sstr[2:].zfill(length) if sstr[:2].lower() == '0x' else sstr.zfill(length)
    elif type(sstr) == bytes: fixed = (b'\x00') * (32 - len(sstr)) + sstr
    else: print("[Error] Input format [Integer] [Hex] [Bytes] allowed only. Detected : ", type(sstr))
    return fixed

print(fl(88).encode('utf8'))

secp256k1.get_int.argtypes = [ctypes.c_char_p]
secp256k1.get_int.restype = None
secp256k1.get_int(str(1977).encode('utf8'))

secp256k1.get_int2.argtypes = None
secp256k1.get_int2.restype = ctypes.c_char_p
gi = int(secp256k1.get_int2())
print(gi)
