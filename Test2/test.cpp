#include "pch.h"
#include "skiplist.h"
#include "skiplist.c"

//создание в мэйн newnode вызывает ошибку чтения памяти
TEST(TestCaseName2, TestName2) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(SearchElementInList, existingElement_expect_1) {
	list* mylist;
	int size = 0;
	int maxsize = 5;
	int boolean = 0;
	mylist = createlist();
	for (int i = 0; i < 5; i++) {
		listinsert(mylist, i, &size);
	}
	for (int i = 0; i < 5; i++) {
		boolean = 0;
		node* elem = search(mylist->head, i);
		if (elem != NULL)
			boolean = 1;
		EXPECT_EQ(1, boolean);
	}
}
//
//TEST(SearchElementInList, NotExistingElement_expect_0) {
//	list* mylist;
//	int size = 0;
//	int boolean = 0;
//	mylist = createlist();
//	for (int i = 0; i < 5; i++) {
//		listinsert(mylist, i, &size);
//	}
//	node* elem = search(mylist->head, rand()%100+10);
//	if (elem != NULL)
//		boolean = 1;
//	
//	EXPECT_EQ(0, boolean);
//}

TEST(AddElemToList, RightOrder) {
	list* mylist;
	int size = 0;
	int boolean = 0;
	node* elem;
	mylist = createlist();
	for (int i = 0; i < 5; i++) {
		insert(mylist->head, rand()%100);
	}
	elem = mylist -> head;
	while (elem->next != NULL) {
		EXPECT_TRUE(elem->value <= elem->next->value);
		elem = elem->next;
	}
}


