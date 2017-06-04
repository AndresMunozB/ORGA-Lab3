#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "estructuras.h"

int main(int argc, char *argv[]){
	//showFile("input.txt");
	//printf("Argumentos: %d\n",argc );
	printf("validate: %d\n",validateData(argc, argv) );
	

	if (!validateData(argc,argv)){
		return 0;
	}
	char nameFile[50];
	memset(nameFile,0,sizeof(nameFile));
	printf("Introduzca el nombre del archivo: ");
	scanf("%s", nameFile);

	Cache* cache = (Cache*) cacheInit(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));
	
	if (existsFile(nameFile)){
		exCache(cache,nameFile);
		statsFile(cache,"salida.html");
		cacheFile(cache,"salida2.html");
	}
	else{
		printf("El archivo no existe\n");
	}

    return 1;
}