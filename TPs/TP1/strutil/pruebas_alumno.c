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
	cadena_tres[0] = "Perro";
	cadena_tres[1] = "";
	cadena_tres[2] = "Gato";
	spliteado = split("Perro,,Gato", ',');
	
	print_test("Split con vacio", comparar_array_cadenas(spliteado, 3, cadena_tres, 3));
	
	free(cadena_tres);
	free_strv(spliteado);

}

void test_join() {
	
	printf("###### TEST JOIN ######\n");
	
	char** cadena_tres = array_cadena_crear(4);
	cadena_tres[0] = "Auto";
	cadena_tres[1] = "Barco";
	cadena_tres[2] = "Caracol";
	cadena_tres[3] = NULL;
	
	char* joineado = join(cadena_tres, ',');
	char* resultado = "Auto,Barco,Caracol";
	print_test("Join de tres elementos", strcmp(joineado, resultado) == 0);
	//printf("%s", joineado);
	
	free(cadena_tres);
	free(joineado);
	
	char** cadena_uno = array_cadena_crear(2);
	cadena_uno[0] = "Caracol";
	cadena_uno[1] = NULL;
	
	joineado = join(cadena_uno, ',');
	
	resultado = "Caracol";
	print_test("Join de un elemento", strcmp(joineado, resultado) == 0);
	
	free(cadena_uno);
	free(joineado);
	
	char** cadena_vacios = array_cadena_crear(3);
	cadena_vacios[0] = "";
	cadena_vacios[1] = "";
	cadena_vacios[2] = NULL;
	
	joineado = join(cadena_vacios, ',');
	
	resultado = ",";
	print_test("Join de vacios", strcmp(joineado, resultado) == 0);
	
	free(cadena_vacios);
	free(joineado);
	
	char** cadena_nula = array_cadena_crear(1);
	cadena_nula[0] = NULL;
	
	joineado = join(cadena_nula, ',');
	
	print_test("Join de NULL", strcmp(joineado, "") == 0);
	
	free(cadena_nula);
	free(joineado);
}

void pruebas_tp1_alumno(void) {
	test_split();
	test_join();
}
