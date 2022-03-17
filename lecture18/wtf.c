/* wtf.c */

#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    unsigned pos_one =  1;
    int      neg_one = -1;

    /* When mixing signed and unsigned, the signed int is treated as
     * unsigned.*/
    if (pos_one < neg_one)  // Fix with a cast
        puts("wtf!");
    else
        puts("obv!");

    /* When mixing integers of different sizes, the smaller one gets promoted
     * to the larger one */
    int16_t count = 0x7ff0;
    printf("count:   %hd\n", count);
    printf("literal: %d\n", 0x8001);
    printf("literal: %hd\n", (short)0x8001);
    while (count < 0x8001) {    // This is promoted to signed int
        count += 1;             // We overflow
        printf("%hd\n", count);
    }
    // Fix 1: Change int16_t count to uint64_t count
    // Fix 2: Change (count < 0x8001) to (count < 0x8001U)

    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
