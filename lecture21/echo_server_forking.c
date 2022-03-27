/* echo_server_forking.c: simple forking TCP echo server  */

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const char *HOST = NULL;
const char *PORT = "9422";

int socket_listen(const char *host, const char *port) {
    /* Lookup server address information */
    struct addrinfo  hints = {
        .ai_family   = AF_UNSPEC,   /* Return IPv4 and IPv6 choices */
        .ai_socktype = SOCK_STREAM, /* Use TCP */
        .ai_flags    = AI_PASSIVE,  /* Use all interfaces */
    };
    struct addrinfo *results;
    int status;
    if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
    	fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
	return -1;
    }

    /* For each server entry, allocate socket and try to connect */
    int server_fd = -1;
    for (struct addrinfo *p = results; p != NULL && server_fd < 0; p = p->ai_next) {
	/* Allocate socket */
	if ((server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
	    fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
	    continue;
	}

	/* Bind socket */
	if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) {
	    fprintf(stderr, "Unable to bind: %s\n", strerror(errno));
	    close(server_fd);
	    server_fd = -1;
	    continue;
	}

    	/* Listen to socket */
	if (listen(server_fd, SOMAXCONN) < 0) {
	    fprintf(stderr, "Unable to listen: %s\n", strerror(errno));
	    close(server_fd);
	    server_fd = -1;
	    continue;
	}
    }

    /* Release allocate address information */
    freeaddrinfo(results);

    return server_fd;
}

FILE *accept_client(int server_fd) {
    struct sockaddr client_addr;
    socklen_t client_len = sizeof(struct sockaddr);

    /* Accept incoming connection */
    int client_fd = accept(server_fd, &client_addr, &client_len);
    if (client_fd < 0) {
        fprintf(stderr, "Unable to accept: %s\n", strerror(errno));
        return NULL;
    }

    /* Open file stream from socket file descriptor */
    FILE *client_file = fdopen(client_fd, "w+");
    if (!client_file) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(client_fd);
    }

    return client_file;
}

int main(int argc, char *argv[]) {
    /* Setup server socket */
    int server_fd = socket_listen(HOST, PORT);
    if (server_fd < 0) {
        return EXIT_FAILURE;
    }

    signal(SIGCHLD, SIG_IGN);

    /* Process incoming connections */
    while (1) {
        /* Accept client connection */
        FILE *client_file = accept_client(server_fd);
        if (!client_file) {
            continue;
        }

        /* Fork process to handle client */
        pid_t pid = fork();

        if (pid < 0) {          /* Error */
            fprintf(stderr, "Unable to fork: %s\n", strerror(errno));
            fclose(client_file);
        } else if (pid == 0) {  /* Child */
            /* Read from client and then echo back */
            char buffer[BUFSIZ];
            while (fgets(buffer, BUFSIZ, client_file)) {
                fputs(buffer, stdout);
                fputs(buffer, client_file);
            }
            fclose(client_file);
            exit(EXIT_SUCCESS);
        } else {                /* Parent */
            /* Close connection */
            fclose(client_file);
        }
    }

    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
