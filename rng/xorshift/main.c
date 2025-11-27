/*
A good and easy alternative to the flawed rand() procedures, is xorshift, a class of pseudo-random number
generators discovered by George Marsaglia. The xorshift generator is among the fastest non-cryptographically-
secure random number generators.
*/

#include <stdint.h>
#include <stdio.h>

/* These state variables must be initialised so that they are not all zero. */
uint32_t w, x, y, z;
uint32_t xorshift128(void)
{
    uint32_t t = x;
    t ^= t << 11U;
    t ^= t >> 8U;
    x = y; y = z; z = w;
    w ^= w >> 19U;
    w ^= t;
    return w;
}

int main() {
    w = 0;
    x = 5;
    y = 4;
    z = 1;
    printf("%d\n", xorshift128());
    printf("%d\n", xorshift128());
    printf("%d\n", xorshift128());
    printf("%d\n", xorshift128());
    return 0;
}
