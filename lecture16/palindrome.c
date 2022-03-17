/* palindrome.c */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_palindrome(const char *s) {
    const char *head = s;			    // Discuss: const
    const char *tail = s + strlen(s) - 1;	    // Discuss: strlen, NUL

    while (head < tail && *head == *tail) {
    	head++;					    // Review: pointer arithmetic
    	tail--;
    }

    return head >= tail;
}

bool is_palindrome_permutation(const char *s) {
    int counts[1<<8] = {0};			    // Discuss: bit-shifting, initializing

    for (const char *c = s; *c; c++) {
    	counts[(int)*c]++;			    // Discuss: casting
    }

    int odds = 0;
    for (size_t i = 0; i < (1<<8); i++) {
    	odds += counts[i] % 2;
    }

    return odds <= 1;
}

bool is_palindrome_permutation_bitset(const char *s) {
    int32_t bset = 0;				    // Discuss: bitset

    for (const char *c = s; *c; c++) {
    	bset ^= (1<<(*c - 'a'));		    // Discuss: XOR, conversion, shift
    }

    int ones = 0;
    for (int i = 0; i < 8*sizeof(bset); i++) {
    	ones += ((bset & (1<<i)) >> i);		    // Discuss: AND, shifts
    }

    return ones <= 1;
}

int main(int argc, char *argv[]) {
    char buffer[BUFSIZ];			    // Discuss: stack allocation

    while (fgets(buffer, BUFSIZ, stdin)) {	    // Discuss: fgets, BUFSIZ, stdin
    	buffer[strlen(buffer) - 1] = 0;		    // Discuss: chomp
    	puts(is_palindrome_permutation_bitset(buffer)
    	    ? "Yes"
    	    : "No"
    	);					    // Discuss: puts, ternary
    }

    return 0;
}
