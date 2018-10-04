#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void destruir_dato(void* dato) {
	free(dato);
}

bool imprimir_un_item(void *elemento, void *extra)
{
    // Sabemos que ‘extra’ es un entero, por tanto le podemos hacer un cast.
    int *contador = extra;
    printf("%d. %s\n", ++(*contador), (char*) elemento);

    return true; // seguir iterando
}

void imprimir_iter_interno(lista_t *lista)
{
    int num_items = 0;
    lista_iterar(lista, imprimir_un_item, &num_items);
    printf("La lista tiene %d ítems\n", num_items);
}

void verificar_lista_vacia(lista_t* lista) {
	print_test("La lista esta vacia", lista_esta_vacia(lista));
	print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
	print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
	print_test("Borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
	print_test("El largo es 0", lista_largo(lista) == 0);
}

void test_lista_vacia() {
	
	printf("\n###### TEST LISTA VACIA ######\n");
	
	lista_t* lista = lista_crear();
	
	verificar_lista_vacia(lista);
	
	lista_destruir(lista, NULL);
	
}

void test_un_elemento() {
	
	printf("\n###### TEST UN ELEMENTO ######\n");
	
	lista_t* lista = lista_crear();
	
	int entero = 5;
	print_test("Inserto un entero al principio", lista_insertar_primero(lista, &entero));
	print_test("El largo es 1", lista_largo(lista) == 1);
	
	print_test("Veo el primero y es ese entero", lista_ver_primero(lista) == &entero);
	print_test("Veo el ultimo y es ese entero", lista_ver_ultimo(lista) == &entero);
	
	print_test("Borro el primero", lista_borrar_primero(lista) == &entero);
	printf("Verifico que la lista este vacia\n");
	verificar_lista_vacia(lista);
	
	char cadena[6] = "Perro";
	print_test("Inserto una cadena al final", lista_insertar_ultimo(lista, cadena));
	print_test("El largo es 1", lista_largo(lista) == 1);
	
	print_test("Veo el primero y es esa cadena", lista_ver_primero(lista) == cadena);
	print_test("Veo el ultimo y es esa cadena", lista_ver_ultimo(lista) == cadena);
	
	print_test("Borro el primero", lista_borrar_primero(lista) == cadena);
	printf("Verifico que la lista este vacia\n");
	verificar_lista_vacia(lista);
	
	lista_destruir(lista, NULL);
	
}

void test_varios_elementos() {
	
	printf("\n###### TEST VARIOS ELEMENTOS ######\n");
	
	lista_t* lista = lista_crear();
	
	int entero = 5;
	print_test("Inserto un entero al principio", lista_insertar_primero(lista, &entero));
	print_test("El largo es 1", lista_largo(lista) == 1);
	
	print_test("Veo el primero y es ese entero", lista_ver_primero(lista) == &entero);
	print_test("Veo el ultimo y es ese entero", lista_ver_ultimo(lista) == &entero);
	
	char cadena[6] = "Perro";
	print_test("Inserto una cadena", lista_insertar_ultimo(lista, cadena));
	
	print_test("El largo es 2", lista_largo(lista) == 2);
	
	print_test("Veo el primero y es el entero", lista_ver_primero(lista) == &entero);
	print_test("Veo el ultimo y es la cadena", lista_ver_ultimo(lista) == cadena);
	
	lista_destruir(lista, NULL);
	
}

void test_destruir() {
	
	printf("\n###### TEST DESTRUIR ######\n");
	
	lista_t* lista_free = lista_crear();
	
	int* array = malloc(5 * sizeof(int));
	
	print_test("Inserto un array de enteros al principio", lista_insertar_primero(lista_free, array));
	
	print_test("Veo el primero y es ese array", lista_ver_primero(lista_free) == array);
	print_test("Veo el ultimo y es ese array", lista_ver_ultimo(lista_free) == array);
	
	printf("Destruyo pasando free() por parametro\n");
	lista_destruir(lista_free, free);
	
	printf("Creo una nueva lista y agrego varios vectores con malloc\n");
	lista_t* lista_funcion = lista_crear();
	
	printf("Insertando al principio: \n");
	bool insertado_ok = false;
	for (int i = 1 ; i <= 5 ; i++) {
				
		int* vector = malloc(5 * sizeof(int));
		
		insertado_ok = lista_insertar_primero(lista_funcion, vector) && lista_largo(lista_funcion) == i;
	}
	
	print_test("Se insertaron correctamente y su largo es correcto", insertado_ok);
	
	printf("Insertando al final: \n");
	insertado_ok = false;
	for (int i = 1 ; i <= 5 ; i++) {
				
		int* vector = malloc(5 * sizeof(int));
		
		insertado_ok = lista_insertar_ultimo(lista_funcion, vector) && lista_largo(lista_funcion) ==  (5 + i);
	}
	
	print_test("Se insertaron correctamente y su largo es correcto", insertado_ok);
	
	printf("Destruyo la lista con una funcion propia por parametro\n");
	lista_destruir(lista_funcion, destruir_dato);
	
}

void test_volumen() {
	
	printf("\n###### TEST VOLUMEN ######\n");
	
	size_t volumen = 10000;
	
	bool inserto_ok = true;
	
	lista_t* lista = lista_crear();
	
	printf("Inserto un volumen de %ld elementos al principio\n", volumen);
	
	for (int i = 0 ; i < volumen && inserto_ok ; i++) {
		inserto_ok = lista_insertar_primero(lista, &i);
	}
	
	print_test("Se insertaron correctamente al principio", inserto_ok);
	
	printf("Inserto un volumen de %ld elementos al final\n", volumen);
	inserto_ok = true;
	for (int i = 0 ; i < volumen && inserto_ok ; i++) {
		inserto_ok = lista_insertar_ultimo(lista, &i);
	}
	print_test("Se insertaron correctamente al final", inserto_ok);
	
	printf("Vacio la lista\n");
	inserto_ok = true;
	for (int i = 0 ; i < 2 * volumen && inserto_ok ; i++) {
		//int* retorno = (*int)lista_borrar_primero(lista);
		//inserto_ok = lista_borrar_primero(lista);
		void* primero = lista_ver_primero(lista);
		inserto_ok = (lista_borrar_primero(lista) == primero);
	}
	print_test("Se borraron correctamente", inserto_ok);
	
	printf("Verifico si la lista esta vacia\n");
	verificar_lista_vacia(lista);
	
	lista_destruir(lista, NULL);
	
}

void test_iterador_interno() {
	
	printf("\n###### TEST ITERADOR INTERNO ######\n");
	
	lista_t* lista = lista_crear();
	
	printf("Uso el iterador con la lista vacia\n");
	imprimir_iter_interno(lista);
	
	print_test("Inserto algunas cosas", lista_insertar_ultimo(lista, "Arbol") 
		&& lista_insertar_ultimo(lista, "Barco") 
		&& lista_insertar_ultimo(lista, "Caracol")
		&& lista_insertar_ultimo(lista, "Diario"));
	
	imprimir_iter_interno(lista);
	
	lista_destruir(lista, NULL);
	
}

void test_iterador_externo_general() {
	
	printf("\n###### TEST ITERADOR EXTERNO GENERAL ######\n");
	
	lista_t* lista = lista_crear();
	
	print_test("Inserto algunas cosas", 
		lista_insertar_ultimo(lista, "Barco") 
		&& lista_insertar_ultimo(lista, "Caracol")
		&& lista_insertar_ultimo(lista, "Diario"));
	
	lista_iter_t* iter = lista_iter_crear(lista);
	
	char primero[6] = "Arbol";
	
	print_test("Inserto con el iterador al principio", lista_iter_insertar(iter, primero));
	
	print_test("Veo el primero", lista_ver_primero(lista) == primero);
	
	print_test("Elimino con el iterador al principio", lista_iter_borrar(iter));
	
	int num_items = 0;

    while (!lista_iter_al_final(iter))
    {
		
		if (num_items == 3) 
			print_test("Inserto con el iterador al medio", lista_iter_insertar(iter, "Insertado al medio"));
		
        char *elemento = lista_iter_ver_actual(iter);
        printf("%d. %s\n", ++num_items, elemento);
        
        if (num_items == 2)
			print_test("Elimino con el iterador al medio", lista_iter_borrar(iter));

        lista_iter_avanzar(iter);
    }
    printf("La lista contiene %d ítems\n", num_items);
    
    print_test("Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    
    char ultimo[9] = "Elefante";
	
	print_test("Inserto con el iterador al final", lista_iter_insertar(iter, ultimo));
	print_test("Veo el ultimo", lista_ver_ultimo(lista) == ultimo);
	
	print_test("Elimino con el iterador al final", lista_iter_borrar(iter));
	
	lista_iter_destruir(iter);
	lista_destruir(lista, NULL);
	
}

void test_iterador_externo_profundo() {
	
	printf("\n###### TEST ITERADOR EXTERNO PROFUNDO ######\n");
	
	lista_t* lista = lista_crear();
	lista_iter_t* iter = lista_iter_crear(lista);
	
	int elemento_1 = 1;
	print_test("Inserto en la lista vacia", lista_iter_insertar(iter, &elemento_1));
	print_test("Veo el primero", lista_ver_primero(lista) == &elemento_1);
	
	int elemento_2 = 2;
	print_test("Inserto al final con primitiva de la lista", lista_insertar_ultimo(lista, &elemento_2));
	
	print_test("Veo el ultimo", lista_ver_ultimo(lista) == &elemento_2);
	print_test("Veo el primero", lista_ver_primero(lista) == &elemento_1);
	
	printf("Vacio la lista\n");
	while (!lista_iter_al_final(iter)) {
		lista_iter_borrar(iter);
	}
	
	verificar_lista_vacia(lista);
	
	print_test("Borrar es NULL", lista_iter_borrar(iter) == NULL);
	
	bool inserto_ok = true;
	int* arreglo = malloc(3 * sizeof(int));
	for (int i = 0 ; i < 3 && inserto_ok; i++) {
		arreglo[i] = i;
		inserto_ok = lista_iter_insertar(iter, &arreglo[i]);
	}
	
	print_test("Inserto 3 elementos", inserto_ok);
	
	print_test("Veo el actual", lista_iter_ver_actual(iter) == &arreglo[2]);
	
	lista_iter_avanzar(iter);
	
	print_test("Avanzo y borro al medio", lista_iter_borrar(iter) == &arreglo[1]);
	
	print_test("Compruebo el primero", lista_ver_primero(lista) == &arreglo[2]);
	print_test("Compruebo el ultimo", lista_ver_ultimo(lista) == &arreglo[0]);
	
	print_test("Borro y queda un solo elemento", lista_iter_borrar(iter) == &arreglo[0]);
	
	printf("Avanzo hasta el final\n");
	while (!lista_iter_al_final(iter)) {
		lista_iter_avanzar(iter);
	}
	
	print_test("Avanzar es false", !lista_iter_avanzar(iter));
	
	print_test("Borrar es NULL", lista_iter_borrar(iter) == NULL);
	
	char cadena[10] = "Elemento";
	print_test("Inserto al final con la primitiva de la lista", lista_insertar_ultimo(lista, cadena));
	
	print_test("Inserto al final", lista_insertar_ultimo(lista, cadena));
	
	print_test("Veo el final con la primitiva de la lista", lista_ver_ultimo(lista) == cadena);
	
	
	printf("Creo un nuevo iterador\n");
	lista_iter_t* iter2 = lista_iter_crear(lista);
	
	print_test("Veo el actual", lista_iter_ver_actual(iter2) == &arreglo[2]);
	
	print_test("Puedo avanzar", lista_iter_avanzar(iter2));
	
	print_test("Veo el actual", lista_iter_ver_actual(iter2) == cadena);
	
	free(arreglo);
	lista_iter_destruir(iter);
	lista_iter_destruir(iter2);
	lista_destruir(lista, NULL);
	
}

void pruebas_lista_alumno(void) {
	test_lista_vacia();
	test_un_elemento();
	test_varios_elementos();
	test_destruir();
	test_volumen();
	test_iterador_interno();
	test_iterador_externo_general();
	test_iterador_externo_profundo();
}
