/* system.c: An example of using system instead of manually forking, execing,
 * and waiting. */

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
    int status = system("ls -l");
    if (status != EXIT_SUCCESS) {
	fprintf(stderr, "Unable to system: %s\n", strerror(errno));
	return status;
    }
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
