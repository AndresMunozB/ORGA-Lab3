#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "estructuras.h"
#include "list.h"

int main(){

	Library* library = (Library*) newLibrary("input.txt");
	showLibrary(library);
	List* list = createList();
	add(list,2);
	add(list,3);
	add(list,4);
	add(list,5);
	add(list,6);
	printf("counter: %d\n", countElements("input.txt"));
	printf("%d\n",list->first->value );
	printf("largo: %d\n", list->length);
	printf("find: %d\n",find(list,2) );
	printf("findPosition: %d\n",findIndex(list,4) );
	printf("getValue: %d\n",getValue(list,4) );
	showList(list);

    return 0;
}