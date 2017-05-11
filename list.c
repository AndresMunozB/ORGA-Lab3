#include "list.h"
#include <stdlib.h>
#include <stdio.h>


/*
 * Funcion createNodo
*/
Nodo* createNodo(int value){ // crea un nodo con una letra dentro
	Nodo* new= (Nodo*)malloc(sizeof(Nodo));
	if(new!=NULL){
		new->value=value;
		new->next=NULL;
	}
	return new;
}
/*
 * Funcion createList
*/
List* createList(){ //crea una lsita incializada
	List* list=(List*)malloc(sizeof(List));
	list->first=NULL;
	list->length=0;
	return list;
}

/*
 * Funcion add
*/
void add(List* list, int value){ // arega una letra a la lista
	Nodo* new=(Nodo*)createNodo(value);
	Nodo* actual;
	if(list->first==NULL){
		list->first=new;
	}
	else{
		actual = list->first;
		while(actual->next!=NULL){
			actual=actual->next;
		}
		actual->next = new;

	}
	list->length+=1;
}

/*
 * Funcion find
*/
int find(List* list,int value){ // verifica si se encuentra la letra en la lista ->0:no esta , 1:si esta
	Nodo* actual=list->first;
	if(list->first==NULL){
		return 0;
	}
	else{
		while(actual!=NULL){
			if(actual->value == value ){
				return 1;
			}
			else{
				actual=actual->next;
			}
		}
	}
	return 0;
}

/*
 * Funcion findIndex
*/
int findIndex(List* list,int value){
	Nodo* actual = list->first;
	int index=0;
	if (actual==NULL){
		return -1;
	}
	else{
		while(actual!=NULL){
			if(actual->value == value){
				return index;
			}
			else{
				actual=actual->next;
				index++;
			}
		}
	}
	return -1;
}

/*
 * Funcion getValue
*/
int getValue(List* list, int index){
	Nodo* actual = list->first;
	int counter=0;
	if (actual==NULL){
		return -1;
	}
	else{
		while(actual!=NULL){
			if(counter == index){
				return actual->value;
			}
			else{
				actual=actual->next;
				counter++;
			}
		}
	}
	return -1;
}

/*
 * Funcion showList
*/
void showList(List* list){
	Nodo* actual = list->first;
	if(actual == NULL){
		printf("()\n");
	}
	else{
		printf("(");
		while(actual!=NULL){
			printf("%d",actual->value );
			if(actual->next != NULL){
				printf(",");
			}
			actual=actual->next;
		}
		printf(")");

	}
}