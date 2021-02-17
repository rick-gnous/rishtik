CC=gcc
CFLAGS=-Wall -g -Isrc/shell_tools
LIB=src/shell_tools

all: directories rishtik clean

rishtik: obj/lib.o obj/shell.o 
	$(CC) -o $@ $^

obj/shell.o: src/shellOpt.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

obj/lib.o: $(LIB)/parser.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

.PHONY: all directories clean

directories:
	if ! [ -d "obj" ]; then \
		mkdir obj; \
	fi

clean:
	rm -rf obj
