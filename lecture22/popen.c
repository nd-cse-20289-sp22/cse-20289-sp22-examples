/* popen.c: An example of using os.popen instead of manually creating a pipe,
 * forking, and execing. */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *stream = popen("ls -l", "r");
    if (!stream) {
	fprintf(stderr, "Unable to popen: %s\n", strerror(errno));
	return EXIT_FAILURE;
    }

    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stream)) {
        fputs(buffer, stdout);
    }

    pclose(stream);
    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
