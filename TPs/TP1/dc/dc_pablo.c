#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pila.h"
#include "strutil.h"

int pot(int n, int k) {
    if (k == 0) return 1;
    int pot_mitad = pot(n, k/2);
    int restante;
    
    if (k%2 == 1) restante = n;
    else restante = 1;

    return pot_mitad * pot_mitad * restante;
}

int _sqrt(int n) {
    int i = 1;
    while(true) {
        if (i * i > n) return i - 1;
        i++;
    }
}

int _log(int n, int b) { 
    int i = 1;
    int ac = 1;
    while (true) {
        if (ac * b > n) return i - 1;
        i ++;
        ac *= b;
    }
}

int interrogacion(int a, int b, int c) {
    if (a == 0) return c;
    else return b;
}

bool str_es_entero(const char* str) {
    char str_num[10] = "0123456789";
    int ini = 0;
    if (str[ini] == '-' && str[ini+1] != '\0') ini = 1;
    for (int i = ini; str[i] != '\0'; i++) {
        for(int j = 0; j < 10; j++) {
            if (str[i] == str_num[j]) break;
            if (j == 9) return false;
        }
        
    }
    return true;
}


char** strv_operadores() {
    char** strv = malloc(sizeof(char*) * 9);
    if (!strv) return NULL;

    strv[0] = strdup("+");
    strv[1] = strdup("-");
    strv[2] = strdup("*");
    strv[3] = strdup("/");
    strv[4] = strdup("sqrt");
    strv[5] = strdup("^");
    strv[6] = strdup("log");
    strv[7] = strdup("?");
    strv[8] = NULL;
    return strv;   
}

int codigo_operacion(const char* str, char** strv_operadores) {
    for (int i = 0; i < 8; i++) {
        if (strcmp(str, strv_operadores[i]) == 0) return i+1;
    }
    return 0;
}


bool error_en_operacion(int* e_1, int* e_2, int* e_3) {    
    if (e_1) free(e_1);
    if (e_2) free(e_2);
    if (e_3) free(e_3);
    return false;
}

bool operacion_2_elementos(pila_t* p_numeros, int cod_operacion, int* result) {
    
    int* e_1 = (int*) pila_desapilar(p_numeros);
    int* e_2 = (int*) pila_desapilar(p_numeros);
    if (!e_1 || !e_2) return error_en_operacion(e_1, e_2, NULL);
    
    if (cod_operacion == 1) *result = *e_1 + *e_2;
    if (cod_operacion == 2) *result = *e_1 - *e_2;
    if (cod_operacion == 3) *result = *e_1 * *e_2;
    if (cod_operacion == 4) {
        if (*e_2 == 0) return error_en_operacion(e_1, e_2, NULL);
        else *result = *e_1 / *e_2;
    }
    if (cod_operacion == 6) {
        if (*e_2 < 0) return error_en_operacion(e_1, e_2, NULL);
        else *result = pot(*e_1, *e_2);   
    }
    if (cod_operacion == 7) {
        if (*e_2 <= 1) return error_en_operacion(e_1, e_2, NULL);
        else *result = _log(*e_1, *e_2);
    }
    free(e_1);
    free(e_2);
    return true;
}

bool operacion_sqrt(pila_t* p_numeros, int* result) {
    
    int* e_1 = (int*) pila_desapilar(p_numeros);
    if (!e_1 || *e_1 < 0) return error_en_operacion(e_1, NULL, NULL);
    
    *result = _sqrt(*e_1);
    free(e_1);
    return true;
}

bool operacion_interr(pila_t* p_numeros, int* result) {
    
    int* e_1 = (int*) pila_desapilar(p_numeros);
    int* e_2 = (int*) pila_desapilar(p_numeros);
    int* e_3 = (int*) pila_desapilar(p_numeros);
    if (!e_1 || !e_2 || !e_3) return error_en_operacion(e_1, e_2, e_3);
        
    *result = interrogacion(*e_1, *e_2, *e_3);
    free(e_1);
    free(e_2);
    free(e_3);
    return true;           
}

void destruir_pila_y_elementos(pila_t* pila) {
    while(!pila_esta_vacia(pila)) free(pila_desapilar(pila));
    pila_destruir(pila);
}

bool error_en_linea(pila_t* p_numeros, char** strv_elementos) {
    fprintf(stdout, "%s\n", "ERROR");
    destruir_pila_y_elementos(p_numeros);
    free_strv(strv_elementos);
    return true;
}

int main(int argc, char* argr[]) {
	
	printf("DC Pablo\n");

    if (argc != 1) {
        fprintf(stdout, "%s\n", "ERROR");
        return 0;
    }
    char* linea = NULL; 
    size_t capacidad = 0;
    char** strv_op = strv_operadores();
    
    while((getline(&linea, &capacidad, stdin)) > 0) { 
        
        linea[strlen(linea) - 1] = '\0';
        pila_t* p_numeros = pila_crear();
        char** strv_elementos = split(linea, ' ');
        size_t strv_idx = 0;
        
        bool error_linea = false;
        while (strv_elementos[strv_idx]) {

            if (strcmp(strv_elementos[strv_idx], "") == 0) {
                strv_idx++;
                continue;
            }
            if (str_es_entero(strv_elementos[strv_idx])) {
                int* num = malloc(sizeof(int));
                *num = atoi(strv_elementos[strv_idx]);
                pila_apilar(p_numeros, num);
            }
            else {
                int* result = malloc(sizeof(int));
                int cod_operacion = codigo_operacion(strv_elementos[strv_idx], strv_op);
                
                if (cod_operacion == 0) error_linea = true;               
                else if (cod_operacion == 5) error_linea = !operacion_sqrt(p_numeros, result);
                else if (cod_operacion == 8) error_linea = !operacion_interr(p_numeros, result);
                else error_linea = !operacion_2_elementos(p_numeros, cod_operacion, result);

                if (error_linea) {
                    free(result);
                    break;
                }
                pila_apilar(p_numeros, result);       
            }
            strv_idx++;
        }
        int* resultado_final = (int*) pila_desapilar(p_numeros);
        if (error_linea || !pila_esta_vacia(p_numeros) || !resultado_final) {
            error_en_linea(p_numeros, strv_elementos);
            if (resultado_final) free(resultado_final);
            continue;
        }
        else {
            fprintf(stdout, "%d\n", *resultado_final);
            free(resultado_final);
            destruir_pila_y_elementos(p_numeros);
            free_strv(strv_elementos);
        }   
    }
    free(linea);
    free_strv(strv_op);      
    return 0;
}






