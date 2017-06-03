#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"
#include "funciones.h"

/*
 * Funcion existsFile
*/
int existsFile(char* filename) {
	FILE* file = NULL;
	file = fopen(filename,"r");
	if (file == NULL)
		return 0;
	else {
		fclose(file);
		return 1;
	}
	return 0;
}


void showFile(char *filename){
	FILE* file = fopen(filename,"r");

	int buffer;
	int counter = 0;
	while (!feof(file)){
    	fscanf(file,"%d\n",&buffer);
    	printf("Dato: %d\n",buffer );
    	counter++;
    }
    fclose(file);
    printf("Counter: %d\n", counter);
}








