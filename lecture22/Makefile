SOURCE=		$(wildcard *.c)
TARGET=		$(SOURCE:.c=)

all:		$(TARGET)

%:		%.c
	gcc -g -std=gnu99 -Wall -o $@ $<

clean:
	rm -f $(TARGET)
