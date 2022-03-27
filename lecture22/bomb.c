/* bomb.c: A demonstration of what happens when fork is called too many times. */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define THRESHOLD 10

int main(int argc, char *argv[]) {
    for (int i = 0; i < THRESHOLD; i++) {
    	pid_t pid = fork();
    	if (pid < 0) {
    	    fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	}
	sleep(5);
    }
    // Use watch pstree to monitor

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
