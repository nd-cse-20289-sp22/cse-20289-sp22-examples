/* check.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void usage(const char *program) {
    fprintf(stderr, "Usage: %s flag path\n", program);
    fprintf(stderr, "   -e path	    Returns if path exists\n");
    fprintf(stderr, "   -r path	    Returns if path is readable\n");
    fprintf(stderr, "   -x path	    Returns if path is executable\n");
    fprintf(stderr, "   -d path	    Returns if path is a directory\n");
    fprintf(stderr, "   -f path	    Returns if path is a regular file\n");
    fprintf(stderr, "   -s path	    Returns if path exists and has size greater than zero\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strlen(argv[1]) < 2) {
    	usage(argv[0]);
    	return EXIT_FAILURE;
    }

    const char *flag = argv[1];
    const char *path = argv[2];
    struct stat s;

    switch (flag[1]) {
	case 'e':
	    return stat(path, &s);
	case 'r':
	    return access(path, R_OK);
	case 'x':
	    return access(path, X_OK);
	case 'd':
	    return stat(path, &s) || !S_ISDIR(s.st_mode);
	case 'f':
	    return stat(path, &s) || !S_ISREG(s.st_mode);
	case 's':
	    return stat(path, &s) || s.st_size == 0;
    }

    return EXIT_FAILURE;
}
