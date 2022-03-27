/* spidey.c: Forking HTTP server */

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <dirent.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

/* Constants */
#define WHITESPACE      " \t\n"

/* Macros */
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...)   fprintf(stderr, "[%5d] DEBUG %10s:%-4d " M "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)
#endif
#define log(M, ...)     fprintf(stderr, "[%5d] LOG   %10s:%-4d " M "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * Allocate a socket, bind it to port, and start listening
 **/
int socket_listen(const char *port) {
    /* TODO: Lookup server address information */
    struct addrinfo *results;
    struct addrinfo  hints = {
        .ai_family      = AF_UNSPEC,    // IPv4 or IPv6
        .ai_socktype    = SOCK_STREAM,  // TCP
        .ai_flags       = AI_PASSIVE,   // Listen on socket
    };

    int status = getaddrinfo(NULL, port, &hints, &results);
    if (status != 0) {
        return -1;
    }

    /* TODO: For each address entry, allocate socket, bind, and listen */
    int server_fd = -1;
    for (struct addrinfo *p = results; p && server_fd < 0; p = p->ai_next) {
        /* TODO: Allocate socket */
        server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (server_fd < 0) {
            continue;
        }

        /* TODO: Bind socket to port */
        if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(server_fd);
            server_fd = -1;
            continue;
        }

        /* TODO: Listen on socket */
        if (listen(server_fd, SOMAXCONN) < 0) {
            close(server_fd);
            server_fd = -1;
            continue;
        }
    }

    freeaddrinfo(results);
    return server_fd;
}

/**
 * Accept an incoming client and return client stream
 **/
FILE *accept_client(int server_fd) {
    /* TODO: Accept incoming connection */
    struct sockaddr client_addr;
    socklen_t       client_len;

    int client_fd = accept(server_fd, &client_addr, &client_len);
    if (client_fd < 0) {
        return NULL;
    }

    /* TODO: Open a file stream from socket file descriptor */
    FILE *client_stream = fdopen(client_fd, "w+");
    if (!client_stream) {
        close(client_fd);
        return NULL;
    }

    return client_stream;
}

/**
 * Handle request
 **/
void handle_file_request(FILE *client_stream);
void handle_directory_request(FILE *client_stream);
void handle_cgi_request(FILE *client_stream);

void handle_request(FILE *client_stream) {
    char buffer[BUFSIZ];

    /* TODO: Parse URI */
    if (!fgets(buffer, BUFSIZ, client_stream)) {
        return;
    }

    // GET URI HTTP/1.0
    char *method   = strtok(buffer, WHITESPACE);
    char *uri      = strtok(NULL  , WHITESPACE);

    debug("method   = %s", method);
    debug("uri      = %s", uri);

    /* TODO: Parse Query String */
    char *query = strchr(uri, '?');
    if (!query) {
        query = "";
    } else {
        *query++ = '\0';
    }

    setenv("QUERY_STRING", query, 1);

    /* TODO: Skip Headers */
    while (fgets(buffer, BUFSIZ, client_stream) && strlen(buffer) > 2);

    /* TODO: Dispatch to Specific Handler */
    handle_file_request(client_stream);
    // handle_directory_request(client_stream);
    // handle_cgi_request(client_stream);

    return;
}

void handle_file_request(FILE *client_stream) {
    // Open file stream
    FILE *file_stream = fopen("spidey.png", "r");
    if (!file_stream) {
        return;
    }

    // Send Headers First
    fprintf(client_stream, "HTTP/1.0 200 OK\r\n");
    fprintf(client_stream, "Content-Type: image/png\r\n");
    fprintf(client_stream, "\r\n");

    // Copy from file_stream to client_stream
    char buffer[BUFSIZ];
    size_t nread;
    while ((nread = fread(buffer, 1, BUFSIZ, file_stream)) > 0) {
        fwrite(buffer, 1, nread, client_stream);
    }

    fclose(file_stream);
}

void handle_directory_request(FILE *client_stream) {
    struct dirent **entries;
    int n = scandir(".", &entries, 0, alphasort);
    if (n < 0) {
        debug("scandir no good: %s", strerror(errno));
        return;
    }

    // Send Headers First
    fprintf(client_stream, "HTTP/1.0 200 OK\r\n");
    fprintf(client_stream, "Content-Type: text/html\r\n");
    fprintf(client_stream, "\r\n");

    // Loop through directory entries and print it
    fprintf(client_stream, "<ol>\n");
    for (int i = 0; i < n; i++) {
        fprintf(client_stream, "<li>%s</li>\n", entries[i]->d_name);
        free(entries[i]);
    }

    free(entries);
    fprintf(client_stream, "</ol>\n");
}

void handle_cgi_request(FILE *client_stream) {
    FILE *process_stream = popen("./cgi.sh", "r");

    // Copy from file_stream to client_stream
    char buffer[BUFSIZ];
    size_t nread;
    while ((nread = fread(buffer, 1, BUFSIZ, process_stream)) > 0) {
        fwrite(buffer, 1, nread, client_stream);
    }

    pclose(process_stream);
}

/* Main Execution */

int main(int argc, char *argv[]) {
    char *port = argv[1];

    /* TODO: Listen to socket */
    int server_fd = socket_listen(port);
    if (server_fd < 0) {
        perror("socket_listen");
        return EXIT_FAILURE;
    }

    signal(SIGCHLD, SIG_IGN);

    /* TODO: Process incoming connections */
    while (true) {
        /* TODO: Accept an incoming connection */
        FILE *client_stream = accept_client(server_fd);
        if (!client_stream) {
            return EXIT_FAILURE;
        }

        pid_t pid = fork();
        if (pid == 0) {     // Child
            debug("handle child connection");
            handle_request(client_stream);
            fclose(client_stream);
            exit(EXIT_SUCCESS);
        } else {            // Parent
            fclose(client_stream);
        }
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
