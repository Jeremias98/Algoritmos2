#include "cola.h"
#include <stdio.h>

typedef struct nodo {
	void* dato;
	struct nodo* prox;
} nodo_t;

struct cola {
	nodo_t* prim;
	nodo_t* ult;
};

// Funcion para verificar si la cola tiene solamente un elemento
bool tiene_un_solo_elemento(cola_t *cola) {
	return (cola->prim == cola->ult);
}

cola_t* cola_crear(void) {
	
	cola_t* cola = malloc(sizeof(cola_t));
	
	if (cola == NULL) {
        return NULL;
    }
    
    cola->prim = NULL;
    cola->ult = NULL;
    
    return cola;
    
}

bool cola_encolar(cola_t *cola, void* valor) {
	
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if (nodo == NULL) {
		return false;
	}
	
	nodo->dato = valor;
	nodo->prox = NULL;
		
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo;
		cola->prim->prox = nodo;
	}
	else {
		cola->ult->prox = nodo;
	}
	
	cola->ult = nodo;
	
	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	return cola_esta_vacia(cola) ? NULL : cola->prim->dato;
}

bool cola_esta_vacia(const cola_t *cola) {
	return (cola->prim == NULL);
}

void* cola_desencolar(cola_t *cola) {
	
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	
	nodo_t* nodo_quitado = cola->prim;
	nodo_t* elemento_quitado = cola->prim->dato;
	
	if (tiene_un_solo_elemento(cola)) {
		cola->prim = NULL;
		cola->ult = NULL;
	}
	else {
		cola->prim = nodo_quitado->prox;
	}
	
	free(nodo_quitado);
	
	return elemento_quitado;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {

	nodo_t* nodo = cola->prim;
	while (nodo != NULL) {
		nodo_t* proximo = nodo->prox;
		
		if (destruir_dato != NULL) {
			destruir_dato(nodo->dato);
		}
			
		free(nodo);
		
		// En caso de tener un solo elemento, hacer free() a la posicion de 
		// memoria de cola->prim ocasiona problemas, ya que cola->prim es igual a 
		// cola->prim->prox y a cola->ult
		nodo = tiene_un_solo_elemento(cola) ? NULL : proximo;
	}
	
	free(cola);
	
}






