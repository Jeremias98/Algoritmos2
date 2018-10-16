#define _POSIX_C_SOURCE 200809L
#include "dc.h"
#include "cola.h"
#include "pila.h"
#include "strutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFFER_SIZE 512

bool es_numero(char* entrada) {
	return !(atoi(entrada) == 0 && entrada[0] != '0');
}

int potencia(int numero, int pow) {
	
	for (int i = pow ; i > 1 ; i--) {
		numero *= numero;
	}
	
	return numero;
	
}


// Por metodo babilonico
int raiz_cuadrada(int x) {
	
	int r = x;
	double factor = 0.5;
	int t = 0;
	
	while (t != r) {
		t = r;
		r = (int) ( factor * (r + (x/r)));
	}
	
	return r;
	
}


int aplicar_funcion(int n, char* funcion) {
	
	printf("%s(%d)\n", funcion, n);
	
	return raiz_cuadrada(n);
	
}

int aplicar_operador_ternario(int n1, int n2, int n3) {
	
	printf("%d != 0 ? %d : %d\n", n3, n2, n1);
	
	return (n3 != 0) ? n2 : n1;
	
}

int aplicar_operacion_algebraica(int n1, int n2, char* operando) {
	
	printf("%d %s %d\n", n1, operando, n2);
	
	if (strcmp(operando, "+") == 0) {
		return (n1 + n2);
	}
	else if (strcmp(operando, "-") == 0) {
		return (n1 - n2);
	}
	else if (strcmp(operando, "*") == 0) {
		return (n1 * n2);
	}
	else if (strcmp(operando, "/") == 0) {
		return (n1 / n2);
	}
	else {
		return potencia(n1, n2);
	}
	
}

bool operando_es_funcion(char* operando) {
	if (strcmp(operando, "sqrt") != 0) {
		return false;
	}
	return true;
}

bool operando_es_ternario(char* operando) {
	if (strcmp(operando, "?") != 0) {
		return false;
	}
	return true;
}

bool operando_es_operacion_alg(char* operando) {
	if (strcmp(operando, "+") != 0 && strcmp(operando, "-") != 0 && strcmp(operando, "*") != 0 && strcmp(operando, "/") != 0 && strcmp(operando, "^") != 0 && strcmp(operando, "log") != 0) {
		return false;
	}
	return true;
}

void calcular(pila_t* pila_numeros, cola_t* cola_operaciones) {
	
	while (!cola_esta_vacia(cola_operaciones) && !pila_esta_vacia(pila_numeros)) {
		
		char* operacion = cola_desencolar(cola_operaciones);
		char* operando = strtok(operacion, "\n");
		
		int i_res = 0;
		
		char* c_res = malloc(20 * sizeof(char));
		bool aplicado = false;
		
		char* c_num_1 = pila_desapilar(pila_numeros);
		
		// Caso es funcion
		if (operando_es_funcion(operando)) {
			
			i_res = aplicar_funcion(atoi(c_num_1), operando);
			
			aplicado = true;
			
		}
		else if (!pila_esta_vacia(pila_numeros)) {
			
			char* c_num_2 = pila_desapilar(pila_numeros);
			
			// Caso operacion algebraica
			if (operando_es_operacion_alg(operando)) {				
				
				i_res = aplicar_operacion_algebraica(atoi(c_num_1), atoi(c_num_2), operando);
				
				aplicado = true;
				
				free(c_num_2);
				
			}
			else if (!pila_esta_vacia(pila_numeros)) {
				
				if (operando_es_ternario(operando)) {
			
					char* c_num_3 = pila_desapilar(pila_numeros);
					
					i_res = aplicar_operador_ternario(atoi(c_num_1), atoi(c_num_2), atoi(c_num_3));
					
					aplicado = true;
					
					free(c_num_2);
					free(c_num_3);
					
				}
				else {
					fprintf(stderr, "ERROR: Operacion desconocida\n");
				}
				
			}
			
		}
		
		if (aplicado) {
			sprintf(c_res,"%d",i_res);
			pila_apilar(pila_numeros, strdup(c_res));
		}
		
		free(c_num_1);
		free(operacion);
		free(c_res);
		
	}
	
	if (pila_esta_vacia(pila_numeros)) {
		fprintf(stderr, "ERROR: Operacion desconocida\n");
	}
	else {
		char* resultado = pila_desapilar(pila_numeros);
		fprintf(stdout, "%s\n", resultado);
		free(resultado);
	}
	
}

void destruir_tdas(pila_t* pila_numeros, cola_t* cola_operaciones) {
	pila_destruir(pila_numeros);
	cola_destruir(cola_operaciones, free);
}

void vaciar_tdas(pila_t* pila_numeros, cola_t* cola_operaciones) {
	
	while(!cola_esta_vacia(cola_operaciones)) {
		free(cola_desencolar(cola_operaciones));
	}
	
	while(!pila_esta_vacia(pila_numeros)) {
		free(pila_desapilar(pila_numeros));
	}
	
}

int dc_procesar_entrada() {
	
	FILE* archivo = stdin;
	
	char linea[BUFFER_SIZE];
	
	pila_t* pila_numeros = pila_crear();
	cola_t* cola_operaciones = cola_crear();
	
	if (pila_numeros == NULL || cola_operaciones == NULL) {
		fprintf(stderr, "No hay memoria disponible\n");
		return -1;
	}
	
	while(fgets(linea, BUFFER_SIZE, archivo) != NULL) {
		
		char** array = split(linea, ' ');
		
		int cant_numeros = 0;
		int cant_operaciones = 0;
	
		for (int i = 0; *(array + i); i++) {
			
			if (es_numero(array[i])) {
				
				pila_apilar(pila_numeros, strdup(array[i]));
				cant_numeros++;
			}
			else {
				cola_encolar(cola_operaciones, strdup(array[i]));
				cant_operaciones++;
			}
			
		}
		
		if (cant_operaciones <= cant_numeros) {
			calcular(pila_numeros, cola_operaciones);
		}
		else {
			fprintf(stderr, "ERROR: Cantidad de operaciones mayor a cantidad de numeros\n");
		}
		
		vaciar_tdas(pila_numeros, cola_operaciones);
		
		free_strv(array);
		
	}
	
	destruir_tdas(pila_numeros, cola_operaciones);
	
	return 0;
}
