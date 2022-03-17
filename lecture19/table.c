/* table.c */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define NBUCKETS (1<<8)

const int DATA[]= {4, 6, 6, 3, 7, 0};

/* Table Structure */

typedef struct Table Table;
struct Table {
    int buckets[NBUCKETS];
};

void	table_insert(Table *t, int value) {
    int bucket = value % NBUCKETS;
    t->buckets[bucket] = value;
}

bool    table_search(Table *t, int value) {
    int bucket = value % NBUCKETS;
    return t->buckets[bucket] == value;
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
