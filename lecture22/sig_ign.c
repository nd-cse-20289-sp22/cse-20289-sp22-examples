/* sig_ign.c:  An example of simply ignore your children. */

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
    int nchildren = atoi(argv[1]);

    signal(SIGCHLD, SIG_IGN);

    for (int i = 0; i < nchildren; i++) {
    	pid_t pid = fork();
    	if (pid == 0) {	    // Child
    	    printf("Child pid: %d, Parent pid: %d\n", getpid(), getppid());
    	    _exit(i);
	} else if (pid < 0) {
    	    fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
	}
    }

    for (int i = 0; i < nchildren; i++) {
    	system("ps ux | grep 'Z+' | grep -v grep");
    	sleep(1);
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
