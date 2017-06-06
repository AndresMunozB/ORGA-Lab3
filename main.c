#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "estructuras.h"

int main(int argc, char *argv[]){
	//showFile("input.txt");
	//printf("Argumentos: %d\n",argc );
	//printf("validate: %d\n",validateData(argc, argv) );
	

	
	if (!validateData(argc,argv)){
		printf("Datos de entrada invalidos...\n");
		printf("Fin del programa.\n");
		return 0;
	}
	Cache* cache = (Cache*) cacheInit(argv[1],atoi(argv[2]),atoi(argv[3]),atoi(argv[4]));

	
	char nameFile[50];
	char nameFileOut1[50];
	char nameFileOut2[50];
	
	
	
	printf(" \n\n                   INDICACIONES:\n\n");
	printf("1) Los nombre de los archivos no deben contener la extension.\n");
	printf("        Ejemplos: input, archivo, entrada\n\n");
	printf("2) Los archivo de salida tendran prefijo \"politica-vias-palabras-bloques.html\".\n");	
	printf("        Ejemplos: MRU-2-2-8-nombre.html, FIFO-4-2-8-nombre.html \n\n\n");
	do
	{
		memset(nameFile,0,sizeof(nameFile));
		printf("Introduzca el nombre del archivo de entrada            : ");
		scanf("%s", nameFile);
		strcat(nameFile,".txt");
		if (!existsFile(nameFile))
		{
			printf("El archivo de entrada no existe....\n");
		}
	} while (!existsFile(nameFile));

	memset(nameFileOut1,0,sizeof(nameFileOut1));
	printf("Introduzca el nombre para el archivo de estadisticas   : ");
	scanf("%s", nameFileOut1);

	do
	{
		memset(nameFileOut2,0,sizeof(nameFileOut2));
		printf("Introduzca el nombre para el archivo de datos en cache : ");
		scanf("%s", nameFileOut2);
		if(!strcmp(nameFileOut1,nameFileOut2)){
			printf("Los archivos de salida coinciden en el nombre...\n");
		}
	} while (!strcmp(nameFileOut1,nameFileOut2));
	

	
	
	addPrefix(nameFileOut1,argv);
	addPrefix(nameFileOut2,argv);


	exCache(cache,nameFile);
	statsFile(cache,nameFileOut1);
	cacheFile(cache,nameFileOut2);
	printf("\n\nLos archivos de salida son:\n");
	printf("   -> %s\n", nameFileOut1);
	printf("   -> %s\n", nameFileOut2);
	freeCache(cache);


	printf("Fin del programa.\n\n");

    return 1;
}