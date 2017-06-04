#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estructuras.h"
#include "funciones.h"

/*
 * Funcion existsFile
*/
int existsFile(char* filename) 
{
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

void showFile(char *filename)
{
	FILE* file = fopen(filename,"r");

	int buffer;
	while (!feof(file)){
    	fscanf(file,"%d\n",&buffer);
    	printf("Dato: %d\n",buffer );
    }
    fclose(file);
}

int isPow2(int value)
{
	if (value  == 1){
		return 1;
	}
	else{
		int i=1;
		while (1){
			i *= 2;
			if (i == value){return 1;}
        	if (i > value){return 0;}
		}
	}
	return 0;
}

int isNumber(char* cadena)
{
	int i;
	for (i=0;i<strlen(cadena);i++){
		if (!(cadena[i]>= 48 && cadena[i]<=57)){
			return 0;
		}
	}
	return 1;
}

int isPolitics(char* cadena)
{
	if (!strcmp(cadena,"MRU")){
		return 1;
	}
	else if (!strcmp(cadena,"mru")){
		return 1;
	}
	else if (!strcmp(cadena,"LRU")){
		return 1;
	}
	else if (!strcmp(cadena,"lru")){
		return 1;
	}
	else if (!strcmp(cadena,"FIFO")){
		return 1;
	}
	else if (!strcmp(cadena,"fifo")){
		return 1;
	}
	return 0;
}

int validateData(int argc, char** argv)
{
	if (argc <5){
		return 0;
	}
	//verificar que lo entregado es correcto
	if (!isNumber(argv[2]), !isNumber(argv[3]) ,!isNumber(argv[4])){
		return 0;
	}
	if (!isPow2(atoi(argv[2])) || !isPow2(atoi(argv[3])) || !isPow2(atoi(argv[4]))){
		return 0;
	}
	if (!isPolitics(argv[1])){
		return 0;
	}

	return 1;
}

Cache* cacheInit(char* politica, int vias, int palabras, int bloques )
{
	Cache* cache = (Cache*)malloc(sizeof(Cache));
	cache->numberGroups = bloques/vias;
	cache->wordsPerBlock = palabras;
	cache->blocksPerGroup = vias;
	cache->numberBlocks = bloques;
	cache->hit = 0;
	cache->miss = 0;
	memset(cache->politics,0,10);
	strcpy(cache->politics,politica);
	cache->groups = (Group*) malloc(sizeof(Group)*cache->numberGroups);
	int i,j,k;
	for (i=0;i<cache->numberGroups;i++){
		cache->groups[i].blocks = (Block*) malloc(sizeof(Block)*cache->blocksPerGroup);
		cache->groups[i].fifo = 0;
		for (j=0;j<cache->blocksPerGroup;j++){
			cache->groups[i].blocks[j].words = (int*) malloc(sizeof(int) * cache->wordsPerBlock);
			for (k=0;k<cache->wordsPerBlock;k++){
				cache->groups[i].blocks[j].words[k] = 0;
			}
		}
	}
	return cache;
}
void freeCache(Cache* cache)
{
	int i,j;
	for (i=0;i<cache->numberGroups;i++){
		for (j=0;j<cache->blocksPerGroup;j++){
			free(cache->groups[i].blocks[j].words);
		}
	}
	for (i=0;i<cache->numberGroups;i++){
		free(cache->groups[i].blocks);
	}
	free (cache->groups);
	free(cache);
}

void showCache(Cache* cache)
{
	int i,j,k;
	for ( i = 0; i < cache->numberGroups; ++i)
	{	
		printf("group[%d]:\n",i );
		for ( j = 0; j < cache->blocksPerGroup; ++j)
		{	
			printf("  block[%d]:\n",j );
			for ( k = 0; k < cache->wordsPerBlock; ++k)
			{
				printf("    word[%d]: %d\n",k,cache->groups[i].blocks[j].words[k] );
			}
		}
	}
}

void inputWords(Cache* cache ,int group,int block,int  dato)
{
	for (int i = 0; i < cache->wordsPerBlock; ++i)
	{
		cache->groups[group].blocks[block].words[i] = dato - (dato%cache->wordsPerBlock) + i ; 
	}
}

void FIFO(Cache* cache, int dato)
{
	
	int group = dato / cache->wordsPerBlock % cache->numberGroups;
	int block = cache->groups[group].fifo % cache->blocksPerGroup;
	int i;
	if (isInCache(cache,dato)){
		cache->hit++;
	}
	else{
		cache->miss++;
		inputWords(cache,group,block, dato);
		cache->groups[group].fifo++;
	}
}

int isInCache(Cache* cache,int dato)
{
	int group = (dato / cache->wordsPerBlock) % cache->numberGroups;
	int i,j;
	for (int i = 0; i < cache->blocksPerGroup; ++i)
	{
		for (int j = 0; j < cache->wordsPerBlock; ++j)
		{
			if (cache->groups[group].blocks[i].words[j] == dato){
				return 1;
			}
		}
	}
	return 0;
}


void exCache(Cache* cache, char* nameFile)
{
	FILE* file = fopen(nameFile,"r");

	int buffer;
	while (!feof(file)){
    	fscanf(file,"%d\n",&buffer);
    	if(!strcmp(cache->politics, "FIFO") || !strcmp(cache->politics, "fifo")){
    		FIFO(cache,buffer);
    	}
    	
    }
    fclose(file);
    showCache(cache);
	//cache->groups[0].blocks[0].words[0] = 1;
	//printf("word: %d\n", cache->groups[0].blocks[0].words[0]);
	printf("\n\nEstadisticas:\n");
	printf("hit:  %d\n",cache->hit );
	printf("miss: %d\n", cache->miss);
}

void statsFile(Cache* cache,char* fileName)
{
	FILE* file = fopen(fileName,"w");
	fprintf(file, "<!DOCTYPE html>\n" );
	fprintf(file, "<html lang=\"es\">\n" );
	fprintf(file, "<head>\n" );
	fprintf(file, "		<meta charset=\"UTF-8\">\n" );
	fprintf(file, "		<title>Estadisticas</title>\n" );
	fprintf(file, "		<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\" integrity=\"sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ\" crossorigin=\"anonymous\">\n" );
	fprintf(file, "		<style type=\"text/css\">\n" );
	fprintf(file, "			td { height: 40px; vertical-align: middle; text-align: center; font-family: Verdana; }\n" );
	fprintf(file, "		</style>\n" );
	fprintf(file, "</head>\n" );
	fprintf(file, "<body>\n" );
	fprintf(file, "		<div class=\"container\">\n" );
	fprintf(file, "			<div class=\"row \">\n" );
	fprintf(file, "				<div class=\"col-md-4\"></div>\n" );
	fprintf(file, "				<div class=\"col-md-4 \"><h1>Estadísticas</h1></div>\n" );
	fprintf(file, "			</div>\n" );
	fprintf(file, "			<br><hr><br>\n" );
	fprintf(file, "			<div class=\"row\">\n" );
	fprintf(file, "				<div class=\"col-md-4\"></div>\n" );
	fprintf(file, "				<div class=\"col-md-4\">\n" );
	fprintf(file, "					<table class=\"table table-bordered\">\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Tamaño</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d Bits</td>\n", 32*cache->wordsPerBlock*cache->blocksPerGroup*cache->numberGroups );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Política</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%s</td>\n",cache->politics );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Vías</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d</td>\n ", cache->blocksPerGroup );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Bloques</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d</td>\n",cache->numberBlocks );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Palabras por bloque</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d</td>\n",cache->wordsPerBlock );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Hit</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d</td>\n",cache->hit );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						<tr>\n" );
	fprintf(file, "							<td class=\"td bg-inverse text-white\">Miss</td>\n" );
	fprintf(file, "							<td class=\"td bg-primary text-white\">%d</td>\n",cache->miss );
	fprintf(file, "						</tr>\n" );
	fprintf(file, "					</table>\n" );
	fprintf(file, "				</div>\n" );
	fprintf(file, "			</div>\n" );
	fprintf(file, "		</div>\n" );
	fprintf(file, "	</body>\n" );
	fprintf(file, "</html>\n" );
}

