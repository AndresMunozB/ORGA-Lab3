#ifndef _LIST_H
#define _LIST_H

typedef	struct Nodo
{
	char value;
	struct Nodo* next;

}Nodo;

typedef struct List
{
	int length;
	Nodo* first;	
}List;


/*
 * Funcion createNodo
 * crea un nodo con el caracter entregado
 * @param int value, valor a guardar en el nodo a crear
 * @return nodo con la informacion guardada

*/
Nodo* createNodo(int value);

/*
 * Funcion createList
 * crea un tipo de dato List inicializado listo para ocupar
 * @return List*, Puntero a una lista
*/
List* createList();

/*
 * Funcion add
 * agrega un elemento a una lista al final de esta
 * @param List* list, lista a la cual se le agregara el elemento
 * @param int value, valor que se agrega a la lista
*/
void add(List* list, int value);

/*
 * Funcion find
 * funcion que busca un valor dentro de un lista 
 * @param List* list, corresponde a la lista en la cual se buscara la letra.
 * @param int valur, corresponde al valor a buscar dentro de la lista.
 * @return int, esta funcion retorna 0 en caso de no encontrar el valor y 1 en caso de si encontralo.
*/
int find(List* list,int value);

/*
 * Funcion findIndex
 * funcion que busca dentro de un a lista la posicion de un letra.
 * @param List* list, corresponde a la lista en la cual se buscara la posicion de la letra
 * @param int value, corresponde al valor que se esta buscando para obtener la posicion.
 * @return int, corresponde a la posicion del valor buscado, entrega -1 en caso de no encotrala.
*/
int findIndex(List* list,int value);

/*
 * Funcion getValue
 * funcion que obitiene el valor segun el indice entregado
 * @param List* list, corresponde a la lista en la cual se obtendra el valor
 * @param int position, corresponde a la posicion de la letra en la lista
 * @retrun value, corresponde al valor de la lista en la posicion entregada como parametro.
*/
int getValue(List* list, int index);

/*
 * Funcion showList
 * funcion que muestra por pantalla una lista desde el inicio a fin.
 * @param List* list, corresponde a la lista que se desea mostrar.
*/
void showList(List* list);


#endif