/* binning.c */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
const char * find_non_repeating(const char *s) {
    for (const char *c = s; *c; c++) {
    	size_t count = 0;
    	for (const char *n = s; *n; n++)
    	    if (tolower(*c) == tolower(*n))
    	    	count++;

    	if (count == 1)
	    return c;
    }

    return NULL;
}
*/

const char * find_non_repeating(const char *s) {
    int set[1<<8] = {0};

    for (const char *c = s; *c; c++) {
    	set[tolower(*c)]++;
    }

    for (const char *c = s; *c; c++) {
    	if (set[tolower(*c)] == 1)
    	    return c;
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stdin)) {
    	buffer[strlen(buffer) - 1] = 0;

    	const char *s = find_non_repeating(buffer);

    	if (s) {
    	    printf("%s Has a non-repeating character: %c\n", buffer, *s);
	} else {
    	    printf("%s Does not contain a non-repeating character\n", buffer);
	}
    }

    return EXIT_SUCCESS;
}
