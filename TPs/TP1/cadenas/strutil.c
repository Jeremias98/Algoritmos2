#define _POSIX_C_SOURCE 200809L
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_subcadena(const char* cadena, int posicion, int largo) {
	
	char* subcadena = malloc((size_t)(largo + 1) * sizeof(char));
	
	if (subcadena == NULL) return NULL;
	
	int i;
	for(i = 0; i < largo ; i++) {
		subcadena[i] = cadena[posicion + i];
	}
	
	subcadena[i] = '\0';
	
	return subcadena;
}

char** split(const char* str, char sep) {
	
    char** result = NULL;
    
    size_t largo = strlen(str);
    
    int cant_palabras = 0;
    
	int inicio_palabra = 0;
	int index_palabra = 0;
	int largo_palabra = 0;
    
    for(int i = 0; i < largo ; i++) {
		if (str[i] == sep) {
			cant_palabras++;
		}
	}
	
	cant_palabras++;
	
	result = malloc( (cant_palabras + 1) * sizeof(char*));
	
	if (result == NULL) return NULL;
   
	for(int i = 0; i <= largo ; i++) {
		if (str[i] == sep || str[i] == '\0') {
			largo_palabra = i - inicio_palabra;
			result[index_palabra] = get_subcadena(str, inicio_palabra, largo_palabra);
			index_palabra++;
			inicio_palabra = i + 1;
		}
	}
	
	result[cant_palabras] = NULL;
    
    return result;
}

char* join(char** strv, char sep) {
	
	char* result;
	
	char sep_casteado[2];
	
	sep_casteado[0] = sep;
	sep_casteado[1] = '\0';
	
	int cant_elementos = 0;
	size_t largo_total = 0;
	while (*(strv + cant_elementos)) {
		largo_total += strlen(strv[cant_elementos]);
		cant_elementos++;
	}
	
	largo_total++;
	
	largo_total += cant_elementos; 
	
	result = malloc( (largo_total) * sizeof(char));
	
	if (result == NULL) return NULL;
	
	strcpy(result, strv[0]);
	
	for (int i = 1; i < cant_elementos ; i++)
	{
		strcat(result, sep_casteado);
		strcat(result, strv[i]);
	}
	
	result[largo_total - 1] = '\0';
	
	return result;
	
}

void free_strv(char* strv[]) {
	
	for (int i = 0; *(strv + i); i++)
	{
		free(*(strv + i));
	}
	
	free(strv);
	
}






