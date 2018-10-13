#include <stdio.h>
#include <stdlib.h>
#include "grep.h"

void validar_parametros(char* keyword, int lineas, char* archivo) {
	
}

int main(int argc, char *argv[]) {
	
	if (argc < 3) {
		fprintf(stderr, "Cantidad de parametros erronea\n");
		return -1;
	}
	
	char* keyword = NULL;
	int lineas = 0;
	char* archivo = NULL;

	for (int i = 2 ; i <= argc && argc > 1 ; i++) {
		switch(i) {
			case(2):
				keyword = argv[1];
			break;
			case(3):
				lineas = atoi(argv[2]);
				if (lineas == 0 && argv[2][0] != '0') {
					fprintf(stderr, "Tipo de parametro incorrecto\n");
					return -1;
				}
				
			break;
			case(4):
				archivo = argv[3];
			break;
		}
	}
	
	grep(keyword, lineas, archivo);
	

    return 0;
}
