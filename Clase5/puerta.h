#ifndef PUERTA_H
#define PUERTA_H

#include <stdbool.h>

typedef struct puerta puerta_t;

puerta_t* crear();

void destruir(puerta_t* p);

void abrir(puerta_t* p);

void cerrar(puerta_t* p);

bool estaAbierta(puerta_t* p);

#endif
