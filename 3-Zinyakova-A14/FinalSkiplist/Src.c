#include "skiplist.h"

void main() {
	list* mylist = createList();
	int size = mylist->size;
	size = 0;
	for (int i = 0; i < 5; i++) {
		listinsert(&mylist, i, &size);
		printf("%d\n", size);
	}
	deleteEl(mylist->head, 3, &size);
	printf("%d\n", size);
}
