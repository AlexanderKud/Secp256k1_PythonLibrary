default:
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O2 -c secp256k1/Int.cpp -o Int.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O2 -c secp256k1/Point.cpp -o Point.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O2 -c secp256k1/SECP256K1.cpp -o SECP256K1.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O2 -c secp256k1/IntMod.cpp -o IntMod.o
	g++ -fPIC -m64 -mssse3 -Wno-write-strings -O2 -c secp256k1/IntGroup.cpp -o IntGroup.o
	g++ -fPIC -shared -m64 -O2 -o secp256k1_lib.so secp256k1_lib.cpp SECP256K1.o Int.o IntGroup.o IntMod.o Point.o -lgmp 
	rm *.o
