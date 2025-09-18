#include <iostream>
#include <cstring>

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
    
    void privatekey_to_hash160(int type, bool compressed, char* priv, unsigned char* BytesOut) {
        Int pk;
        pk.SetBase10(priv);
        Point P = ::secp256k1->ComputePublicKey(&pk);
        ::secp256k1->GetHash160(type, compressed, P, BytesOut);
    }
    
    void publickey_to_hash160(int type, bool compressed, unsigned char* publicKeyBytesIn, unsigned char* BytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        ::secp256k1->GetHash160(type, compressed, P, BytesOut);
    }

}
