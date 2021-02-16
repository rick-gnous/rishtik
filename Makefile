CC=gcc
CFLAGS=-Wall -g -Isrc/parser

all: directories rishtik clean

rishtik: obj/lib.o obj/shell.o 
	$(CC) -o $@ $^

obj/shell.o: src/shellOpt.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

obj/lib.o: src/parser/parser.c directories 
	$(CC) $(CFLAGS) $< -o $@ -c

.PHONY: all directories clean

directories:
	if ! [ -d "obj" ]; then \
		mkdir obj; \
	fi

clean:
	rm -rf obj
