#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo {
	void* dato;
	struct nodo* prox;
} nodo_t;

struct lista {
	nodo_t* prim;
	nodo_t* ult;
	size_t largo;
};

typedef struct lista_iter {
	nodo_t* anterior;
	nodo_t* actual;
	lista_t* lista;
}lista_iter_t;

nodo_t* nodo_crear(void) {
	
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if (nodo == NULL) return NULL;
	
	nodo->dato = NULL;
	nodo->prox = NULL;
	
	return nodo;
	
}

// #### PRIMITIVAS DE LA LISTA #### //
lista_t *lista_crear(void) {
	
	lista_t* lista = malloc(sizeof(lista_t));
	
	if (lista == NULL) return NULL;
	
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	
	return lista;
	
}

bool lista_esta_vacia(const lista_t *lista) {
	return (lista->largo == 0);
}

void *lista_ver_primero(const lista_t *lista) {
	return lista_esta_vacia(lista) ? NULL : lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
	return lista_esta_vacia(lista) ? NULL : lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	
	nodo_t* nodo = nodo_crear();
	
	if (nodo == NULL) return false;
	
	nodo->dato = dato;
	nodo->prox = lista->prim;
	
	if (lista_esta_vacia(lista)) {
		lista->ult = nodo;
		lista->ult->prox = NULL;
	}
	
	lista->prim = nodo;
	
	lista->largo++;
	
	return true;
	
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	
	nodo_t* nodo = nodo_crear();
	
	if (nodo == NULL) return false;
	
	nodo->dato = dato;
	
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo;
		lista->prim->prox = nodo;
	}
	else {
		lista->ult->prox = nodo;
	}
	
	lista->ult = nodo;
	lista->ult->prox = NULL;
	
	lista->largo++;
	
	return true;
	
}

void *lista_borrar_primero(lista_t *lista) {
	
	if (lista_esta_vacia(lista)) return NULL;
	
	nodo_t* nodo_quitado = lista->prim;
	void* elemento_quitado = lista_ver_primero(lista);
	
	lista->prim = lista->prim->prox;
	
	free(nodo_quitado);
	
	lista->largo--;
	
	return elemento_quitado;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	
	nodo_t* nodo = lista->prim;
	while (nodo != NULL) {
		
		nodo_t* proximo = nodo->prox;
		
		if (destruir_dato != NULL) {
			destruir_dato(nodo->dato);
		}
	
		free(nodo);
		
		nodo = (lista->prim == lista->ult) ? NULL : proximo;
	}
	
	free(lista);
	
}

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	
	nodo_t* actual = lista->prim; 
	bool respuesta_visitar = true;
	while (actual != NULL && respuesta_visitar) {
		if (visitar != NULL) {
			respuesta_visitar = visitar(actual->dato, extra);
		}
		actual = actual->prox;
	}
}

// #### PRIMITIVAS DEL ITERADOR EXTERNO #### //

lista_iter_t *lista_iter_crear(lista_t *lista) {
	
	lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
	
	if (iterador == NULL) return NULL;
	
	iterador->lista =  lista;
	iterador->anterior = NULL;
	iterador->actual = lista->prim;
	
	return iterador;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return (iter->actual == NULL);
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	
	if (lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)) return false;
	
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	
	return true;
	
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	
	nodo_t* nodo = nodo_crear();
	
	if (nodo == NULL) return false;
	
	nodo->dato = dato;
	nodo->prox = iter->actual;
	
	if (iter->anterior != NULL) {
		iter->anterior->prox = nodo;
	}
	
	iter->actual = nodo;
	
	// Caso lista vacia
	if (lista_esta_vacia(iter->lista)) {
		iter->lista->prim = iter->actual;
		iter->lista->ult = iter->actual;
		iter->lista->prim->prox = iter->actual;
		iter->lista->ult->prox = NULL;
	}
	else {
		// Caso con un elemento
		if (iter->lista->ult == iter->lista->prim) {
			// Si se inserto a lo ultimo...
			if (iter->anterior == iter->lista->ult) {
				iter->lista->prim->prox = iter->actual;
				iter->lista->ult = iter->actual;
			}
			else {
				iter->lista->ult = iter->lista->prim;
				iter->lista->prim = iter->actual;
				iter->lista->prim->prox = iter->lista->ult;
			}
			
		}
		// Caso mas de un elemento
		// Si se inserto a lo ultimo...
		else if (iter->anterior == iter->lista->ult) {
			iter->lista->ult = iter->actual;
		}
		// Si se inserto al principio...
		else if (iter->lista->prim == iter->actual->prox) {
			iter->lista->prim = iter->actual;
		}
		
	}
	
	
	iter->lista->largo++;
	
	return true;
	
}

void *lista_iter_borrar(lista_iter_t *iter) {
	
	if (lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)) return NULL;
	
	nodo_t* nodo_quitado = iter->actual;
	
	void* elemento_quitado = iter->actual->dato;
	
	if (nodo_quitado == iter->lista->prim) {
		iter->actual = iter->actual->prox;
		iter->lista->prim = iter->actual;
	}
	else if (nodo_quitado == iter->lista->ult) {
		iter->lista->ult = iter->anterior;
		iter->actual = NULL;
		iter->anterior = iter->lista->ult;
	}
	else {
		iter->actual = iter->actual->prox;
		iter->anterior->prox = iter->actual;
	}
	
	
	free(nodo_quitado);
	
	iter->lista->largo--;
	
	return elemento_quitado;
	
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	return (iter->lista->largo > 0 && !lista_iter_al_final(iter)) ? iter->actual->dato : NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}




