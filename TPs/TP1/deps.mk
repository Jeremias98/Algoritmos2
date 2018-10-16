CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror


build: $(CC) $(CFLAGS) -o grep ./lib/*.c *.c

run: build
