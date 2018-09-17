#include <stdio.h>
#include <string.h>
#include "validate.h"
#include "pass.h"

bool v3(char* input){
  char* pass = get_pass();
  return strcmp(input, pass) == 0;
}

bool v2(char* input) {
  char *pass = get_pass();
  return strcmp(input, pass + 3) == 0;
}

bool v1(char* input) {
  char *pass = get_pass();
  if(strlen(input) != strlen(pass) - 6) return false;
  for(int i = 0; i < strlen(pass) - 6; i++) {
    int v = pass[i] + pass[i+1] + pass[i+2];
    if (v>255) v-=255; 
    if (v<32) v+=32;
    if (v>126) v-=126;
    if(input[i] != (char)(v)) 
      return false;
  }
  return true;
}

bool v5(char* input) {
  char* pass = get_pass();
  int len = strlen(input);
  bool ok = true;
  if(strlen(input) != (strlen(pass)/2)+1) return false;
  for (int i = 1; i<(len/2)+1; i++) {
    char x = input[i];
    input[i] = input[len-i];
    input[len-i] = x;
    ok &= (input[i] == pass[i]);
  }
  return ok;
}

void swap (char* s, int x, int y){
  char t = s[x];
  s[x] = s[y];
  s[y]=t;
}


bool v4(char* input) {
  char* pass = get_pass();
  if(input[7]!=(char)98) return false;
  input[7] = (char)118;
  if(input[13]!=(char)120) return false;
  input[13] = (char)111;   
  swap(input, 15, 0); swap(input, 1, 4);
  swap(input, 3, 12); swap(input, 5, 9);
  swap(input, 6, 7); swap(input, 7, 8);
  swap(input, 8, 9); swap(input, 10, 14);
  swap(input, 8, 9); swap(input, 10, 14);
  swap(input, 8, 14); swap(input, 11, 12);
  swap(input, 12, 13); swap(input, 13, 14);
  swap(input, 9, 12); swap(input, 10, 12); 
  swap(input, 11, 15); swap(input, 15, 14); 
  for (int i = 0; i < strlen(input)+1; i++) {
    if(input[i] != pass[i])
      return false;
  } 
  return true;
}