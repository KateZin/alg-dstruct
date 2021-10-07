#include "skiplist.h"
#include<math.h>
#pragma warning(disable:4996)

void main() {
	list* myList = createList();
	for (int i = 0; i < 100; i++) {
		listInsert(&myList, rand() % 100);
	}
	
	int count = 0;
	list* tempList = myList;
	while (tempList) {
		count++;
		tempList = tempList->down;
	}
	printf("%d", count);

	deleteList(myList);
}
