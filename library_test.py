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
P5 = secp256k1.add_points(P2, P3)
print(f'P5: {secp256k1.point_to_upub(P5)}') # uncompressed pubkey
P5_neg = secp256k1.negate_point(P5)
print()
print(f'P5_neg: {secp256k1.point_to_upub(P5_neg)}') # uncompressed pubkey
PQ = secp256k1.add_point_scalar(P5, 25)
print(f'PQ: {secp256k1.point_to_upub(PQ)}') # uncompressed pubkey
P1 = secp256k1.subtract_points(P3, P2)
print(f'P1: {secp256k1.point_to_upub(P1)}') # uncompressed pubkey
PP = secp256k1.subtract_point_scalar(P3, 1)
print(f'PP: {secp256k1.point_to_upub(PP)}') # uncompressed pubkey
Pm = secp256k1.point_multiplication(P3, 8)
print(f'Pm: {secp256k1.point_to_upub(Pm)}') # uncompressed pubkey
Pd = secp256k1.point_division(Pm, 2)
print(f'Pm: {secp256k1.point_to_upub(Pd)}') # uncompressed pubkey
infinityP = secp256k1.add_points_safe(P5, P5_neg)
print(f'infinityP: {secp256k1.point_to_upub(infinityP)}') # uncompressed pubkey

addP1 = secp256k1.add_points_safe(infinityP, P1)
print(f'addP1: {secp256k1.point_to_upub(addP1)}') # uncompressed pubkey

subP1 = secp256k1.subtract_points_safe(infinityP, P1)
print(f'subP1: {secp256k1.point_to_upub(subP1)}') # uncompressed pubkey

subP2 = secp256k1.subtract_points_safe(P1, P1)
print(f'subP2: {secp256k1.point_to_upub(subP2)}') # uncompressed pubkey

addPs = secp256k1.add_point_scalar_safe(P1, 1024)
print(f'addPs: {secp256k1.point_to_upub(addPs)}') # uncompressed pubkey

subPs = secp256k1.subtract_point_scalar_safe(addPs, 9)
print(f'subPs: {secp256k1.point_to_upub(subPs)}') # uncompressed pubkey

incP = secp256k1.increment_point(P1)
print(f'incP: {secp256k1.point_to_upub(incP)}') # uncompressed pubkey

decP = secp256k1.decrement_point(P3)
print(f'decP: {secp256k1.point_to_upub(decP)}') # uncompressed pubkey

wif0 = "5HpHagT65TZzG1PH3CSu63k8DbpvD8s5ip4nEB3kEsreAnchuDf"
wif1 = secp256k1.privatekey_to_cwif(1)
print(wif1)
print(wif0 == wif1)

wif02 = "5HpHagT65TZzG1PH3CSu63k8DbpvD8s5ip4nEB3kEsreAvUcVfH"
wif2 = secp256k1.privatekey_to_uwif(2)
print(wif2)
print(wif0 == wif2)
print(wif02 == wif2)

wif03 = "KwDiBf89QgGbjEhKnhXJuH7LrciVrZi3qYjgd9M7rFU74sHUHy8S"
wif3 = secp256k1.privatekey_to_cwif(3)
print(wif3)
print(wif0 == wif3)
print(wif03 == wif3)

wiff = "L5iGPF2Ktx92hBbmvMsFBUNntd4vENWKFN3dyc5M8edEhenMRnbz"
wiffc = secp256k1.privatekey_to_cwif(114611115102251689443574372519848189708031905844456858542872688930023724442114)
print(wiffc)
print(wiff == wiffc)

wifu = secp256k1.privatekey_to_wif(False, 4)
wifc = secp256k1.privatekey_to_wif(True, 4)
print(len(wifu))
print(len(wifc))
print(wifu)
print(wifu == "5HpHagT65TZzG1PH3CSu63k8DbpvD8s5ip4nEB3kEsreB4AD8Yi")
print(wifc)
print(wifc == "KwDiBf89QgGbjEhKnhXJuH7LrciVrZi3qYjgd9M7rFU75NBY2dKG")

