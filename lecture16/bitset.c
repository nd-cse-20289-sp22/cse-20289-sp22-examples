/* bitset.c */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int bitset = 0;			    // Initialize bitset to 0

    for (int argind = 1; argind < argc; argind++) {
    	char *argument = argv[argind];
    	int   bit      = atoi(argument);    // Convert argument to integer

    	bitset |= (1<<bit);		    // Set bit in bitset
    }

    printf("bitset = %d\n", bitset);	    // Print raw bitset value

    for (int i = 0; i < (sizeof(bitset)*8); i++) {
    	if (bitset & (1<<i)) {		    // Check if bitset is set
    	    printf("%d is set!\n", i);
	}
    }

    return EXIT_SUCCESS;
}
