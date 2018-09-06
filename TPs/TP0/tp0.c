/*
 * Universidad de Buenos Aires, Facultad de ingenieria
 * Alumno: Ramirez Jeremias Nicolas
 * Padron: 102878
 * Titulo: TP0
 * */

#include "tp0.h"
#include<stdio.h>

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	// Creo una variable auxiliar y hago el intercambio de valores
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	/* En maximo guardo el valor a comparar, y 
	 en max_index su posicion */
	int maximo = 0;
	int max_index = 0;
	// Compruebo que el vector tenga elementos, si no retorno -1
	if (n > 0) {
		// Guardo en maximo el primer elemento
		maximo = vector[0];
		for(int i = 0; i < n ; i++) {
			// Recorro elemento a elemento, si es mayor lo guardo
			if (vector[i] >= maximo) {
				maximo = vector[i];
				max_index = i;
			}
		}
		return max_index;
	}
	return -1;
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	
	/* Quiero obtener el menor n, para eso guardo alguno de los dos en n 
	 * y verifico si son distintos */
	int n = n1;
	if (n1 != n2) {
		// Con un operador ternario guardo el menor de los valores en n
		n = (n1 < n2) ? n1 : n2;
	}
	// Si hubiesen sido iguales, cualquier n sirve

	// Comparo elemento a elemento y retorno en caso de ser necesario
	for (int i = 0; i < n ; i++) {
		if (vector1[i] < vector2[i]) {
			return -1;
		}
		else if (vector1[i] > vector2[i]) {
			return 1;
		}
	}
	
	/* Llegado a este punto, si no se retorno nada es porque eran iguales 
	 * o no tenian elementos. Verifico cual caso es con un if */
	if (n1 != n2) {
		return (n1 < n2) ? -1 : 1;
	}
	else {
		return 0;
	}
	
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	for (int i = 0; i < n-1 ; i++) {
		int minimo = i;
		for (int j = i+1; j < n ; j++) {
			if (vector[j] < vector[minimo]) {
				minimo = j;
			}
		}
		swap(&vector[i], &vector[minimo]);
	}
}