void cacheFile(Cache* cache,char*fileName)
{

	FILE* file = fopen(fileName,"w");
	int i,j,k;
	fprintf(file, "<!DOCTYPE html>\n" );
	fprintf(file, "<html lang=\"es\">\n" );
	fprintf(file, "<head>\n" );
	fprintf(file, "		<meta charset=\"UTF-8\">\n" );
	fprintf(file, "		<title>Datos caché</title>\n" );
	fprintf(file, "		<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\" integrity=\"sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ\" crossorigin=\"anonymous\">\n" );
	fprintf(file, "		<style type=\"text/css\">\n" );
	fprintf(file, "			td { height: 40px; vertical-align: middle; text-align: center; font-family: Verdana; }\n" );
	fprintf(file, "		</style>\n" );
	fprintf(file, "</head>\n" );
	fprintf(file, "<body>\n" );
	fprintf(file, "		<div class=\"container\">\n" );
	fprintf(file, "			<div class=\"row \">\n" );
	fprintf(file, "				<div class=\"col-md-4\"></div>\n" );
	fprintf(file, "				<div class=\"col-md-4 \"><h1>Datos caché</h1></div>\n" );
	fprintf(file, "			</div>\n" );
	fprintf(file, "			<br><hr><br>\n" );
	
	fprintf(file, "		</div>\n" );
	fprintf(file, "			<div class=\"row\">\n" );
	fprintf(file, "				<div class=\"col-md-1\"></div>\n" );
	fprintf(file, "				<div class=\"col-md-10\">\n" );
	fprintf(file, "					<table class=\"table table-bordered \">\n" );

	fprintf(file, "						<tr>\n" );

	for (i=0;i<cache->numberGroups;i++)
	{
	fprintf(file, "							<td class=\"td bg-inverse text-white\" colspan=\"%d\">G%d</td>\n",(cache->wordsPerBlock)*(cache->blocksPerGroup),i );
	}
	fprintf(file, "						</tr>\n" );

	fprintf(file, "						<tr>\n" );

	for (i=0;i<cache->numberGroups;i++)
	{
		for (j=0;j<cache->blocksPerGroup;j++)
		{
	fprintf(file, "							<td class=\"bg-primary text-white\" colspan=\"%d\">B%d</td>\n",cache->wordsPerBlock,j );
		}
	}	
	fprintf(file, "						</tr>\n" );

	fprintf(file, "						<tr>\n" );

	for (i=0;i<cache->numberGroups;i++)
	{
		for (j=0;j<cache->blocksPerGroup;j++)
		{
			for (k=0;k<cache->wordsPerBlock;k++)
			{
	fprintf(file, "							<td class=\"bg-danger text-white\">W%d</td>\n",k );
			}
		}
		
	}	
	fprintf(file, "						</tr>\n" );
	fprintf(file, "						</tr>\n" );

	fprintf(file, "						</tr>\n" );

	fprintf(file, "						<tr>\n" );

	for (i=0;i<cache->numberGroups;i++)
	{
		for (j=0;j<cache->blocksPerGroup;j++)
		{
			for (k=0;k<cache->wordsPerBlock;k++)
			{
	fprintf(file, "							<td class=\"bg-warning text-white\">%d</td>\n",cache->groups[i].blocks[j].words[k] );
			}
		}
		
	}	
	fprintf(file, "						</tr>\n" );
	fprintf(file, "					</table>\n" );
	fprintf(file, "				</div>\n" );
	fprintf(file, "			</div>\n" );
	fprintf(file, "	</body>\n" );
	fprintf(file, "	</html>\n" );


}





