#include "skiplist.h"
#include<math.h>

void main() {
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list mylist = { &head, &tail, 0 };
	list* ptrList = &mylist;
	int size = 0;
	insert(&head, 5, &size);
	insert(&head, 4, &size);
	node* elem = search(&head, 5);
	deleteEl(&head, 4, &size);
}
