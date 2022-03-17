CC=	gcc
CFLAGS=	-Wall -g -std=gnu99

all:	palindrome bitset

palindrome:	palindrome.c
	$(CC) $(CFLAGS) -o $@ $^

bitset:		bitset.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f palindrome bitset
