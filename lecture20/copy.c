/* copy.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>

void usage(const char *program) {
    fprintf(stderr, "Usage: %s source target\n", program);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
    	usage(argv[0]);
    	return EXIT_FAILURE;
    }

    // Command line arguments
    const char *source_path = argv[1];
    const char *target_path = argv[2];

    // Open file for reading
    int source_fd = open(source_path, O_RDONLY);    // Discuss: open
    if (source_fd < 0) {			    // Discuss: errno
    	fprintf(stderr, "open: %s\n", strerror(errno));
    	return EXIT_FAILURE;
    }

    FILE *source_file = fdopen(source_fd, "r");	    // Discuss: fdopen
    if (!source_file) {
    	fprintf(stderr, "fopen: %s\n", strerror(errno));
    	return EXIT_FAILURE;
    }

    // Open file for writing
    FILE *target_file = fopen(target_path, "w");    // Discuss: fopen
    if (!target_file) {
    	fprintf(stderr, "fopen: %s\n", strerror(errno));
    	return EXIT_FAILURE;
    }

    // Copy from source file to target file
    char   buffer[BUFSIZ];			    // Review: buffer
    size_t nread;				    // Discuss: fread
    while ((nread = fread(buffer, 1, BUFSIZ, source_file)) > 0) {
    	fwrite(buffer, 1, nread, target_file);	    // Discuss: fwrite
    }

    // Close files
    fclose(source_file);			    // Review: fclose
    fclose(target_file);

    return EXIT_SUCCESS;
}
