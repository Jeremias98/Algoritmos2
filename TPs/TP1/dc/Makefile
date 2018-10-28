CC = gcc
CFLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = ./dc < operaciones.txt

build_pablo: dc_pablo.c strutil.c pila.c
	$(CC) $(CFLAGS) -o dc dc_pablo.c strutil.c pila.c
	$(VALGRIND) $(CMD)
	
build: main_dc.c dc.c strutil.c pila.c
	$(CC) $(CFLAGS) -o dc main_dc.c dc.c strutil.c pila.c
	$(VALGRIND) $(CMD)

run_pablo: build_pablo
run: build
