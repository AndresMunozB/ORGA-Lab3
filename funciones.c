#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"

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

int countElements(char *filename){
	FILE* file;
	int buffer;
	file = fopen(filename,"r");
	int counter=0;
    while (!feof(file)){
    	fscanf(file,"%d\n",&buffer);
    	counter++;
    }
    fclose(file);
    return counter;
}
Library* newLibrary(char *filename){
	FILE* file = fopen(filename,"r");
	int buffer;
	int counter=0;
	int elements = countElements(filename);
	Library* library = (Library*) malloc(sizeof(Library));
	//Guardando los datos en biblioteca de datos
    library->data = (int*) malloc(sizeof(int)*elements);
    library->length = elements;
       
    while (!feof(file)){
    	fscanf(file,"%d\n",&buffer);
    	library->data[counter] = buffer;
    	counter++;
    }
    fclose(file);
    return library;
    
}

void showLibrary(Library* library){
	int i;
	for(i=0;i<library->length;i++){
		printf("index %03d: %d\n",i,library->data[i] );
	}
}


