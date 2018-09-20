#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void test_cola_vacia() {
	
	printf("\n### TEST COLA VACIA ###\n");
	
	cola_t* cola = cola_crear();
	
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	print_test("Ver primero es NULL", cola_ver_primero(cola) == NULL);
	print_test("Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
	
	cola_destruir(cola, NULL);
}

void test_encolar() {
	
	printf("\n### TEST ENCOLAR ###\n");
	
	cola_t* cola = cola_crear();
	
	int entero = 5;
	print_test("Encolar un entero", cola_encolar(cola, &entero));
	print_test("Pido el primero", cola_ver_primero(cola) == &entero);
	
	print_test("Encolar un NULL", cola_encolar(cola, NULL));
	print_test("Pido el primero", cola_ver_primero(cola) == &entero);
	
	char cadena[6] = "Perro";
	print_test("Encolar una cadena", cola_encolar(cola, cadena));
	print_test("Pido el primero", cola_ver_primero(cola) == &entero);
	
	cola_destruir(cola, NULL);
	
}

void test_desencolar() {
	
	printf("\n### TEST DESENCOLAR ###\n");
	
	cola_t* cola = cola_crear();
	
	printf("Encolo tres cosas y las desencolo\n");
	int entero = 5;
	print_test("Encolar un entero", cola_encolar(cola, &entero) && cola_ver_primero(cola) == &entero);
	
	print_test("Encolar un NULL", cola_encolar(cola, NULL) && cola_ver_primero(cola) == &entero);
	
	char cadena[6] = "Perro";
	print_test("Encolar una cadena", cola_encolar(cola, cadena) && cola_ver_primero(cola) == &entero);
	
	print_test("Desencolo y devuelve el entero", cola_desencolar(cola) == &entero);
	print_test("Desencolo y devuelve NULL", cola_desencolar(cola) == NULL);
	print_test("Desencolo y devuelve la cadena", cola_desencolar(cola) == cadena);
	
	cola_destruir(cola, NULL);
	
}

void pruebas_cola_alumno() {
	test_cola_vacia();
    test_encolar();
    test_desencolar();
}
