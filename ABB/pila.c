#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 10
#define FACTOR_REDIMENSION_AGRANDAR 2
#define FACTOR_REDIMENSION_ACHICAR 0.5

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

bool pila_redimensionar(pila_t* pila, const double factor) {
	
	size_t capacidad_nueva = (size_t)((double)pila->capacidad * factor);
	
	pila->datos = realloc(pila->datos, capacidad_nueva * sizeof(void*));
	pila->capacidad = capacidad_nueva;
	
	if (pila->datos == NULL) {
		free(pila);
		return false;
	}
	
	return true;
}

pila_t* pila_crear(void) {
	
	pila_t* pila = malloc(sizeof(pila_t));
	
	if (pila == NULL) {
        return NULL;
    }
    
    pila->datos = malloc(CAPACIDAD_INICIAL * sizeof(void*));
    
    if (pila->datos == NULL) {
        free(pila);
        return NULL;
    }
    
    pila->cantidad = 0;
    pila->capacidad = CAPACIDAD_INICIAL;
    
    return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_apilar(pila_t *pila, void* valor) {
	
	if (pila->cantidad == pila->capacidad) {
		if (!pila_redimensionar(pila, FACTOR_REDIMENSION_AGRANDAR)) {
			return false;
		}
	}
	
	pila->datos[pila->cantidad] = valor;
	pila->cantidad = pila->cantidad + 1;
	
	return true;
	
}

bool pila_esta_vacia(const pila_t *pila) {
	return (pila->cantidad == 0);
}	

void* pila_ver_tope(const pila_t *pila) {
	return pila_esta_vacia(pila) ? NULL : pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila) {
	
	if (pila->cantidad == 0) {
		return NULL;
	}
	
	void* elemento_quitado = pila_ver_tope(pila);
	
	pila->cantidad = pila->cantidad - 1;
	
	if (pila->cantidad <= pila->capacidad / 4 && pila->capacidad > CAPACIDAD_INICIAL) {
		pila_redimensionar(pila, FACTOR_REDIMENSION_ACHICAR);		
	}
	
	return elemento_quitado;
	
}




