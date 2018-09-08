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
    
    pila->datos = malloc(sizeof(void*));
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
	
	if (pila->cantidad == pila->capacidad) {
		
		pila->datos = realloc(pila->datos, (pila->capacidad * 2) * sizeof(int));
		pila->capacidad = pila->capacidad * 2;
		
		if (pila->datos == NULL) {
			free(pila);
			return false;
		}
		
	}
	
	pila->datos[pila->cantidad + 1] = valor;
	pila->cantidad = pila->cantidad + 1;
	
	return true;
	
}
