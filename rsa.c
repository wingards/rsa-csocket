#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>
#include <bitset>
#include <string>
#include <string.h>
#include "rsa.h"

#ifdef Boolean
typedef enum{
    true = (1==1),false = (1==0)
}bool;
#endif

Uint32_t Rand(Uint32_t min){
    return rand() % (MAX_RAND - min + 1) + min;
}

bool isPrime(Uint32_t num){
    Uint32_t i, half = num/2;
    if(num < MIN_PRIME)
      return true;
    for(i = MIN_PRIME; i<=half; ++i)
      if(num%i == 0) return false;

    return true;
}

void get_primes(Uint32_t *p, Uint32_t *q, Uint32_t min){
    
    do{
      do{
        *p = Rand(min);
      }while(!isPrime(*p));

      do{
        *q = Rand(min);
      }while(!isPrime(*q));
    }while(*p == *q);

}

Uint32_t gcd(Uint32_t p, Uint32_t q){
    
    Uint32_t tmp;

    while( q > 0 ){
      tmp = p % q;
      p = q;
      q = tmp;
    }
    return p;
}

Uint32_t get_public(Uint32_t t/*get totient*/, Uint32_t min){
    
    Uint32_t pub_exp;
    
    do{
      pub_exp = (Uint32_t)Rand(0)%(t - min) + min; 
    }while(gcd(pub_exp, t) != 1 || !isPrime(pub_exp));

    return pub_exp;
}

void euclidean_swap(Uint64_t *new_val, Uint64_t *old_val, Uint64_t quotient) 
{                                 
	Uint64_t actual_val = *new_val;
	
	// r(i+1) = r(i-1) - q(i) * r(i)                
	*new_val = *old_val - quotient * actual_val;  
	*old_val = actual_val;                        
}

Uint32_t get_private(Uint32_t exp_pub, Uint32_t t)
{
	// x(1) = 1, x(0) = 0, y(1) = public exponent, y(0) = fi 
	Uint64_t xx = 1, yy = exp_pub, x = 0, y = t, Uint32_t_quotient;

	// while y(i) > 0     
	while (yy > 0) {

		// q(i) = y(i-1)/y(i)
		Uint32_t_quotient = y/yy;

		// x(i+1) = x(i-1) - q(i) * x(i)
		euclidean_swap(&xx, &x, Uint32_t_quotient);
		
		// y(i+1) = y(i-1) - q(i) * y(i)
		euclidean_swap(&yy, &y, Uint32_t_quotient);
	}
	return x; // return the value of x(k) when y(k+1) is equal to zero
}

void get_keys(Uint32_t *pub, Uint32_t *priv, Uint32_t *prod){

    Uint32_t p,q,t;
    Uint64_t tmp_priv;

    do{
      get_primes(&p,&q, MIN_PRIME);
      *prod = p * q;
      t = (p - 1) * (q - 1);
      *pub = get_public(t, MIN_PRIME);
      tmp_priv = get_private(*pub, t);
    }while(tmp_priv >= t);

    *priv = (Uint32_t)tmp_priv;
}

Uint32_t modPow(Uint32_t sum, Uint32_t pub, Uint32_t prod){
    
    if(pub == 0) return 1;
    else if(pub == 1) return sum;

    Uint64_t p2 = pub / 2, sp2, sp, spN;
    sp2 = modPow(sum, p2, prod);
    spN = ((sp2 % prod) * (sp2 % prod)) % prod;
//    printf("spN = %llu\n", spN);
    if(pub % 2 == 1)
      return (spN * sum) % prod;
    else
      return spN;
    
}

Uint32_t encrypt(char* str, char* cipher, Uint32_t pub, Uint32_t prod){

    int val;
    Uint32_t len = strlen(str);
    char buf[64];
    memset(cipher , 0, strlen(cipher)); 
    for(int i = 0; i < len ; ++i){
      
      std::bitset<16> x = str[i];
//      printf("%c is covert to %lu\n", str[i], x.to_ulong());
      val =  (int)modPow((Uint32_t)x.to_ulong(), pub, prod);
//      printf("%c convert to %d\n", str[i], val);
      sprintf(buf, "%010d", val);
      strncat(cipher, buf, strlen(buf));
    } 
    return strlen(cipher);

}

Uint32_t get_val(char* str, int start, int len){

    Uint32_t val = 0;
    for(int i = start; i < start + len &&  i < strlen(str) ; ++i){
      val = val * 10 + str[i] - '0';
    }
    return val;
}

Uint32_t decrypt(char* cipher, char* str, Uint32_t pri, Uint32_t prod){


    Uint32_t len = strlen(cipher) / 10, val;
    
    for(int i = 0; i < len; ++i){
      
      val = get_val(cipher, i * 10, 10);
      val = modPow(val, pri, prod);
      
      sprintf(str, "%s%c", str, (char)val);
    }
    return strlen(str);
}

int main(){

    Uint32_t pub, priv, prod,test = 213;
    char str[1024],ciph[1024];
    memset(ciph, 0, 1024);
    printf("Input:\n");
    fgets(str, sizeof(str), stdin);
    get_keys(&pub, &priv, &prod);
    printf("pub = %lu,priv = %lu,\n" ,pub, priv);
    printf("input:%s\n", str);
    printf("output:%s\n", ciph);
    encrypt(str, ciph, pub, prod);
    printf("encrypt:%s\n", ciph);
    memset(str, 0, 1024);
    decrypt(ciph, str, priv, prod);
    printf("decrypt:%s\n,", str);
}


