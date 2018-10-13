#include "strutil.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool comparar_array_cadenas(char** cadena_1, int largo_1, char** cadena_2, int largo_2) {
	
	if (largo_1 != largo_2) return false;
	
	bool son_iguales = true;
	
	for (int i = 0; i < largo_1; i++)
	{
		son_iguales = strcmp(cadena_1[i], cadena_2[i]) == 0 ? true : false;
	}
	
	return son_iguales;
	
}

char** array_cadena_crear(size_t tam) {
	char** array = malloc(tam * sizeof(char*));
	if (array == NULL) return NULL;
	return array;
}

void test_split() {
	
	printf("###### TEST SPLIT ######\n");
	
	char** cadena_vacia = array_cadena_crear(1);
	cadena_vacia[0] = "";
	char** spliteado = split("", ',');
	
	print_test("Split de cadena vacia", comparar_array_cadenas(spliteado, 1, cadena_vacia, 1));
	
	free(cadena_vacia);
	free_strv(spliteado);
	
	
	char** cadena_sin_coma = array_cadena_crear(1);
	cadena_sin_coma[0] = "Perro";
	spliteado = split("Perro", ',');
	
	print_test("Split sin separador", comparar_array_cadenas(spliteado, 1, cadena_sin_coma, 1));
	
	free(cadena_sin_coma);
	free_strv(spliteado);
	
	char** cadena_tres = array_cadena_crear(4);
	cadena_tres[0] = "Auto";
	cadena_tres[1] = "Barco";
	cadena_tres[2] = "Caracol";
	cadena_tres[3] = NULL;
	
	char* joineado = join(cadena_tres, ',');
	
	printf("%s\n", joineado);
	
	free(cadena_tres);
	
	free(joineado);
	
	//print_test("Split sin separador", comparar_array_cadenas(spliteado, 1, cadena_sin_coma, 1));
	
}

void pruebas_tp1_alumno(void) {
	test_split();
}
