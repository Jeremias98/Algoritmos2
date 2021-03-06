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

char* concatenar(const char *s1, const char *s2)
{
    char *concatenado = malloc(strlen(s1) + strlen(s2) + 1);
    if (!concatenado) return NULL;
    
    strcpy(concatenado, s1);
    strcat(concatenado, s2);
    
    return concatenado;
}

char* join(char** strv, char sep) {
	
	char* result;
	
	if (strv[0] == NULL) {
		result = malloc( 2 * sizeof(char));
		strcpy(result, "");
		return result;
	}
	
	char sep_casteado[2];
	sep_casteado[0] = sep;
	sep_casteado[1] = '\0';
	
	size_t cant_elementos = 1;
	
	result = strdup(strv[0]);
	
	while (*(strv + cant_elementos)) {
		
		// Guardo la posicion de memoria para liberarla
		char* res_anterior = result;
		
		char* parcial = concatenar(sep_casteado, strv[cant_elementos]);
		result = concatenar(result, parcial);
		
		free(res_anterior);		
		free(parcial);
		
		cant_elementos++;
	}
	
	return result;
	
}



void free_strv(char* strv[]) {
	
	for (int i = 0; *(strv + i); i++)
	{
		free(*(strv + i));
	}
	
	free(strv);
	
}






