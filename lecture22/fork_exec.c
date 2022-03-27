/* fork_exec.c: An example of forking and execing */

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
    int status = EXIT_SUCCESS;
    pid_t  pid = fork();
    if (pid < 0) {	    // Error
	fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	return EXIT_FAILURE;
    }

    if (pid == 0) {	    // Child
	printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
	if (execlp("uname", "uname", "-a", NULL) < 0) {
	    fprintf(stderr, "Unable to execlp: %s\n", strerror(errno));
	    _exit(EXIT_FAILURE);
	}
	// 1. First argument is path, while second argument is the name of the process
	// 2. Replace execlp with execvp
    } else {		    // Parent
	printf("Parent pid: %d, Child pid: %d\n", getpid(), pid);
	while ((pid = wait(&status)) < 0);
	printf("Child pid: %d, Exit Status: %d\n", pid, status);
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
