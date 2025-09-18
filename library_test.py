import secp256k1
'''
pk = 1
for i in range(1000000):
    P = secp256k1.scalar_multiplication(pk)
    pk += 1
'''
pk = 115792089237316195423570985008687907852837564279074904382605163141518161494336
#pk = 1
P = secp256k1.scalar_multiplication(pk)
print(P.hex())
print(secp256k1.point_to_upub(P))
print(secp256k1.point_to_cpub(P))
