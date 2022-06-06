//Reuben T. Chavez
//CSE 13s
//rsa.c

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

#include "rsa.h"
#include "numtheory.h"
#include "randstate.h"

gmp_randstate_t state;

// Calculates the lcm(a,b)
void lcm(mpz_t d, mpz_t a, mpz_t b) {
    //lcm(a,b) = |a * b|/gcd(a,b);

    mpz_t abs, div;
    mpz_inits(abs, div, NULL);

    mpz_mul(abs, a, b); // abs = a * b
    mpz_abs(abs, abs); //abs = |abs|

    gcd(div, a, b);

    mpz_divexact(d, abs, div); // return d = |a * b| / gcd(a,b)

    mpz_clears(abs, div, NULL);
    return;
}

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters) {

    mpz_t p_minus, p_bits, q_bits, q_minus, torient_n, lambda_n, num, test;
    mpz_inits(p_minus, p_bits, q_bits, q_minus, torient_n, lambda_n, num, test, NULL);

    uint64_t n_div_2 = nbits / 2;
    uint64_t n_div_4 = nbits / 4;

    make_prime(p_bits, nbits, iters); // pbits  = random_number
    mpz_mod_ui(p_bits, p_bits, n_div_2); // pbits = (random_num % nbits/2)
    mpz_add_ui(p_bits, p_bits, n_div_4); // pbits = (random_num % nbits/2) + nbits/4

    uint64_t pbits = mpz_get_ui(p_bits); // converts mpzt to unsigned interger
    uint64_t qbits = nbits - pbits; // qbits = nbits - pbits
    make_prime(q_bits, qbits, iters); // qbits = random_number

    mpz_set(p, p_bits); // p = p'
    mpz_set(q, q_bits); // q = q'
    mpz_mul(n, p, q); // n = p * q
    mpz_sub_ui(p_minus, p, 1); // p - 1
    mpz_sub_ui(q_minus, q, 1); // q - 1

    lcm(lambda_n, p_minus, q_minus); //lambda(n) = |a * b|/ gcd(a,b)

    // while the gcd(lambda(n), e) is not 1
    while (mpz_cmp_ui(test, 1) != 0) {
        mpz_urandomb(e, state, nbits);
        gcd(test, lambda_n, e); // test = gcd(lambda(n), e)
    }
    mpz_clears(p_minus, p_bits, q_bits, q_minus, torient_n, lambda_n, num, test, NULL);
    return;
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%ZX\n%ZX\n%ZX\n%Zs\n", n, e, s, username);
    return;
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%ZX\n%ZX\n%ZX\n%Zs\n", n, e, s, username);
    return;
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q) {

    mpz_t n, p_minus, q_minus, torient_n, num, lambda_n;
    mpz_inits(n, p_minus, q_minus, torient_n, num, lambda_n, NULL);

    mpz_sub_ui(p_minus, p, 1); // p_minus =  p - 1
    mpz_sub_ui(q_minus, q, 1); // q_minus = q - 1

    lcm(lambda_n, p_minus, q_minus);
    mod_inverse(d, e, lambda_n); // d = inverse of e modulo lambda(n)

    mpz_clears(n, p_minus, q_minus, torient_n, num, lambda_n, NULL);
    return;
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%ZX\n%ZX\n", n, d);
    return;
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%ZX\n%ZX\n", n, d);
    return;
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n) {
    pow_mod(c, m, e, n); // c = m^e mod n
    return;
}
// Refrences
// I attended Eugene's Lecture on 2/11/2022
void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e) {
    mpz_t c, m;
    mpz_inits(c, m);

    //Calculating size k
    uint8_t k = mpz_get_ui(n);
    k = (log(k) / log(2) - 1) / 8; //k = [(log2(n)−1)/8]

    //Create array that holds k bytes
    uint8_t *block = calloc(k, sizeof(uint8_t));
    block[0] = 0xFF; // setting zeroth byte to 0xFF

    // Read bytes from infile
    uint8_t *j = calloc(k, sizeof(uint8_t)); // read bits
    gmp_fscanf(infile, "%X\n", j);

    for (int i = 1; i < k; i += 1) {
        block[i] = j[i];
    }

    // turn array in mpzt
    mpz_import(m, k, 1, sizeof(uint8_t), 1, 0, block); // mpz_t m = block[k]

    //Write that mpz_t to a file as hexstring
    rsa_encrypt(c, m, e, n); // c = m^e mod n
    gmp_fprintf(outfile, "%X\n", c);

    //assert(mpz_cmp_ui(m, block) == 0);

    free(block);
    free(j);
    mpz_clears(c, m);
    return;
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n) {
    pow_mod(m, c, d, n); // m = c ^d mod n
    return;
}

void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d) {
    mpz_t c, m;
    mpz_inits(c, m, NULL);

    //Calculating size k
    uint8_t k = mpz_get_ui(n);
    k = (log(k) / log(2) - 1) / 8; //k = [(log2(n)−1)/8]

    //Create array that holds k bytes
    uint8_t *block = calloc(k, sizeof(uint8_t));

    //Scan hexstring as mpz_t c
    gmp_fscanf(infile, "%ZX\n", c);

    //Turn mpz_t to array
    mpz_export(block, NULL, 1, sizeof(uint8_t), 1, 0, c); // block[k] = mpzt c

    //Write that mpz_t to a file as hexstring
    rsa_decrypt(m, c, d, n); // m = c ^ d mod n
    gmp_fprintf(outfile, "%ZX\n", c);

    //assert(mpz_cmp_ui(c, block) == 0);

    free(block);
    mpz_clears(c, m, NULL);
    return;
}

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n) {
    pow_mod(s, m, d, n); // s = m^d mod n
    return;
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n) {
    mpz_t t;
    mpz_inits(t, NULL);
    pow_mod(t, s, e, n); // t = s^e mod n
    if (m == t) {
        mpz_clear(t);
        return true;
    }
    mpz_clears(t, NULL);

    return false;
}
