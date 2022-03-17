/* list.c */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */

const int DATA[] = {4, 6, 6, 3, 7, 0};

/* Node Structure */

typedef struct Node Node;
struct Node {
    int   data;
    Node *next;
};

Node * node_create(int data, Node *next) {
    Node *n = malloc(sizeof(Node));
    if (n) {
    	n->data = data;
    	n->next = next;
    }
    return n;
}

/* List Structure */

typedef struct List List;
struct List {
    Node *head;
};

void	list_insert(List *l, int value) {
    l->head = node_create(value, l->head);
}

bool    list_search(List *l, int value) {
    for (Node *curr = l->head; curr; curr = curr->next) {
    	if (curr->data == value) {
    	    return true;
	}
    }

    return false;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    List l = {0};

    // Insert each item in DATA into set
    for (const int *p = DATA; *p > 0; p++) {
    	list_insert(&l, *p);
    }

    // Search for numbers 1 - 9 in set
    for (int i = 1; i < 10; i++) {
    	printf("%d ? %s\n", i, list_search(&l, i) ? "YES" : "NO");
    }

    return EXIT_SUCCESS;
}
