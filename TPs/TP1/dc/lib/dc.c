#define _POSIX_C_SOURCE 200809L
#include "dc.h"
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


int logaritmo(int numero, int base) {
		
	if (numero == base) return 1;
	if (numero == 1) return 0;
	if (numero < 0) return -1; // Codigo de error
	
	return 1 + logaritmo(numero/base, base);
		
}

int potencia(int numero, int pot) {
	
	if (pot == 0) return 1;
	
	int x = potencia(numero, pot/2);
	
	if (pot % 2 == 0) {
		return x * x;
	}
	
	return numero * x * x;
	
}

int _raiz_cuadrada(int x, int factor) {
	
	if ((factor * factor) <= x) return factor;
	
	return _raiz_cuadrada(x, (factor/2)+1);
	
}

int raiz_cuadrada(int x) {
	if (x < 0) return -1;
	return _raiz_cuadrada(x, x);
}

int aplicar_funcion(int n, char* funcion) {
	
	//printf("%s(%d)\n", funcion, n);
	
	return raiz_cuadrada(n);
	
}

int aplicar_operador_ternario(int n1, int n2, int n3) {
	
	//printf("%d != 0 ? %d : %d\n", n3, n2, n1);
	
	return (n3 != 0) ? n2 : n1;
	
}

int aplicar_operacion_algebraica(int n1, int n2, char* operando) {
	
	//printf("%d %s %d\n", n1, operando, n2);
	
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
	else if (strcmp(operando, "log") == 0) {
		return logaritmo(n1, n2);
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

bool calcular(pila_t* pila_numeros, char* operacion) {
	
	bool calculo_ok = true;
	
	char* operando = strtok(operacion, "\n");
	
	int i_res = 0;
	char* c_res = malloc(20 * sizeof(char));
	
	char* c_num_1 = pila_desapilar(pila_numeros);
	
	// Caso es funcion  => un numero
	if (operando_es_funcion(operando)) {
		
		i_res = aplicar_funcion(atoi(c_num_1), operando);
		
	}
	else if (!pila_esta_vacia(pila_numeros)) {
		
		char* c_num_2 = pila_desapilar(pila_numeros);
		
		// Caso operacion algebraica  => dos numeros
		if (operando_es_operacion_alg(operando)) {				
			
			i_res = aplicar_operacion_algebraica(atoi(c_num_1), atoi(c_num_2), operando);
	
			free(c_num_2);
			
		}
		else if (!pila_esta_vacia(pila_numeros)) {
			
			// Caso operador ternario => tres numeros
			if (operando_es_ternario(operando)) {
		
				char* c_num_3 = pila_desapilar(pila_numeros);
				
				i_res = aplicar_operador_ternario(atoi(c_num_1), atoi(c_num_2), atoi(c_num_3));
								
				free(c_num_2);
				free(c_num_3);
				
			}
			else {
				fprintf(stderr, "ERROR: Operacion desconocida\n");
				calculo_ok = false;
			}
			
		}
		else {
			fprintf(stderr, "ERROR: No hay suficientes numeros\n");
			calculo_ok = false;
		}
		
	}
	else {
		fprintf(stderr, "ERROR: No hay suficientes numeros\n");
		calculo_ok = false;
	}
	
	if (calculo_ok) {
		sprintf(c_res,"%d",i_res);
		pila_apilar(pila_numeros, strdup(c_res));
	}
	
	free(c_num_1);
	free(c_res);
	
	return calculo_ok;
	
}

void vaciar_pila(pila_t* pila_numeros) {
	
	while(!pila_esta_vacia(pila_numeros)) {
		free(pila_desapilar(pila_numeros));
	}
	
}

int dc_procesar_entrada() {
	
	FILE* archivo = stdin;
	
	char linea[BUFFER_SIZE];
	
	pila_t* pila_numeros = pila_crear();
	
	if (pila_numeros == NULL) {
		fprintf(stderr, "No hay memoria disponible\n");
		return -1;
	}
	
	while(fgets(linea, BUFFER_SIZE, archivo) != NULL) {
		
		char** array = split(linea, ' ');
		
		bool calculo_ok = true;
	
		for (int i = 0; *(array + i) && calculo_ok ; i++) {
			
			if (es_numero(array[i])) {
				
				pila_apilar(pila_numeros, strdup(array[i]));
				
			}
			else {
				calculo_ok = calcular(pila_numeros, array[i]);
			}
			
		}
		
		char* resultado = pila_desapilar(pila_numeros);
		
		if (pila_esta_vacia(pila_numeros) &&  calculo_ok) {
			fprintf(stdout, "%s\n", resultado);	
		}
		
		if (resultado != NULL) free(resultado);
		
		free_strv(array);
		
	}
	
	pila_destruir(pila_numeros);
	
	return 0;
}
