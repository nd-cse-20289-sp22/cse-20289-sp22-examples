/* value.c */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>

typedef union {
    uint64_t number;	// DISCUSS: signed vs unsigned
    char     string[6]; // DISCUSS: Change 6 to 10 (padding)
} Value;

void value_format(Value *v, FILE *stream) {
    fprintf(stream, "Value{number = %016lx, string = %s}\n", v->number, v->string);
}

void value_bytes(Value *v, FILE *stream) {
    uint8_t *bytes = (uint8_t *)v;  // DISCUSS: casting

    // DISCUSS: endianness
    for (int i = sizeof(Value) - 1; i >= 0; i--) {
    	printf("byte[%d] = %02x\n", i, bytes[i]);
    }
}

int main(int argc, char *argv[]) {
    printf("Sizeof(Value) = %lu\n", sizeof(Value));
    puts("");

    Value v = {0};
    value_format(&v, stdout);
    value_bytes(&v, stdout);
    puts("");

    v.number = -1;
    value_format(&v, stdout);
    value_bytes(&v, stdout);
    puts("");
    
    v.number = ULONG_MAX;
    printf("%lu\n", ULONG_MAX);
    value_format(&v, stdout);
    value_bytes(&v, stdout);
    puts("");

    v.number = 0x4150524546;
    value_format(&v, stdout);
    value_bytes(&v, stdout);

    return 0;
}
