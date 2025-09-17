import secp256k1

P = secp256k1.scalar_multiplication(1)
print(P)
print()
print(P.hex())
