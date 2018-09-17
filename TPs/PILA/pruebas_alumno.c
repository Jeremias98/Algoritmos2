#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void test_pila_vacia() {
	
	printf("\n### TEST PILA VACIA ###\n");
	
	pila_t* pila = pila_crear();
	
	print_test("La pila esta vacia", pila_esta_vacia(pila) == true);
	
	print_test("Ver tope de la pila vacia", pila_ver_tope(pila) == NULL);
	
	print_test("Desapilar sin elementos", pila_desapilar(pila) == NULL);
	
	pila_destruir(pila);
}

void test_apilar() {
	
	printf("\n### TEST APILAR ###\n");
	
	pila_t* pila = pila_crear();
	
	print_test("Apilar NULL", pila_apilar(pila, NULL) == true);
	print_test("El tope es NULL", pila_ver_tope(pila) == NULL);
	
	int entero = 5;
	print_test("Apilar entero", pila_apilar(pila, &entero) == true);
	print_test("El tope es ese entero", pila_ver_tope(pila) == &entero);
	
	char cadena[6] = "Perro";
	print_test("Apilar cadena", pila_apilar(pila, cadena) == true && pila_ver_tope(pila) == cadena);
	print_test("El tope es esa cadena", pila_ver_tope(pila) == cadena);
	
	int* vector = malloc(20 * sizeof(int));
	
	for (int i = 0; i < 20 ; i++) {
		vector[i] = i;
	}
	
	print_test("Apilar vector lleno", pila_apilar(pila, vector) == true);
	
	pila_t* pila_aux = pila_crear();
	print_test("Apilar pila", pila_apilar(pila, pila_aux) == true);
	
	print_test("La pila contiene elementos", pila_esta_vacia(pila) == false);
	
	free(vector);
	pila_destruir(pila_aux);
	pila_destruir(pila);
	
}

void test_desapilar() {
	
	printf("\n### TEST DESAPILAR ###\n");
	
	pila_t* pila = pila_crear();
	
	int numero = 5;
	pila_apilar(pila, &numero);
	print_test("Desapilar un elemento", pila_desapilar(pila) == &numero);
	
	int* vector = malloc(20 * sizeof(int));
	
	for (int i = 0; i < 20 ; i++) {
		vector[i] = i;
	}
	
	pila_apilar(pila, vector);
	
	print_test("Desapilar vector", pila_desapilar(pila) == vector);
	
	pila_t* pila_aux = pila_crear();
	pila_apilar(pila, pila_aux);
	print_test("Desapilar pila", pila_desapilar(pila) == pila_aux);
	
	print_test("La pila esta vacia", pila_esta_vacia(pila) == true);
	
	free(vector);
	pila_destruir(pila_aux);
	pila_destruir(pila);
	
}

void test_volumen() {
	
	printf("\n### TEST VOLUMEN ###\n");
	
	pila_t* pila = pila_crear();
	
	size_t volumen = 10000;
	int* vector = malloc(volumen * sizeof(int));
	
	bool flag_apilar = true;
	bool flag_valor = true;
	for (int i = 0; i < volumen ; i++) {
		vector[i] = i;
		flag_apilar &= pila_apilar(pila, &vector[i]);
		flag_valor &= (pila_ver_tope(pila) == &vector[i]);
	}
	
	printf("Apilar volumen de %li elementos\n", volumen);
	print_test("Se apilaron correctamente", flag_apilar);
	print_test("Los topes fueron correctos", flag_valor);
	print_test("La pila contiene elementos", pila_esta_vacia(pila) == false);
	
	void* elemento_tope = NULL;
	for (int i = 0; i < volumen ; i++) {
		elemento_tope = pila_ver_tope(pila);
		flag_valor &= (pila_desapilar(pila) == elemento_tope);
	}
	
	printf("Desapilar volumen de %li elementos\n", volumen);
	print_test("La pila esta vacia", pila_esta_vacia(pila));
	print_test("Se devolvieron elementos correctos", flag_valor);
	print_test("Ver tope de la pila vacia", pila_ver_tope(pila) == NULL);
	print_test("Desapilar sin elementos", pila_desapilar(pila) == NULL);
	
	printf("Vuelvo a apilar para corroborar el redimensionamiento al desapilar\n");
	// No apilo la misma cantidad que antes, ni los mismos valores
	for (int i = 0; i < volumen / 2 ; i++) {
		vector[i] = vector[i] + i;
		flag_apilar &= pila_apilar(pila, &vector[i]);
		flag_valor &= (pila_ver_tope(pila) == &vector[i]);
	}
	
	print_test("Los topes fueron correctos", flag_valor);
	print_test("La pila contiene elementos", pila_esta_vacia(pila) == false);
	
	free(vector);
	pila_destruir(pila);
}

void pruebas_pila_alumno() {
	test_pila_vacia();
    test_apilar();
    test_desapilar();
    test_volumen();
}
