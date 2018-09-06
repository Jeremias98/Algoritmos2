#include "puerta.h"

#include <stdlib.h>
#include <stdbool.h>

struct puerta {
	bool estado;
};

puerta_t* crear() {
	puerta_t* p = malloc(sizeof(puerta_t));
	if (p == NULL) {
		return NULL;
	}
	cerrar(p);
	return p;
}

void abrir(puerta_t* p) {
	p->estado = true;
}

void cerrar(puerta_t* p) {
	p->estado = false;
}

bool estaAbierta(puerta_t* p) {
	return p->estado;
}

void destruir(puerta_t* p) {
	free(p);
}

