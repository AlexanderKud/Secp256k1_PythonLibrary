import secp256k1

pk = 115792089237316195423570985008687907852837564279074904382605163141518161494336
P = secp256k1.scalar_multiplication(pk)
print(P.hex())
print(secp256k1.point_to_upub(P))
print(secp256k1.point_to_cpub(P))
print(secp256k1.privatekey_to_hash160(0, False, pk))
print(secp256k1.privatekey_to_hash160(0, True, pk))
print()
Q = secp256k1.scalar_multiplication(33)
print(secp256k1.publickey_to_hash160(0, False, Q))
print(secp256k1.publickey_to_hash160(0, True, Q))
