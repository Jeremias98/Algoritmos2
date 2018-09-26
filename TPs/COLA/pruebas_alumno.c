#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void verificar_cola_vacia(cola_t* cola) {
	print_test("La cola esta vacia", cola_esta_vacia(cola));
	print_test("Ver primero es NULL", cola_ver_primero(cola) == NULL);
	print_test("Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
}

void destruir_vector(void* vector) {
	free(vector);
}

void test_cola_vacia() {
	
	printf("\n### TEST COLA VACIA ###\n");
	
	cola_t* cola = cola_crear();
	
	verificar_cola_vacia(cola);
	
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
	
	printf("La cola se comporta como vacia\n");
	verificar_cola_vacia(cola);
	
	cola_destruir(cola, NULL);
	
}

void test_destruir() {
	
	printf("\n### TEST DESTRUIR ###\n");
	
	cola_t* cola = cola_crear();
	
	int* vector = malloc(5 * sizeof(int));
	print_test("Encolar un vector", cola_encolar(cola, vector));
	
	printf("Se destruye el vector con free() pasado por parametro => No hay errores de Valgrind\n");
	cola_destruir(cola, free);
	
	cola_t* cola2 = cola_crear();
	
	int* vector2 = malloc(5 * sizeof(int));
	for (int i = 0; i <  5; i++) {
		vector2[i] = i;
	}
	print_test("Encolar un vector con elementos", cola_encolar(cola2, vector2));
	printf("Se destruye el vector con una funcion propia  => No hay errores de Valgrind\n");
	cola_destruir(cola2, destruir_vector);
	
}

void test_volumen() {
	
	printf("\n### TEST VOLUMEN ###\n");
	
	cola_t* cola_de_estaticos = cola_crear();
	
	size_t volumen = 10000;
	bool flag_valor = false;
	bool flag_cola = false;
	
	int* vector_entero = malloc(volumen * sizeof(int));
	
	printf("Se encola un volumen de %ld elementos\n", volumen);
	
	for (int i = 0 ; i < volumen ; i++) {
		vector_entero[i] = i;
		flag_cola = cola_encolar(cola_de_estaticos, &vector_entero[i]);
		flag_valor = (cola_ver_primero(cola_de_estaticos) == &vector_entero[0]);
	}
	
	print_test("Se encolo correctamente", flag_cola);
	print_test("Los valores fueron los esperados", flag_valor);
	
	free(vector_entero);
	
	printf("Se desencolan %ld elementos\n", volumen);
	
	for (int i = 0 ; i < volumen ; i++) {
		void* first = cola_ver_primero(cola_de_estaticos);
		flag_cola = (cola_desencolar(cola_de_estaticos) == first);
	}
	
	print_test("Se desencolan correctamente", flag_cola);
	
	printf("Verifico si la cola se comporta como vacia\n");
	
	verificar_cola_vacia(cola_de_estaticos);
	
	cola_destruir(cola_de_estaticos, NULL);
	
	cola_t* cola_de_dinamicos = cola_crear();
	printf("Se encolan %ld elementos que requieren free\n", volumen);
	
	void* first;
	for (int i = 0 ; i < volumen ; i++) {
		void* v = malloc(sizeof(void*));
		if (i == 0) first = v;
		flag_cola = cola_encolar(cola_de_dinamicos, v);
		flag_valor = (cola_ver_primero(cola_de_dinamicos) == first);
	}
	
	print_test("Se encolo correctamente", flag_cola);
	print_test("Los valores fueron los esperados", flag_valor);
	
	printf("Desencolo %ld elementos (la mitad)\n", volumen/2);
	for (int i = 0 ; i < volumen/2 ; i++) {
		first = cola_ver_primero(cola_de_dinamicos);
		flag_cola = (cola_desencolar(cola_de_dinamicos) == first);
		free(first);
	}
	
	print_test("Se desencolan correctamente", flag_cola);
	
	printf("Destruyo el resto\n");
	cola_destruir(cola_de_dinamicos, free);
	
}

void pruebas_cola_alumno() {
	test_cola_vacia();
    test_encolar();
    test_desencolar();
    test_destruir();
    test_volumen();
}
