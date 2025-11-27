/*
The function rand() can be used to generate a pseudo-random integer value between 0 and RAND_MAX (0 and
RAND_MAX included).
srand(int) is used to seed the pseudo-random number generator. Each time rand() is seeded wih the same seed,
it must produce the same sequence of values. It should only be seeded once before calling rand(). It should not be
repeatedly seeded, or reseeded every time you wish to generate a new batch of pseudo-random numbers.
Standard practice is to use the result of time(NULL) as a seed. If your random number generator requires to have a
deterministic sequence, you can seed the generator with the same value on each program start. This is generally
not required for release code, but is useful in debug runs to make bugs reproducible.
It is advised to always seed the generator, if not seeded, it behaves as if it was seeded with srand(1).

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
    int i;
    srand(time(NULL));
    i = rand();
    printf("Random value between [0, %d]: %d\n", RAND_MAX, i);
    return 0;
}
