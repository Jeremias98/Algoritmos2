CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = ./dc < bin/scripts1.txt

build: ./lib/*.c *.c
	$(CC) $(CFLAGS) -o dc ./lib/*.c *.c
	$(VALGRIND) $(CMD)

run: build
