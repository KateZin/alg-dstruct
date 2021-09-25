#include "skiplist.h"

#include<math.h>

void main() {
	list* mylist = createList();
	int size = mylist->size;
	size = 0;
	for (int i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
		printf("%d\n", size);
	}
	listDeleteEl(&mylist, 3, &size);
	//deleteEl(mylist->head, 4, &size);
	if (3648334734384734< mylist->tail->value)
	printf("%f\n", mylist->tail->value);
}
