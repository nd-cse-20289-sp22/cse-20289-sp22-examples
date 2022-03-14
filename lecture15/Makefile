SOURCE=		$(wildcard *.c)
TARGET=		$(SOURCE:.c=)

all:		$(TARGET)

%:%.c
	gcc -std=gnu99 -Wall -o $@ $<

clean:
	rm -f $(TARGET)
