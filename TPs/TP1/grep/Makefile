CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = grep vos 0 "bin/charla.txt"

build: ./lib/*.c *.c
	$(CC) $(CFLAGS) -o grep ./lib/*.c *.c
	$(VALGRIND) ./$(CMD)

run: build
