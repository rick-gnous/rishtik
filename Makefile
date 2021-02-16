CC=gcc
CFLAGS=-Wall -g -Isrc/include

%: obj/lib.o obj/%.o 
	$(CC) -o $@ $^

obj/%.o: src/%.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

obj/lib.o: src/include/mylib.c directories 
	$(CC) $(CFLAGS) $< -o $@ -c

.PHONY: directories clean

directories:
	if ! [ -d "obj" ]; then \
		mkdir obj; \
	fi

clean:
	rm -rf obj
