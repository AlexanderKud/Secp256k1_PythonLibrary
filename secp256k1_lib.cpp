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
        Point P = ::secp256k1->ComputePublicKey(&pk);
        std::cout << ::secp256k1->GetPublicKeyHex(false, P) << std::endl;
        std::cout << ::secp256k1->GetPublicKeyHex(true, P) << std::endl;
    }
    
    void scalar_multiplication(char* priv, unsigned char* publicKeyBytesIn) {
        Int pk;
        pk.SetBase10(priv);
        Point P = ::secp256k1->ComputePublicKey(&pk);
        ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesIn);
    }
    
    void point_to_upub(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
    }
    
    void point_to_cpub(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        ::secp256k1->GetPubKeyBytes(true, P, publicKeyBytesOut);
    }
    /*
    const char* ret_str() {
        const char *str = "0479be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8";
        return str;
    }
    
    void get_int(char* i) {
        Int pvk;
        pvk.SetBase10(i);
        std::cout << pvk.GetBase10() << std::endl;
    }
    
    const char* get_int2() {
        Int pvk;
        char* key = "ff";
        pvk.SetBase16(key);
        return pvk.GetBase10().c_str();
    }
    */
}
