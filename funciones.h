#include "estructuras.h"
#ifndef _FUNCIONES_H
#define _FUNCIONES_H
/*
 * Funcion existFile
 * Funcion que verifica si un archivo de texto plano existe
 * @param char* filename, nombre del archivo
 * @return entero 1 en caso de que si exista y 0 en caso contrario
*/
int existsFile(char* filename);
void showFile(char *filename);
Cache* cacheInit(char* potilica, int vias, int palabras, int bloques );
void freeCache(Cache* cache);
void showCache(Cache* cache);
void FIFO(Cache* cache, int dato);
int isInCache(Cache* cache,int dato);
void exCache(Cache* cache, char* nameFile);
void inputWords(Cache* cache ,int group,int block,int dato);
int isPow2(int value);
int isNumber(char* cadena);
int isPolitics(char* cadena);
int validateData(int argc, char** argv);
void statsFile(Cache* cache,char* fileName);
void cacheFile(Cache* cache,char*fileName);
int isComplete(Cache* cache, int group);
int indexBlock(Cache* cache, int group, int dato);
void MRU(Cache* cache, int dato);
void interactionBlockLRU(Cache* cache, int group,int block);
int indexBlockLRU(Cache* cache, int group);
void LRU(Cache* cache, int dato);
void addPrefix(char* str,char**argv);
#endif
