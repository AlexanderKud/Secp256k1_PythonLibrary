import secp256k1

pk = 115792089237316195423570985008687907852837564279074904382605163141518161494336
P = secp256k1.scalar_multiplication(pk)
print(P.hex())
print(secp256k1.point_to_upub(P)) # uncompressed pubkey
print(secp256k1.point_to_cpub(P)) # compressed pubkey
'''
ripemd160 hash
P2PKH  0
P2SH   1
BECH32 2
'''
print(secp256k1.privatekey_to_hash160(0, False, pk)) # uncompressed ripemd160 hash
print(secp256k1.privatekey_to_hash160(0, True, pk))  # compressed ripemd160 hash
print()
P2 = secp256k1.scalar_multiplication(2)
print(f'P2: {secp256k1.point_to_upub(P2)}') # uncompressed pubkey
print(secp256k1.privatekey_to_hash160(0, False, 4)) # uncompressed ripemd160 hash
print(secp256k1.privatekey_to_hash160(0, True, 4))  # compressed ripemd160 hash
print()
P3 = secp256k1.scalar_multiplication(3)
print(f'P3: {secp256k1.point_to_upub(P3)}') # uncompressed pubkey
print()
P5 = secp256k1.add_points(P2 ,P3)
print(f'P5: {secp256k1.point_to_upub(P5)}') # uncompressed pubkey
P5_neg = secp256k1.negate_point(P5)
print()
print(f'P5_neg: {secp256k1.point_to_upub(P5_neg)}') # uncompressed pubkey

