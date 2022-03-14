/* str_length */

#include <assert.h>
#include <string.h>
#include <stdlib.h>

size_t str_length(const char *s) {
    const char *c;
    for (c = s; *c; c++);
    return (c - s);
}

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
    	assert(str_length(argv[i]) == strlen(argv[i]));
    }
    return EXIT_SUCCESS;
}
