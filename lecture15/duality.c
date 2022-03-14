/* duality.c */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int a[]  = {5, 4, 7, 0, 1, -1};
    size_t n = sizeof(a) / sizeof(int);

    for (size_t i = 0; i < n; i++) {
    	assert(a[i]  == *(a + i));
    	assert(a[i]  == *(i + a));
    	assert(a[i]  == i[a]);
	assert(a + i == &a[i]);
    }
    
    // for (int *p = a; p < (a + n); p++) {
    for (int *p = a; *p >= 0; p++) {
    	printf("%d\n", *p);
    }

    return EXIT_SUCCESS;
}
