/* list.c */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char path[BUFSIZ];

    /* Determine directory */
    if (argc == 2) {
        strncpy(path, argv[1], BUFSIZ);
    } else {
        getcwd(path, BUFSIZ);
    }

    /* Open directory for reading */
    DIR *d = opendir(path);
    if (!d) {
        fprintf(stderr, "Unable to opendir on %s: %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    /* Iterate through directory entries */
    for (struct dirent *e = readdir(d); e; e = readdir(d)) {
        if (strcmp(e->d_name, ".") == 0 || strcmp(e->d_name, "..") == 0) {
            continue;
        }

        printf("%c. %s (%ld)\n", (e->d_type == DT_DIR ? 'D' : 'F'), e->d_name, e->d_ino);
    }

    closedir(d);

    /* Sorted alternative */

    struct dirent **entries;
    int n;

    /* Allocate sorted array of entries */
    n = scandir(path, &entries, NULL, alphasort);
    if (n < 0) {
        fprintf(stderr, "Unable to scandir on %s: %s\n", path, strerror(errno));
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        puts(entries[i]->d_name);
        free(entries[i]);   /* Free each entry */
    }
    free(entries);          /* Free array of entries */

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
