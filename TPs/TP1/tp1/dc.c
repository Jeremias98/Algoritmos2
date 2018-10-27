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
	if (numero == 1 || numero < base) return 0;
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

int raiz_cuadrada(int x) {
	
	int inicio, fin, medio;
	inicio = 1;
	fin = x;
	
	while (inicio <= fin) {
		
		medio = (inicio + fin) / 2;
		if (medio * medio == x) return medio;
		if (medio * medio > x) fin = medio - 1;
		else inicio = medio + 1; 
		
	}
	return fin;
		
}

bool aplicar_raiz_cuadrada(int n, int* resultado) {
	
	*resultado = raiz_cuadrada(n);
	
	return *resultado > -1;
	
}

int aplicar_operador_ternario(int n1, int n2, int n3) {

	return (n1 == 0) ? n3 : n2;
	
}

bool aplicar_operacion_algebraica(int n1, int n2, char* operando, int* resultado) {
	
	if (strcmp(operando, "+") == 0) {
		*resultado = (n1 + n2);
	}
	else if (strcmp(operando, "-") == 0) {
		*resultado = (n1 - n2);
	}
	else if (strcmp(operando, "*") == 0) {
		*resultado = (n1 * n2);
	}
	else if (strcmp(operando, "/") == 0) {
		if (n2 == 0) return false;
		*resultado = (n1 / n2);
	}
	else if (strcmp(operando, "log") == 0) {
		if (n1 > 0 && n2 > 0) {
			*resultado = logaritmo(n1, n2); 
		}
		else {
			return false;
		}
		
	}
	else {
		*resultado = potencia(n1, n2);
	}
	
	//printf("%d %s %d = %d\n", n2, operando, n1, *resultado);
	
	return true;
	
}

// Devuelve si se requiere una sola operacion. En caso que se 
// agreguen operaciones, puede utilizarce
bool op_requiere_uno(char* operando) {
	if (strcmp(operando, "sqrt") != 0) {
		return false;
	}
	return true;
}

bool op_requiere_tres(char* operando) {
	if (strcmp(operando, "?") != 0) {
		return false;
	}
	return true;
}

bool op_requiere_dos(char* operando) {
	if (strcmp(operando, "+") != 0 && strcmp(operando, "-") != 0 && strcmp(operando, "*") != 0 && strcmp(operando, "/") != 0 && strcmp(operando, "^") != 0 && strcmp(operando, "log") != 0) {
		return false;
	}
	return true;
}

bool calcular(pila_t* pila_numeros, char* operacion) {
	
	if (pila_esta_vacia(pila_numeros)) return false;
	
	bool calculo_ok = false;
	
	char* operando = strtok(operacion, "\n");
	
	int i_res = 0;
	char* c_res = malloc(20 * sizeof(char));
	
	char* c_num_1 = pila_desapilar(pila_numeros);
		
	// Caso un numero
	if (op_requiere_uno(operando)) {
		
		calculo_ok = aplicar_raiz_cuadrada(atoi(c_num_1), &i_res);
				
	}
	else if (!pila_esta_vacia(pila_numeros)) {
		
		char* c_num_2 = pila_desapilar(pila_numeros);
		
		// Caso dos numeros
		if (op_requiere_dos(operando)) {				
			
			calculo_ok = aplicar_operacion_algebraica(atoi(c_num_1), atoi(c_num_2), operando, &i_res);
	
			free(c_num_2);
			
		}
		else if (!pila_esta_vacia(pila_numeros)) {
			
			// Caso tres numeros
			if (op_requiere_tres(operando)) {
		
				char* c_num_3 = pila_desapilar(pila_numeros);
				
				i_res = aplicar_operador_ternario(atoi(c_num_1), atoi(c_num_2), atoi(c_num_3));
				
				calculo_ok = true;
								
				free(c_num_2);
				free(c_num_3);
				
			}
			
		}
		
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
	
	bool esta_vacio = true;
	
	while(fgets(linea, BUFFER_SIZE, archivo) != NULL) {
		
		esta_vacio = false;
		
		char** array = split(linea, ' ');
		
		bool calculo_ok = true;
	
		for (int i = 0; array[i] && calculo_ok ; i++) {
			
			if (strcmp(array[i], "") != 0 && strcmp(array[i], "\n") != 0) {
				
				if (es_numero(array[i])) {
				
					pila_apilar(pila_numeros, strdup(array[i]));
					
				}
				else {
					calculo_ok = calcular(pila_numeros, array[i]);
				}
			}
			
		}
		
		char* resultado = pila_desapilar(pila_numeros);
		
		if (pila_esta_vacia(pila_numeros) &&  calculo_ok && resultado != NULL) {
			fprintf(stdout, "%s\n", resultado);	
		}
		else {
			while (!pila_esta_vacia(pila_numeros)) {
				free(pila_desapilar(pila_numeros));
			}
			
			fprintf(stderr, "ERROR\n");	
		}
		
		if (resultado != NULL) free(resultado);
		
		free_strv(array);
		
	}
	
	if (esta_vacio) {
		fprintf(stderr, "ERROR\n");	
	}
	
	//printf("LINEA%s\n", linea);
	
	pila_destruir(pila_numeros);
	
	return 0;
}
