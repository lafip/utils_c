#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <gmp.h>



long inversel(long a, long mod){
    /*
     * inversio a by modulo m, if m is prime
     * using Euler's theorem a^-1 = a^(M-2) mod M
     * if a = 0 or a =m  returning -1
     */

    long res = 1;
    long exp = mod - 2;
    a %= mod;
    while (exp != 0) {
        if (exp & 1) res = (res * a) % mod;
        exp >>= 1;
        a = (a * a) % mod;
    }
    return res;
}

long long chremgarnerll(unsigned int k, long *m, long *a){
    /*
     * Chines remainder, method of Garner
     * k - number 
     * m - modules, primes
     * a - value
     */
    int i;
    long b=1;
    long d;
    long x;
    if (k < 1) return 0;
    long long s = a[0];
    for(i=2; i<=k; i++){
        b *= m[i-2];
        d = inversel(b, m[i-1]);
        x = d * (a[i-1] - s) % m[i-1];
        s += x * b;
    }
    return s;
}

int mpz_chremgarner(mpz_t s, unsigned int k, mpz_t *m, mpz_t *a){
    int i;
    mpz_t b, d, x;
    if (k < 1) return -1;
    mpz_inits(b, d, x, NULL);
    mpz_set(s, a[0]);
    mpz_set_si(b, 1);
    for(i=2; i<=k; i++){
        mpz_mul(b, b, m[i-2]);
        mpz_invert(d, b, m[i-1]);
        mpz_sub(x, a[i-1], s);
        mpz_mul(x, x, d);
        mpz_mod(x, x, m[i-1]);
        mpz_addmul(s, x, b);
    }
    mpz_clears(b, d, x, NULL);
    return 1;
}


int main(){
    // assert(invert2exp(192, 1301) == 454);
    // printf("%lu\n", inversel(192, 1301));
    int i;
    long m[2] = {3, 5};
    long a[2] = {1, 4};
    long res = chremgarnerll(2, m, a);
    printf("%ld\n", res);
    
    mpz_t rz;
    mpz_init(rz);
    mpz_t mz[2];
    mpz_t az[2];
    for (i=0; i<2; i++){
        mpz_inits(mz[i], az[i], NULL);
    }
    
    mpz_set_si(mz[0], 112909);
    mpz_set_si(mz[1], 614657);
    mpz_set_si(az[0], 1);
    mpz_set_si(az[1], -1);
    
    mpz_chremgarner(rz, 2, mz, az);
    
    gmp_printf("%Zd \n", rz);
    mpz_clear(rz);
    for (i=0; i<2; i++){
        mpz_clears(mz[i], az[i], NULL);
    }
    puts("passed");
}
