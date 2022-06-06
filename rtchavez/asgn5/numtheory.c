//Reuben T. Chavez
//CSE 13s
//numtheory.c

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <gmp.h>

#include "numtheory.h"
#include "randstate.h"

gmp_randstate_t state;

void gcd(mpz_t d, mpz_t a, mpz_t b) {
    mpz_t t;
    //while(b != 0){...}
    while (mpz_cmp_ui(b, 0) != 0) {
        mpz_init_set(t, b); // t = b
        mpz_mod(b, a, b); // b = a % b
        mpz_set(a, t); // a = t
    }
    mpz_set(d, a); // return a
    mpz_clears(t, NULL);
    return;
}

void mod_inverse(mpz_t i, mpz_t a, mpz_t n) {
    mpz_t r, rp, t, tp, q, temp_t, temp_r;
    mpz_inits(r, rp, t, tp, q, temp_t, temp_r, NULL);

    mpz_set(r, n); //r = n
    mpz_set(rp, a); // r' = a
    mpz_set_ui(t, 0); // t = 0
    mpz_set_ui(tp, 1); // t' = 1

    //while r' != 0 {...}
    while (mpz_cmp_ui(rp, 0) != 0) {

        mpz_tdiv_q(q, r, rp); // q = r / r'

        mpz_set(temp_r, r); // temp_r = r

        mpz_set(r, rp); // r = r'

        mpz_mul(rp, q, rp); // r' = q * r
        mpz_sub(rp, temp_r, rp); // r' = r - q * r

        mpz_set(temp_t, t); // temp_t - t

        mpz_set(t, tp); // t = t'

        mpz_mul(tp, q, tp); // t' = q * t'
        mpz_sub(tp, temp_t, tp); // t' = t - q * t'
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set_ui(i, 0);
        mpz_clears(r, rp, t, tp, q, temp_t, temp_r, NULL);
        return;
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n); // t += n
    }
    mpz_set(i, t); // return t
    mpz_clears(r, rp, t, tp, q, temp_t, temp_r, NULL);

    return;
}

void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus) {
    mpz_t v, p;
    mpz_inits(v, p, NULL);

    mpz_set_ui(v, 1); // v = 1
    mpz_set(p, base); // p = base

    //while( exponent > 0){...}
    while (mpz_cmp_ui(exponent, 0) > 0) {
        // if(exponent is odd){...}
        if (mpz_odd_p(exponent)) {
            mpz_mul(v, v, p); // v *= p
            mpz_mod(v, v, modulus); // v *p % modulus
        }

        mpz_mul(p, p, p); // p *= p
        mpz_mod(p, p, modulus); // p^2 % modulus
        mpz_div_2exp(exponent, exponent, 1); //exponet >> 1
        //mpz_divexact(exponent, exponent, two);
    }

    mpz_set(out, v); // return v
    mpz_clears(v, p, NULL);

    return;
}
//Refrences:
// Attended Brian Zhou's meeting on 2-9-22
bool is_prime(mpz_t n, uint64_t iters) {
    mpz_t r, s, a, y, j, n_sub_1, n_sub_2, s_sub_1, two, m;

    mpz_inits(r, s, a, y, j, n_sub_1, n_sub_2, s_sub_1, two, m, NULL);

    mpz_sub_ui(n_sub_1, n, 1); //n_sub_1 = n - 1
    mpz_set(r, n_sub_1); // n_sub_1 = n - 1
    mpz_set_ui(two, 2);

    mpz_sub_ui(n_sub_2, n, 2);

    if (mpz_cmp_ui(r, 0) <= 0) {
        mpz_set_ui(r, 0);
        mpz_set(r, n_sub_1);
    }
    // write n-1 = 2^s
    while (mpz_even_p(r)) {

        //printf("In while Loop\n");
        mpz_fdiv_q_2exp(r, r, 1); // r >> 1
        mpz_add_ui(s, s, 1); // s += 1
    }

    mpz_sub_ui(s_sub_1, s, 1); // s_sub_s = s - 1

    // for(int i = 1; i < iters; i+= 1 ){...}
    for (uint64_t i = 1; i < iters; i++) {

        mpz_urandomm(a, state, n_sub_1); //a = randomnumber{2,3,...,n-2}
        pow_mod(y, a, r, n); // y = pow_mod(a,r,n)
        //mpz_powm(y, a, r, n);

        gmp_printf("%Zd ^ %Zd mod %Zd y = %Zd  m = %Zd \n", a, r, n, y, m);

        //assert(mpz_cmp(y,m) == 0);
        //if(y != 1 and y != n-1){...}
        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_sub_1) != 0) {

            mpz_set_ui(j, 1); // j = 1

            // while(j < s -1 and y != n-1){...}
            while (mpz_cmp(j, s_sub_1) <= 0 && mpz_cmp(y, n_sub_1) != 0) {
                //mpz_powm(y,y,two,n);
                pow_mod(y, y, two, n); // y = pow_mod(y,2,n)
                if (mpz_cmp_ui(y, 1) == 0) {
                    return false;
                }
                mpz_add_ui(j, j, 1); // j += 1
            }
            if (mpz_cmp(y, n_sub_1) != 0) {
                return false;
            }
        }
    }
    mpz_clears(r, s, a, y, j, n_sub_1, n_sub_2, s_sub_1, two, m, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_t temp;
    mpz_init2(temp, bits);

    // while( temp is not prime number){...}
    while (!is_prime(temp, iters)) {

        mpz_urandomb(temp, state, bits); // temp = randomnumber{0 ... 2^n -1}
    }

    mpz_set(p, temp); // return p

    mpz_clears(temp, NULL);
    return;
}
