/* argument.c */

#include <stdio.h>
#include <stdlib.h>

void dump(int *a, int n) {
    // WRONG: n = sizeof(a) / sizeof(int);
    for (size_t i = 0; i < n; i++) {
    	printf("%ld. %d\n", i, a[i]);
    }
}

int main(int argc, char *argv[]) {
    int a[]  = {5, 4, 7, 0, 1, 3, 13, 3, 15, 12, 24};
    size_t n = sizeof(a) / sizeof(int);

    dump(a, n);
    return EXIT_SUCCESS;
}
