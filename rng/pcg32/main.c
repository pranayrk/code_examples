/*
   This code is (minimal) PCG32 from pcg-random.org, a modern, fast, general-purpose RNG with excellent statistical properties.
   It's not cryptographically secure, so don't use it for cryptography.
   */

#include <stdint.h>
#include <stdio.h>

typedef struct { 
    uint64_t state; 
    uint64_t inc; 
} pcg32_random_t;

uint32_t pcg32_random_r(pcg32_random_t* rng) {
    uint64_t oldstate = rng->state;
    /* Advance internal state */
    rng->state = oldstate * 6364136223846793005ULL + (rng->inc | 1);
    /* Calculate output function (XSH RR), uses old state for max ILP */
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq) {
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

int main(void) {
    pcg32_random_t rng; /* RNG state */
    int i;
    /* Seed the RNG */
    pcg32_srandom_r(&rng, 42u, 54u);
    /* Print some random 32-bit integers */
    for (i = 0; i < 6; i++)
        printf("0x%08x\n", pcg32_random_r(&rng));
    return 0;
}
