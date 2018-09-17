#include <stdio.h>
#include <string.h>
#include "pass.h"
#include "validate.h"

#define MAX 16

int main(void) {
  char password[MAX + 1];
  fgets(password, MAX + 1, stdin);
  if(password[strlen(password) - 1] == '\n')
    password[strlen(password) - 1] = '\0';
  if(v1(password) || v2(password) || v3(password) || v4(password) || v5(password))
    printf("Ganaste! Visitá https://algoritmos-rw.github.io/algo2/gdb-challenge\n");
  else
    printf("Perdiste!\n");
  return 0;
}