CC=gcc
CFLAGS=-Wall -g -Isrc/parser

%: obj/lib.o obj/%.o 
	$(CC) -o $@ $^

obj/%.o: src/%.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

obj/lib.o: src/parser/parser.c directories 
	$(CC) $(CFLAGS) $< -o $@ -c

.PHONY: directories clean

directories:
	if ! [ -d "obj" ]; then \
		mkdir obj; \
	fi

clean:
	rm -rf obj
