import secp256k1
import timeit
'''
pk = 57896044618658097711785492504343953926418782139537452191302581570759080747169
G = secp256k1.scalar_multiplication(pk)
G_bytes_x = G[1:33]
G_bytes_y = G[33:]
print(G)
print(G_bytes_x.hex())
print(G_bytes_y.hex())
'''
#P = secp256k1.scalar_multiplication(4)
#for i in range(2**20):
    #P = secp256k1.scalar_multiplication(4)
    #cpub = secp256k1.point_to_cpub(P)

def test_func():
    P = secp256k1.scalar_multiplication(4)
    #cpub = '035cbdf0646e5db4eaa398f365f2ea7a0e3d419b7e0330e39ce92bddedcac4f9bc'
    #address = '1LagHJk2FyCV2VzrNHVqg3gYG4TSYwDV4m'
    #wif ='5HpHagT65TZzG1PH3CSu63k8DbpvD8s5ip4nEB3kEsreAvUcVfH'
    for i in range(2**16):
        P = secp256k1.point_division2(P, 2)
        #print(hash160)
    
print("test_func:", timeit.timeit(test_func, number=1))

#print(secp256k1.point_to_cpub(P))
#Q = secp256k1.point_division(P, 2)
#print(secp256k1.point_to_cpub(Q))
#cpub = '035cbdf0646e5db4eaa398f365f2ea7a0e3d419b7e0330e39ce92bddedcac4f9bc'
#print(cpub[:2])
