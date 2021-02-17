CC=gcc
CFLAGS=-Wall -g -Isrc/boitoutil
LIB=src/boitoutil
src:=$(wildcard $(LIB)/*.c)
obj:=$(patsubst $(LIB)/%.c,obj/%.o,$(src))

all: directories rishtik clean

rishtik: $(obj) obj/shell.o 
	$(CC) -o $@ $^

obj/shell.o: src/shellOpt.c 
	$(CC) $(CFLAGS) $^ -o $@ -c

$(obj): obj/%.o: $(LIB)/%.c
	$(CC) $(CFLAGS) $^ -o $@ -c

.PHONY: all directories clean

directories:
	if ! [ -d "obj" ]; then \
		mkdir -p obj/lib; \
	fi

clean:
	rm -rf obj
