#!/bin/bash

gcc -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror -o pruebas *.c
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
