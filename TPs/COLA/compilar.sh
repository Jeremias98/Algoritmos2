#!/bin/bash

gcc -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o pruebas *.c
valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
