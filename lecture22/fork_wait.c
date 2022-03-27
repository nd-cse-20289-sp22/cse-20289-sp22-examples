/* fork_wait.c: An example of forking and waiting */

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

    switch (pid) {
        case  0:            // Child
            printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
            // 1. Add return EXIT_FAILURE
            break;

        case -1:            // Parent (Error)
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
            break;

        default:            // Parent (Success)
            printf("Parent pid: %d, Child pid: %d\n", getpid(), pid);
            while ((pid = wait(&status)) < 0);
            printf("Child pid: %d, Exit Status: %d\n", pid, status);
            // 2. Use WEXITSTATUS
            break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
