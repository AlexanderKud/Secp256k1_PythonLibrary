#include <iostream>

#include "secp256k1/SECP256k1.h"
#include "secp256k1/Int.h"
#include "secp256k1/IntGroup.h"

extern "C" {
    
    Secp256K1* secp256k1 = new Secp256K1();
    
    void Init() {
        ::secp256k1->Init();
    }
    
    void check() {
        Int pk; 
        pk.SetInt32(1);
        Point P = ::secp256k1->ScalarMultiplication(&pk);
        std::cout << ::secp256k1->GetPublicKeyHex(P) << std::endl;
    }

}
