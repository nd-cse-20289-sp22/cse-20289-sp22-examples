/* table.c */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define NBUCKETS (1<<2)

const int DATA[]= {4, 6, 6, 3, 7, 0};

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

/* Table Structure */

typedef struct Table Table;
struct Table {
    Node *buckets[NBUCKETS];
};

void	table_insert(Table *t, int value) {
    int bucket = value % NBUCKETS;

    for (Node *curr = t->buckets[bucket]; curr; curr = curr->next) {
    	if (curr->data == value) {
    	    return;
	}
    }

    t->buckets[bucket] = node_create(value, t->buckets[bucket]);
}

bool    table_search(Table *t, int value) {
    int bucket = value % NBUCKETS;

    for (Node *curr = t->buckets[bucket]; curr; curr = curr->next) {
    	if (curr->data == value) {
    	    return true;
	}
    }

    return false;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    Table t = {0};

    // Insert each item in DATA into set
    for (const int *p = DATA; *p > 0; p++) {
    	table_insert(&t, *p);
    }

    // Search for numbers 1 - 9 in set
    for (int i = 1; i < 10; i++) {
    	printf("%d ? %s\n", i, table_search(&t, i) ? "YES" : "NO");
    }

    return EXIT_SUCCESS;
}
