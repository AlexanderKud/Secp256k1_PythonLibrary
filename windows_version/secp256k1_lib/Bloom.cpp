#include <stdio.h>
#include <iostream>
#include <math.h>
#include <string.h>
#include <fcntl.h>

#include "Bloom.h"

Bloom::Bloom()
{
    _ready = 0;
    _entries = 1000000;
    _error = 0.00001;

    long double num = -log(_error);
    long double denom = 0.480453013918201; // ln(2)^2
    _bpe = (num / denom);

    long double dentries = (long double)_entries;
    long double allbits = dentries * _bpe;
    _bits = (unsigned long long int)allbits;

    if (_bits % 8) {
        _bytes = (unsigned long long int)(_bits / 8) + 1;
    } else {
        _bytes = (unsigned long long int) _bits / 8;
    }

    _hashes = (int)ceil(0.693147180559945 * _bpe);  // ln(2)
    
    _bf = (unsigned char *)calloc(_bytes, sizeof(unsigned char));
    if (_bf == NULL) {
        printf("Bloom init error\n");
        return;
    }
    
    _ready = 1;

}

void Bloom::init_bloom(unsigned long long entries, double error)
{
    _ready = 0;
    if (entries < 1000 || error <= 0 || error >= 1) {
        printf("Bloom init error\n");
        return;
    }

    _entries = entries;
    _error = error;

    long double num = -log(_error);
    long double denom = 0.480453013918201; // ln(2)^2
    _bpe = (num / denom);

    long double dentries = (long double)_entries;
    long double allbits = dentries * _bpe;
    _bits = (unsigned long long int)allbits;

    if (_bits % 8) {
        _bytes = (unsigned long long int)(_bits / 8) + 1;
    } else {
        _bytes = (unsigned long long int) _bits / 8;
    }

    _hashes = (int)ceil(0.693147180559945 * _bpe);  // ln(2)

    _bf = (unsigned char *)calloc(_bytes, sizeof(unsigned char));
    if (_bf == NULL) {
        printf("Bloom init error\n");
        return;
    }

    _ready = 1;

}

Bloom::~Bloom()
{
    if (_ready) free(_bf);
}

int Bloom::check(const void *buffer, int len)
{
    return bloom_check_add(buffer, len, 0);
}


int Bloom::add(const void *buffer, int len)
{
    return bloom_check_add(buffer, len, 1);
}

void Bloom::print()
{
    printf("Bloom at %p\n", (void *)this);
    if (!_ready) {
        printf(" *** NOT READY ***\n");
    }
    printf("  Entries    : %llu\n", _entries);
    printf("  Error      : %1.10f\n", _error);
    printf("  Bits       : %llu\n", _bits);
    printf("  Bits/Elem  : %f\n", _bpe);
    printf("  Bytes      : %llu", _bytes);
    unsigned int KB = (unsigned int)_bytes / 1024;
    unsigned int MB = KB / 1024;
    //printf(" (%u KB, %u MB)\n", KB, MB);
    printf(" (%u MB)\n", MB);
    printf("  Hash funcs : %d\n", _hashes);
}


int Bloom::reset()
{
    if (!_ready) return 1;
    memset(_bf, 0, _bytes);
    return 0;
}

int Bloom::save(const char *filename)
{
    if (!_ready || filename == nullptr || filename[0] == '\0') {
        return 1;
    }
    
    FILE *filePtr = fopen(filename, "wb");
    if (filePtr == NULL) {
        return 1;
    }
    // header struct
    struct {
        unsigned short int header_size;
        unsigned long long int entries;
        double error;
        double bpe;
        unsigned long long int bits;
        unsigned long long int bytes;
        int hashes;
    } header;

    header.header_size = sizeof(header);
    header.entries = _entries;
    header.error = _error;
    header.bpe = _bpe;
    header.bits = _bits;
    header.bytes = _bytes;
    header.hashes = _hashes;
    
    // write header struct
    size_t written = fwrite(&header, sizeof(header), 1, filePtr);
    if (written != size_t(1)) {
        printf("Error writing header\n");
        fclose(filePtr);
        return 1;
    }

    // write byte array
    size_t res = fwrite(_bf, sizeof(unsigned char), _bytes, filePtr);
    if(res != _bytes) {
        printf("Error writing bytes\n");
        fclose(filePtr);
        return 1;
    }

    fclose(filePtr);
    return 0;
}

