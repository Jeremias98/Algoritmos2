#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"

#include <string.h>
#include <stdio.h>

typedef struct abb_nodo {
	struct abb_nodo* izq;
	struct abb_nodo* der;
	char* clave;
	void* dato;
} abb_nodo_t;

typedef struct abb {
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
} abb_t;

typedef struct abb_iter {
	pila_t* pila;
} abb_iter_t;

abb_nodo_t* abb_nodo_crear(const char* clave, void* dato) {
	
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if (!nodo) return NULL;
	
	nodo->izq = NULL;
	nodo->der = NULL;
	
	nodo->clave = strdup(clave);
	nodo->dato = dato;
	
	return nodo;
	
}

void abb_nodo_destruir(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
	
	if (!nodo) return;
	
	free(nodo->clave);
	if (destruir_dato) destruir_dato(nodo->dato);
	free(nodo);
	
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	
	abb_t* arbol = malloc(sizeof(abb_t));
	if (!arbol) return NULL;
	
	arbol->raiz = NULL;
	
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	
	arbol->cantidad = 0;
	
	return arbol;
	
}

abb_nodo_t* abb_insertar(abb_t *arbol, abb_nodo_t* nodo, const char *clave, void *dato) {
	
	if (!nodo) {
		arbol->cantidad++;
		return abb_nodo_crear(clave, dato);
	}
	
	if (arbol->cmp(nodo->clave, clave) == 0) {
		nodo = abb_insertar(arbol, NULL, clave, dato);
	}
	else if (arbol->cmp(nodo->clave, clave) > 0) { 
		nodo->der = abb_insertar(arbol, nodo->der, clave, dato);
	}
	else { 
		nodo->izq = abb_insertar(arbol, nodo->izq, clave, dato);
	}
	
	return nodo;
	
}

abb_nodo_t* get_reemplazante(abb_nodo_t* nodo) {
	
	abb_nodo_t* actual = nodo;
	
	while(actual->izq) {
		actual = actual->izq;
	}
	
	return actual;
	
}

size_t get_cantidad_hijos(abb_nodo_t* nodo) {
	
	size_t hijos = 0;
	
	if (nodo->der) hijos++;
	if (nodo->izq) hijos++;
	
	return hijos;
}

abb_nodo_t* abb_obtener_padre(abb_nodo_t* nodo, abb_comparar_clave_t cmp, const char *clave) {
	
	if (!nodo) return NULL;
	
	if (nodo->izq && cmp(nodo->izq->clave, clave) == 0) {
		return nodo;
	}
	else if (nodo->der && cmp(nodo->der->clave, clave) == 0) {
		return nodo;
	}
	else if (cmp(nodo->clave, clave) > 0) return abb_obtener_padre(nodo->der, cmp, clave);
	else return abb_obtener_padre(nodo->izq, cmp, clave);
	
}


// #### PRIMITIVAS #### //
bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
	
	if (!arbol) return false;
	
	if (!arbol->raiz) {
		arbol->raiz = abb_nodo_crear(clave, dato);
		arbol->cantidad++;
		return true;
	}
	
	return abb_insertar(arbol, arbol->raiz, clave, dato);
	
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
	
	if (!arbol) return false;
	
	return abb_obtener(arbol, clave) ? true : false;
	
}

abb_nodo_t* _abb_obtener(abb_nodo_t* nodo, abb_comparar_clave_t cmp, const char *clave) {
	
	if (!nodo) return NULL;
	
	if (cmp(nodo->clave, clave) > 0) return _abb_obtener(nodo->der, cmp, clave);
	else if (cmp(nodo->clave, clave) < 0) return _abb_obtener(nodo->izq, cmp, clave);
	else return nodo;
	
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
	
	if (!arbol) return NULL;
	
	abb_nodo_t* obtenido = _abb_obtener(arbol->raiz, arbol->cmp, clave);
	
	if (!obtenido) return NULL;
	
	return obtenido->dato;
}

abb_nodo_t* _abb_borrar(abb_t* arbol, abb_nodo_t *nodo, const char *clave) {
	
	if (!nodo) return NULL;
	
	if (arbol->cmp(nodo->clave, clave) < 0) {
		nodo->izq = _abb_borrar(arbol, nodo->izq, clave);
	}
	else if (arbol->cmp(nodo->clave, clave) > 0) {
		nodo->der = _abb_borrar(arbol, nodo->der, clave);
	}
	else {
		
		if (!nodo->izq) {
			
			abb_nodo_t* temp = nodo->der;
			
			free(nodo->clave);
			free(nodo);
			
			arbol->cantidad--;
			return temp;
			
		}
		else if (!nodo->der) {
			
			abb_nodo_t* temp = nodo->izq;
			
			free(nodo->clave);
			free(nodo);
				
			arbol->cantidad--;
			return temp;
		}
		
		abb_nodo_t* temp = get_reemplazante(nodo->der);
		
		free(nodo->clave);
		nodo->clave = strdup(temp->clave);
		nodo->dato = temp->dato;
		
		nodo->der = _abb_borrar(arbol, nodo->der, temp->clave);
		
	}
	
	return nodo;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
	
	if (!arbol) return NULL;
	
	void* dato_borrado = abb_obtener(arbol, clave);
	
	if (!dato_borrado) return NULL;
	
	arbol->raiz = _abb_borrar(arbol, arbol->raiz, clave);
	
	return dato_borrado;
	
}

size_t abb_cantidad(abb_t *arbol) {
	return arbol->cantidad;
}

void _abb_destruir(abb_nodo_t *nodo, abb_destruir_dato_t destruir_dato) {
	
	if (!nodo) return;
	
	_abb_destruir(nodo->izq, destruir_dato);
	
	_abb_destruir(nodo->der, destruir_dato);
	
	free(nodo->clave);
	if (destruir_dato) destruir_dato(nodo->dato);
	free(nodo);
	
	
}

void abb_destruir(abb_t *arbol) {
	
	if (!arbol) return;
	
	_abb_destruir(arbol->raiz, arbol->destruir_dato);
	
	free(arbol);
	
}

void _abb_in_order(abb_nodo_t *nodo, bool visitar(const char *, void *, void *), void *extra) {
	
	if (!nodo) return;
	
	_abb_in_order(nodo->izq, visitar, extra);
	
	printf("%s\n", nodo->clave);
	if (visitar) visitar(nodo->clave, nodo->dato, extra);
	
	_abb_in_order(nodo->der, visitar, extra);
	
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
	
	if (!arbol) return;
	
	_abb_in_order(arbol->raiz, visitar, extra);
	
}


