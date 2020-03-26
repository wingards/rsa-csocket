#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <bitset>
#include <string>
#include <string.h>
#include <time.h>

const int MIN_PRIME = 2;
const int BYTE = 8;
const int MAX_RAND = 32767;

typedef unsigned long long Uint64_t;
typedef unsigned long int Uint32_t;

Uint32_t Rand(Uint32_t min);

bool isPrime(Uint32_t num);

void get_primes(Uint32_t *p, Uint32_t *q, Uint32_t min);

Uint32_t gcd(Uint32_t p, Uint32_t q);

Uint32_t get_public(Uint32_t t/*get totient*/, Uint32_t min);

void euclidean_swap(Uint64_t *new_val, Uint64_t *old_val, Uint64_t quotient);

Uint32_t get_private(Uint32_t exp_pub, Uint32_t t);

void get_keys(Uint32_t *pub, Uint32_t *priv, Uint32_t *prod);

Uint32_t modPow(Uint32_t sum, Uint32_t pub, Uint32_t prod);

Uint32_t encrypt(char* str, char* cipher, Uint32_t pub, Uint32_t prod);

Uint32_t get_val(char* str, int start, int len);

Uint32_t decrypt(char* cipher, char* str, Uint32_t pri, Uint32_t prod);

