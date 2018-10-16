#define _POSIX_C_SOURCE 200809L
#include "grep.h"
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 512

bool buscar(char* keyword, int cant_lineas, char* archivo) {
	
	FILE* entrada = (archivo == NULL) ? stdin : fopen(archivo, "r");
	
	if (entrada == NULL) {
		fprintf(stderr, "No se encontro el archivo especificado\n");	
		return false;
	}
	
	int index_linea = 1;
	int find_result = 0;
	
	char temp[BUFFER_SIZE];
	
	cola_t* cola_lineas_extra = cola_crear();
	
	if (cola_lineas_extra == NULL) return false;
	
	while(fgets(temp, BUFFER_SIZE, entrada) != NULL) {
		
		if((strstr(temp, keyword)) != NULL) {
			
			while(cola_ver_primero(cola_lineas_extra) != NULL) {
				char* linea = cola_desencolar(cola_lineas_extra);
				printf("%s\n", linea);
				free(linea);
			}
			
			printf("%s\n", temp);
			
			find_result++;
			
		}
		
		if (cant_lineas > 0) cola_encolar(cola_lineas_extra, strdup(temp));
		
		if (index_linea == cant_lineas) {
			free(cola_desencolar(cola_lineas_extra));
		}
		
		index_linea++;
	}
	
	
	if (archivo != NULL) fclose(entrada);
 
	cola_destruir(cola_lineas_extra, free);
	
	if(find_result == 0) {
		return false;
	}
	
	return true;
}

bool grep(char* keyword, int cant_lineas, char* archivo) {
	
	bool encontrado = buscar(keyword, cant_lineas, archivo);
	
	return encontrado;
}
