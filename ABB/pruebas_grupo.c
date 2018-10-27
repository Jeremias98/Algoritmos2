#include "abb.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_numeros(const char* str1, const char* str2) {
	
	if (atoi(str1) > atoi(str2)) return -1;
	else if (atoi(str1) < atoi(str2)) return 1;
	else return 0;
	
}

void test_crear() {
	
	abb_t* arbol = abb_crear(strcmp, NULL);
	
	char* clave_1 = "14";
	char* dato_1 = "Perro";
	
	char* clave_2 = "9";
	char* dato_2 = "Gato";
	
	char* clave_3 = "1";
	char* dato_3 = "Jirafa";
	
	print_test("Obtener es NULL", abb_obtener(arbol, clave_1) == NULL);
	print_test("Borrar es NULL", abb_borrar(arbol, clave_1) == NULL);
	
	print_test("Guardar elemento 1", abb_guardar(arbol, clave_1, dato_1));
	print_test("Obtener elemento 1", abb_obtener(arbol, clave_1) == dato_1);
	print_test("Cantidad es 1", abb_cantidad(arbol) == 1);
	
	print_test("Guardar elemento 2", abb_guardar(arbol, clave_2, dato_2));
	print_test("Obtener elemento 2", abb_obtener(arbol, clave_2) == dato_2);
	print_test("Cantidad es 2", abb_cantidad(arbol) == 2);
	
	print_test("Guardar elemento 3", abb_guardar(arbol, clave_3, dato_3));
	print_test("Obtener elemento 3", abb_obtener(arbol, clave_3) == dato_3);
	print_test("Cantidad es 3", abb_cantidad(arbol) == 3);
	
	print_test("Pertenece 1", abb_pertenece(arbol, clave_1));
	print_test("Pertenece 2", abb_pertenece(arbol, clave_2));
	print_test("Pertenece 3", abb_pertenece(arbol, clave_3));
	
	printf("Inorder: \n");
	abb_in_order(arbol, NULL, NULL);	
	
	print_test("Borrar 1 (raiz)", abb_borrar(arbol, clave_1) == dato_1);
	print_test("Cantidad es 2", abb_cantidad(arbol) == 2);
	
	printf("Inorder: \n");
	abb_in_order(arbol, NULL, NULL);	
	
	print_test("Borrar 2", abb_borrar(arbol, clave_2) == dato_2);
	print_test("Cantidad es 1", abb_cantidad(arbol) == 1);
	
	printf("Inorder: \n");
	abb_in_order(arbol, NULL, NULL);
	
	print_test("Borrar 3", abb_borrar(arbol, clave_3) == dato_3);
	print_test("Cantidad es 0", abb_cantidad(arbol) == 0);
	
	
	abb_destruir(arbol);
	
}


void pruebas_abb_alumno() {
	test_crear();
}
