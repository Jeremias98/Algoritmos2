#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...
pila_t* pila_crear(void) {
	
	pila_t* pila = malloc(sizeof(pila_t));
	
	if (pila == NULL) {
        return NULL;
    }
    
    pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_INICIAL;

    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    
    return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_apilar(pila_t *pila, void* valor) {
	
	if (valor == NULL) {
		return false;
	}
	
	if (pila->cantidad == pila->capacidad) {
		
		pila->datos = realloc(pila->datos, (pila->capacidad * 2) * sizeof(int));
		pila->capacidad = pila->capacidad * 2;
		
		if (pila->datos == NULL) {
			free(pila);
			return false;
		}
		
	}
	
	pila->datos[pila->cantidad] = valor;
	pila->cantidad = pila->cantidad + 1;
	
	return true;
	
}

bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad == 0 ? true : false;
}	

void* pila_ver_tope(const pila_t *pila) {
	return pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila) {
	
	if (pila->cantidad == 0) {
		return NULL;
	}
	
	void* elemento_quitado = pila_ver_tope(pila);
	
	pila->datos[pila->cantidad - 1] = NULL;
	pila->cantidad = pila->cantidad - 1;
	
	if (pila->cantidad <= pila->capacidad / 4) {
		
		pila->datos = realloc(pila->datos, (pila->capacidad / 2) * sizeof(int));
		pila->capacidad = pila->capacidad / 2;
		
	}
	
	return elemento_quitado;
	
}




