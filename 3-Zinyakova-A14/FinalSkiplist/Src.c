#include "skiplist.h"
#include<math.h>
#pragma warning(disable:4996)


void main() {
	list* myList = createList();
	listInsert(myList, 5);
	listInsert(myList, 10);
	searchElement(myList, 5);
	deleteList(myList, 5);
}
