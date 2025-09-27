#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H


class Bloom
{
public:
    Bloom();
    //Bloom(unsigned long long int entries, double error);
    ~Bloom();
    int check(const void *buffer, int len);
    int add(const void *buffer, int len);
    void print();
    int reset();
    int save(const char *filename);
    int load(const char *filename);
    void init_bloom(unsigned long long int entries, double error);

    int get_hashes();
    unsigned long long int get_bits();
    unsigned long long int get_bytes();
    const unsigned char *get_bf();

private:
    static unsigned int murmurhash2(const void *key, int len, const unsigned int seed);
    int test_bit_set_bit(unsigned char *buf, unsigned int bit, int set_bit);
    int bloom_check_add(const void *buffer, int len, int add);

private:
    unsigned long long int _entries;
    unsigned long long int _bits;
    unsigned long long int _bytes;
    int _hashes;
    double _error;
    int _ready;
    double _bpe;
    unsigned char *_bf;

};

#endif // BLOOMFILTER_H
