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
int countElements(char *filename);

Library* newLibrary(char *filename);
void showLibrary(Library* library);




#endif
