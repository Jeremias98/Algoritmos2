/*
 * Universidad de Buenos Aires, Facultad de ingenieria
 * Alumno: Ramirez Jeremias Nicolas
 * Padron: 102878
 * Titulo: TP0
 * */

#include "tp0.h"

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	// Creo una variable auxiliar y hago el intercambio de valores
	int aux = *x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {
	
	int max_index = 0;
	
	if (n <= 0) {
		return -1;
	}
	
	for(int i = 0; i < n ; i++) {
		if (vector[i] >= vector[max_index]) {
			max_index = i;
		}
	}
	
	return max_index;
	
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	
	int n = n1;
	if (n1 != n2) {
		n = (n1 < n2) ? n1 : n2;
	}

	for (int i = 0; i < n ; i++) {
		if (vector1[i] < vector2[i]) {
			return -1;
		}
		else if (vector1[i] > vector2[i]) {
			return 1;
		}
	}
	
	if (n1 != n2) {
		return (n1 < n2) ? -1 : 1;
	}
	
	return 0;
	
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n) {
	
	/* Se reutiliza codigo implementando la funcion maximo en el algoritmo de seleccion */
	for (int i = 0; i < n-1 ; i++) {
		int max = maximo(vector, n-i);
		swap(&vector[n-1-i], &vector[max]);
	}
	
	
}









