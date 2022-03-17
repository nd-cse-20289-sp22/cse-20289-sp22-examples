/* mock.c */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *mock(const char *s) {
    /*
    char t[BUFSIZ];			// BUG: stack allocation
    strncpy(t, s, strlen(s) + 1);	// BUG: Off-by-1
    */
    char *t = malloc(strlen(s) + 1);	// BUG: Off-by-1
    strncpy(t, s, strlen(s) + 1);	// BUG: Off-by-1

    for (char *c = t; *c; c++) {
	*c = ((size_t)c % 2) ? toupper(*c) : tolower(*c);
    }

    // BUG: free?
    return t;
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
	char *t = mock(argv[i]);
	puts(t);
	free(t);    // BUG: free
    }
    return EXIT_SUCCESS;
}