int Bloom::load(const char *filename)
{
    if (filename == nullptr || filename[0] == '\0') {
        return 1;
    }

    FILE *filePtr = fopen(filename, "rb");
    if (filePtr == NULL) {
        return 1;
    }

    // Read and verify header
    struct {
        unsigned short int header_size;
        unsigned long long int entries;
        double error;
        double bpe;
        unsigned long long int bits;
        unsigned long long int bytes;
        int hashes;
    } header;

    size_t hres = fread(&header, sizeof(header), 1, filePtr);
    if (hres != size_t(1)) {
        printf("Error reading header from file\n");
        fclose(filePtr);
        return 1;
    }

    // free existing filter if it exists
    if (_ready) {
        free(_bf);
        _ready = 0;
     }

    // initialize with loaded parameters
    _entries = header.entries;
    _error = header.error;
    _bpe = header.bpe;
    _bits = header.bits;
    _bytes = header.bytes;
    _hashes = header.hashes;

    // allocate byte array
    _bf = (unsigned char *)malloc(_bytes);
    if (_bf == nullptr) {
        printf("Memory Allocation error\n");
        fclose(filePtr);
        return 1;
    }

    // read byte array
    if (fread(_bf, sizeof(unsigned char), _bytes, filePtr) != _bytes) {
        printf("Bytes read error\n");
        free(_bf);
        _bf = nullptr;
        fclose(filePtr);
        return 1;
    }

    _ready = 1;
    fclose(filePtr);
    return 0;
}

int Bloom::get_hashes()
{
    return _hashes;
}

unsigned long long int Bloom::get_bits()
{
    return _bits;
}

unsigned long long int Bloom::get_bytes()
{
    return _bytes;
}

const unsigned char *Bloom::get_bf()
{
    return _bf;
}

int Bloom::test_bit_set_bit(unsigned char *buf, unsigned int bit, int set_bit)
{
    unsigned int byte = bit >> 3;
    unsigned char c = buf[byte];        // expensive memory access
    unsigned char mask = 1 << (bit % 8);

    if (c & mask) {
        return 1;
    } else {
        if (set_bit) {
            buf[byte] = c | mask;
        }
        return 0;
    }
}

int Bloom::bloom_check_add(const void *buffer, int len, int add)
{
    /*
    if (_ready == 0) {
        printf("bloom not initialized!\n");
        return -1;
    }*/

    unsigned char hits = 0;
    unsigned int a = murmurhash2(buffer, len, 0x9747b28c);
    unsigned int b = murmurhash2(buffer, len, a);
    unsigned int x;
    unsigned char i;

    for (i = 0; i < _hashes; i++) {
        x = (a + b * i) % _bits;
        if (test_bit_set_bit(_bf, x, add)) {
            hits++;
        } else if (!add) {
            // Don't care about the presence of all the bits. Just our own.
            return 0;
        }
    }

    if (hits == _hashes) {
        return 1;                // 1 == element already in (or collision)
    }

    return 0;
}

// MurmurHash2, by Austin Appleby

// Note - This code makes a few assumptions about how your machine behaves -

// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4

// And it has a few limitations -

// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.
unsigned int Bloom::murmurhash2(const void *key, int len, const unsigned int seed)
{
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const unsigned int m = 0x5bd1e995;
    const int r = 24;

    // Initialize the hash to a 'random' value

    unsigned int h = seed ^ len;

    // Mix 4 bytes at a time into the hash

    const unsigned char *data = (const unsigned char *)key;

    while (len >= 4) {
        unsigned int k = *(unsigned int *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    // Handle the last few bytes of the input array

    switch (len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0];
        h *= m;
    };

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}
