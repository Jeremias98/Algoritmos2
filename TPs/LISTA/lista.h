#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

// ##### DEFINICION DE LOS TIPOS DE DATO ##### //

// Lista
struct lista;
typedef struct lista lista_t;

// Iterador externo de la lista
typedef struct lista_iter lista_iter_t;

// ##### PRIMITIVAS DE LA LISTA ##### //

// Crea una lista
// Post: Devuelve una nueva lista vacia
lista_t *lista_crear(void);

// Retorna true o false dependiendo si la lista tiene o no elementos
// Pre: La lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento al principio de la lista. Retorna false en caso de error.
// Pre: La lista fue creada
// Post: Se agrego un nuevo elemento al principio de la lista
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un elemento al final de la lista. Retorna false en caso de error.
// Pre: La lista fue creada
// Post: Se agrego un nuevo elemento al final de la lista
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Se quita el elemento que esta al principio de la lista. Si tiene elementos
// retorna el elemento quitado, si esta vacia NULL
// Pre: La lista fue creada
// Post: La lista contiene un elemento menos al principio, si no estaba vacia
void *lista_borrar_primero(lista_t *lista);

// Retorna el primer elemento de la lista, NULL si esta vacia
// Pre: La lista fue creada
// Post: Se retorno el valor del primer elemento de la lista, NULL si estaba vacia
void *lista_ver_primero(const lista_t *lista);

// Retorna el ultimo elemento de la lista, NULL si esta vacia
// Pre: La lista fue creada
// Post: Se retorno el valor del ultimo elemento de la lista, NULL si estaba vacia
void *lista_ver_ultimo(const lista_t* lista);

// Retorna la cantidad de elementos (largo) que tiene la lista
// Pre: La lista fue creada
// Post: Se retorno el largo de la lista
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si recibe por parametro destruir_dato, le aplica esa funcion
// a cada elemento de la lista.
// Pre: La lista fue creada
// Post: Se elimino la lista y todos sus elementos
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Recorre la lista elemento a elemento
// a cada elemento de la lista.
// Pre: La lista fue creada
// Post: Se elimino la lista y todos sus elementos
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// ##### PRIMITIVAS DEL ITERADOR ##### //
lista_iter_t *lista_iter_crear(lista_t *lista);

bool lista_iter_avanzar(lista_iter_t *iter);

bool lista_iter_al_final(const lista_iter_t *iter);

void *lista_iter_ver_actual(const lista_iter_t *iter);

bool lista_iter_insertar(lista_iter_t *iter, void *dato);

void *lista_iter_borrar(lista_iter_t *iter);

void lista_iter_destruir(lista_iter_t *iter);

// ##### PRUEBAS UNITARIAS ##### //
void pruebas_lista_alumno(void);


#endif // LISTA_H
