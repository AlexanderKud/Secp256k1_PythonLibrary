#include <iostream>

#include "secp256k1/SECP256k1.h"
#include "secp256k1/Int.h"
#include "secp256k1/IntGroup.h"
#include "bloom/Bloom.h"

extern "C" {
    
    Secp256K1* secp256k1 = new Secp256K1();
    Bloom bf[2];
    
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
    
    void scalar_multiplication(char* priv, unsigned char* publicKeyBytesOut) {
        Int pk;
        pk.SetBase10(priv);
        if (pk.IsZero()) {
            Point P;
            P.x.SetInt32(0);
            P.y.SetInt32(0);
            P.z.SetInt32(1);
            ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
        }
        else {
            Point P = ::secp256k1->ComputePublicKey(&pk);
            ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
        }        
    }
    
    void point_multiplication(unsigned char* publicKeyBytesIn, char* priv, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.z.SetInt32(1);
        Int pk;
        pk.SetBase10(priv);
        Point ret = ::secp256k1->PointMultiplication(P, &pk);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void point_to_upub(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
    }
    
    void point_to_cpub(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        ::secp256k1->GetPubKeyBytes(true, P, publicKeyBytesOut);
    }
    
    void double_point(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P = ::secp256k1->DoubleDirect(P);
        ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
    }
    
    void negate_point(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.y.ModNeg();
        ::secp256k1->GetPubKeyBytes(false, P, publicKeyBytesOut);
    }
    
    void add_points(unsigned char* publicKeyBytesIn1, unsigned char* publicKeyBytesIn2, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn1);
        Point Q = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn2);
        Point ret = ::secp256k1->AddPoints(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void add_points_safe(unsigned char* publicKeyBytesIn1, unsigned char* publicKeyBytesIn2, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn1);
        P.z.SetInt32(1);
        Point Q = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn2);
        Q.z.SetInt32(1);
        Point ret = ::secp256k1->AddPoints2(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void add_point_scalar(unsigned char* publicKeyBytesIn, char* priv, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        Int pk;
        pk.SetBase10(priv);
        Point Q = ::secp256k1->ComputePublicKey(&pk);
        Point ret = ::secp256k1->AddPoints(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void add_point_scalar_safe(unsigned char* publicKeyBytesIn, char* priv, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.z.SetInt32(1);
        Int pk;
        pk.SetBase10(priv);
        Point Q = ::secp256k1->ComputePublicKey(&pk);
        Point ret = ::secp256k1->AddPoints2(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void subtract_points(unsigned char* publicKeyBytesIn1, unsigned char* publicKeyBytesIn2, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn1);
        Point Q = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn2);
        Point ret = ::secp256k1->SubtractPoints(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void subtract_points_safe(unsigned char* publicKeyBytesIn1, unsigned char* publicKeyBytesIn2, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn1);
        P.z.SetInt32(1);
        Point Q = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn2);
        Q.z.SetInt32(1);
        Point ret = ::secp256k1->SubtractPoints2(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void subtract_point_scalar(unsigned char* publicKeyBytesIn, char* priv, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        Int pk;
        pk.SetBase10(priv);
        Point Q = ::secp256k1->ComputePublicKey(&pk);
        Point ret = ::secp256k1->SubtractPoints(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void subtract_point_scalar_safe(unsigned char* publicKeyBytesIn, char* priv, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.z.SetInt32(1);
        Int pk;
        pk.SetBase10(priv);
        Point Q = ::secp256k1->ComputePublicKey(&pk);
        Point ret = ::secp256k1->SubtractPoints2(P, Q);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void increment_point(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.z.SetInt32(1);
        Point ret = ::secp256k1->AddPoints2(P, ::secp256k1->G);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void decrement_point(unsigned char* publicKeyBytesIn, unsigned char* publicKeyBytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        P.z.SetInt32(1);
        Point ret = ::secp256k1->SubtractPoints2(P, ::secp256k1->G);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    bool point_on_curve(unsigned char* publicKeyBytesIn) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        return ::secp256k1->EC(P);
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
    
    void privatekey_to_uwif(char* priv, unsigned char* BytesOut) {
        Int pk;
        pk.SetBase10(priv);
        std::string wif = ::secp256k1->GetPrivAddress(false, pk);
        for(int i = 0; i < wif.size(); i++) {
            BytesOut[i] = wif[i];
        }
    }
    
    void privatekey_to_cwif(char* priv, unsigned char* BytesOut) {
        Int pk;
        pk.SetBase10(priv);
        std::string wif = ::secp256k1->GetPrivAddress(true, pk);
        for(int i = 0; i < wif.size(); i++) {
            BytesOut[i] = wif[i];
        }
    }
    
    void privatekey_to_wif(bool compressed, char* priv, unsigned char* BytesOut) {
        Int pk;
        pk.SetBase10(priv);
        std::string wif = ::secp256k1->GetPrivAddress(compressed, pk);
        for(int i = 0; i < wif.size(); i++) {
            BytesOut[i] = wif[i];
        }
    }
    
    void wif_to_privatekey(char* wif, unsigned char* BytesOut) {
        Int pk = Secp256K1::DecodePrivateKey2(wif);
        pk.Get32Bytes(BytesOut);
    }
    
    void privatekey_to_address(int type, bool compressed, char* priv, unsigned char* BytesOut) {
        Int pk;
        pk.SetBase10(priv);
        Point P = ::secp256k1->ComputePublicKey(&pk);
        std::string address = ::secp256k1->GetAddress(type, compressed, P);
        for(int i = 0; i < address.size(); i++) {
            BytesOut[i] = address[i];
        }
    }
    
    void publickey_to_address(int type, bool compressed, unsigned char* publicKeyBytesIn, unsigned char* BytesOut) {
        Point P = ::secp256k1->SetPubKeyBytes(publicKeyBytesIn);
        std::string address = ::secp256k1->GetAddress(type, compressed, P);
        for(int i = 0; i < address.size(); i++) {
            BytesOut[i] = address[i];
        }
    }
    
    void hash160_to_address(int type, bool compressed, unsigned char* hash160, unsigned char* BytesOut) {
        std::string address = ::secp256k1->GetAddress(type, compressed, hash160);
        for(int i = 0; i < address.size(); i++) {
            BytesOut[i] = address[i];
        }
    }
    
    void publickey_to_point(char* publicKey, unsigned char* publicKeyBytesOut) {
        Point ret = ::secp256k1->ParsePublicKeyHex2(publicKey);
        ::secp256k1->GetPubKeyBytes(false, ret, publicKeyBytesOut);
    }
    
    void p2pkh_address_to_hash160(char* address, unsigned char* BytesOut) {
        std::string hash160 = ::secp256k1->GetHashFromP2PKHAddress(address);
        for(int i = 0; i < hash160.size(); i++) {
            BytesOut[i] = hash160[i];
        }
    }
    
    void init_bloom(int arrayIndex, unsigned long long entries, double error) {
        ::bf[arrayIndex].init_bloom(entries, error);
    }

    void bloom_info(int arrayIndex) {
        ::bf[arrayIndex].print();
    }
    
    void bloom_save(int arrayIndex, char* filename) {
        ::bf[arrayIndex].save(filename);
    }
    
    void bloom_load(int arrayIndex, char* filename) {
        ::bf[arrayIndex].load(filename);
    }
    
    void bloom_add(int arrayIndex, char* item, int len) {
        ::bf[arrayIndex].add(item, len);
    }
    
    int bloom_check(int arrayIndex, char* item, int len) {
        int in_bloom = ::bf[arrayIndex].check(item, len);
        return in_bloom;
    }
      
}
