#include <stdio.h>
#include <stdlib.h>
#include "dc.h"

int main(int argc, char *argv[]) {
	
	if (argc != 1) {
        fprintf(stdout, "%s\n", "ERROR\n");
        return 0;
    }
	
    return dc_procesar_entrada();
    
}
