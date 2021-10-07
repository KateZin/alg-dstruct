#include<stdio.h>
#include<Header.h>
#include<math.h>


int main() {
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