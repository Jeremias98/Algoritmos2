#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int edad;
	char* nombre;
	int dni;
} Persona;

Persona* crearPersona(int edad, char* nombre, int dni)  {
	
	Persona* persona = malloc(sizeof(Persona));
	
	persona->edad = edad;//Equivalente: (*persona).edad = edad;
	persona->nombre = nombre;
	(*persona).dni = dni;
	
	return persona;
}


int factorial(int n) {
	if(n == 0) {
		return 1;
	}
	return n * factorial(n-1);
}

void cadenas() {
	char s1[4] = "Hola";
	char s2[5] = "Mundo";
	
	char cadena_estatica[5] = "PEPE";
	char* cadena_dinamica = malloc( sizeof(char) * (strlen(cadena_estatica) + 1) ); // El +1 representa el \0
	
	printf("%s\n", s1);
	printf("%s\n", cadena_dinamica);
}

void structs() {
	
	Persona pepe = {20, "Pepe", 12312312};
	
	printf("%d\n", pepe.edad);
	printf("%s\n", pepe.nombre);
	printf("%d\n", pepe.dni);
	
}

int main(void) {
	//printf("%d\n", factorial(5));
	//cadenas();
	
	structs();
	
	return 0;
}
