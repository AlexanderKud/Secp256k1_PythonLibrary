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
Q = secp256k1.scalar_multiplication(33)
print(secp256k1.publickey_to_hash160(0, False, Q)) # uncompressed ripemd160 hash
print(secp256k1.publickey_to_hash160(0, True, Q))  # compressed ripemd160 hash