pk1 = secp256k1.wif_to_privatekey("5K2jRkYtEju8Ds2Y3HwwNBut1a6vADjy6B4Eu5N8NZbkiaZ5DTZ")
print(pk1)
pk2 = secp256k1.wif_to_privatekey("L5oLkpV3aqBjhki6LmvChTCV6odsp4SXM6FfU2Gppt5kFLaHLuZ9")
print(pk2)
pk3 = secp256k1.wif_to_privatekey("5HpHagT65TZzG1PH3CSu63k8DbpvD8s5ip4nEB3kEsreB4AD8Yi")
print(pk3)

pvk = 33
print(secp256k1.privatekey_to_address(0, False, pvk))
print(secp256k1.privatekey_to_address(0, True, pvk))
print(secp256k1.privatekey_to_address(1, True, pvk))
print(secp256k1.privatekey_to_address(2, True, pvk))

pnt = secp256k1.scalar_multiplication(77)
print(secp256k1.publickey_to_address(0, False, pnt))
print(secp256k1.publickey_to_address(0, True, pnt))
print(secp256k1.publickey_to_address(1, True, pnt))
print(secp256k1.publickey_to_address(2, True, pnt))

pnt = secp256k1.scalar_multiplication(7777)
print(secp256k1.publickey_to_address(0, False, pnt))
print(secp256k1.publickey_to_address(0, True, pnt))
print(secp256k1.publickey_to_address(1, True, pnt))
print(secp256k1.publickey_to_address(2, True, pnt))
print()

P_parsed = secp256k1.publickey_to_point('031cf3c12331b71866c1c5318f5ca47eedcb875a823218b5a39b070506ed55d204')
print(P_parsed.hex())

P_parsed2 = secp256k1.publickey_to_point('045cbdf0646e5db4eaa398f365f2ea7a0e3d419b7e0330e39ce92bddedcac4f9bc6aebca40ba255960a3178d6d861a54dba813d0b813fde7b5a5082628087264da')
print(P_parsed2.hex())

print(secp256k1.p2pkh_address_to_hash160('19HGKmF6Dv6FYJVg7T4KuaBi7gMQoKUtHF'))
print()

secp256k1.init_bloom(0, 1000000, 0.0000000001)
secp256k1.bloom_info(0)
val = "bloomCheck"
secp256k1.bloom_add(0, val)
if (secp256k1.bloom_check(0, val)):
    print(f'{val} is in the bloom')
else:
    print(f'{val} is not in the bloom')
secp256k1.bloom_save(0, "bloom_1.bf")
print()
   
secp256k1.bloom_load(1, "bloom_1.bf")
secp256k1.bloom_info(1)
if (secp256k1.bloom_check(1, val)):
    print(f'{val} is in the bloom')
else:
    print(f'{val} is not in the bloom')

Gp = secp256k1.scalar_multiplication(1)
print(f'Point_on_curve: {secp256k1.point_on_curve(Gp)}')
testP1 = secp256k1.add_points(Gp, Gp)
print(f'Point_on_curve: {secp256k1.point_on_curve(testP1)}')
testP2 = secp256k1.add_points_safe(Gp, Gp)
print(f'Point_on_curve: {secp256k1.point_on_curve(testP2)}')
print()
P0 = secp256k1.scalar_multiplication(0)
print(P0 == infinityP)
print(secp256k1.point_to_cpub(P0))
P01 = secp256k1.scalar_multiplication(1)
print(secp256k1.point_to_cpub(P01))
N = 0xfffffffffffffffffffffffffffffffebaaedce6af48a03bbfd25e8cd0364141
P02 = secp256k1.scalar_multiplication(115792089237316195423570985008687907852837564279074904382605163141518161494339 + N * 2)
print(secp256k1.point_to_cpub(P02))
print(secp256k1.hash160_to_address(0, False, '7f4c4db9be542f0231327db9fe3d47987c7dc69b'))

P_test = secp256k1.scalar_multiplication(57896044618658097711785492504343953926418782139537452191302581570759080747169)
print(secp256k1.point_to_cpub(P_test))
print(secp256k1.point_to_upub(P_test))
print()
Pn4 = secp256k1.scalar_multiplication(4)
Pn2 = secp256k1.point_division(Pn4, 2)
print(secp256k1.point_to_cpub(Pn2))
