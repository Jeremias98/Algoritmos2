#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
 
void test_apilar() {
	
	pila_t* pila = pila_crear();
	
	print_test("Pila vacia", pila_esta_vacia(pila) == true);
	
	print_test("Apilar NULL", pila_apilar(pila, NULL) == false);
	
	int entero = 5;
	print_test("Apilar entero", pila_apilar(pila, &entero) == true && pila_ver_tope(pila) == &entero);
	
	char cadena[6] = "Perro";
	print_test("Apilar cadena", pila_apilar(pila, cadena) == true && pila_ver_tope(pila) == cadena);
	
	int* vector_vacio = malloc(20 * sizeof(int));
	print_test("Apilar vector vacio", pila_apilar(pila, vector_vacio) == true);
	
	pila_t* pila_aux = pila_crear();
	print_test("Apilar pila", pila_apilar(pila, pila_aux) == true);
	
	print_test("Pila con elementos", pila_esta_vacia(pila) == false);
	
	free(vector_vacio);
	pila_destruir(pila_aux);
	pila_destruir(pila);
	
}

void test_desapilar() {
	
	pila_t* pila = pila_crear();
	
	pila_apilar(pila, NULL);
	print_test("Desapilar sin elementos", pila_desapilar(pila) == NULL);
	
	pila_apilar(pila, "Perro");
	print_test("Desapilar un elemento", pila_desapilar(pila) == NULL);
	
	pila_destruir(pila);
	
}

void pruebas_pila_alumno() {
	
    pila_t* ejemplo = NULL;

    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    
    test_apilar();
    test_desapilar();
}
