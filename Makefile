default:
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/Int.cpp -o Int.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/Point.cpp -o Point.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/IntMod.cpp -o IntMod.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/Random.cpp -o Random.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c base58/Base58.cpp -o Base58.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c bech32/Bech32.cpp -o Bech32.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c hash/ripemd160.cpp -o ripemd160.o 
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c hash/sha256.cpp -o sha256.o 
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c hash/ripemd160_sse.cpp -o ripemd160_sse.o 
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c hash/sha256_sse.cpp -o sha256_sse.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O1 -c bloom/Bloom.cpp -o bloom.o
	g++ -fPIC -shared -Wno-write-strings -o secp256k1_lib.so secp256k1_lib.cpp bloom.o Base58.o Bech32.o SECP256K1.o Int.o IntGroup.o IntMod.o Point.o Random.o ripemd160.o ripemd160_sse.o sha256.o sha256_sse.o
	rm *.o
