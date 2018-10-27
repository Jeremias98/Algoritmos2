CFLAGS := -g -std=c99 -Wall -Wformat=2
CFLAGS += -Wshadow -Wpointer-arith -Wunreachable-code
CFLAGS += -Wconversion -Wno-sign-conversion -Wbad-function-cast

# Se puede comentar durante el desarrollo.
CFLAGS += -Werror

VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes
CMD = ./pruebas

test: abb_aux
	./abb_test.py

abb_aux: abb.o abb_aux.o

# Dependencias adicionales.
-include deps.mk

clean:
	rm -f abb_aux *.o
	
build: abb.c pruebas_grupo.c pila.c main.c testing.c
	$(CC) $(CFLAGS) -o pruebas abb.c pruebas_grupo.c pila.c main.c testing.c
	$(VALGRIND) $(CMD)

run: build

.PHONY: test clean
