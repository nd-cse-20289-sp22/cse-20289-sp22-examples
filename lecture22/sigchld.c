/* sigchld.c: An example of using SIGCHLD */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t ChildPid    = -1;
int   ChildStatus = -1;

void sigchld_handler(int signum) {
    ChildPid = wait(&ChildStatus);
}

int main(int argc, char *argv[]) {
    signal(SIGCHLD, sigchld_handler);   // Register handler

    pid_t pid = fork();
    if (pid < 0) {	    // Error
	fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	return EXIT_FAILURE;
    }

    if (pid == 0) {	    // Child
	printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
	sleep(5);
    } else {		    // Parent
	while (ChildPid < 0) {  // Busy wait
            printf("Parent pid: %d, Child pid: %d\n", getpid(), pid);
	    sleep(1);
        }
	printf("Child pid: %d, Exit Status: %d\n", ChildPid, ChildStatus);
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
