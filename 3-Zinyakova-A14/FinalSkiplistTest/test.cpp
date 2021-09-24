#include "pch.h"
#include"skiplist.h"
#include"skiplist.c"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(SearchElementInList, ExistingElement_expect_1) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = mylist->size;

	for (int i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}

	for (int i = 0; i < 5; i++) {
		boolean = 0;
		node* elem = search(mylist->head, i);
		if (elem != NULL)
			boolean = 1;
		EXPECT_EQ(1, boolean);
	}
}

TEST(SearchElementInList, NotExistingElement_expect_0) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = mylist->size;

	for (int i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}
	node* elem = search(mylist->head, 7);
	if (elem != NULL)
		boolean = 1;
	EXPECT_EQ(0, boolean);
}


TEST(PuttinfElementInList, AddFiveEements_expect_true) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = mylist->size;
	size = 0;
	for (int i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}
	EXPECT_EQ(5, size);

}

TEST(PuttinfElementInList, AddingExistingElement) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = 0; 
	int i = 0;
	for ( i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}
	listInsert(&mylist, 4, &size);
	EXPECT_EQ(5, size);
}


TEST(DeleteElementInList, DeleteExistingElement_expect_true) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = 0;
	int i = 0;
	for (i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}
	for (i = 0; i < 5; i++) {
		deleteEl(mylist->head, i, &size);
	}
	EXPECT_EQ(0, size);
}


TEST(DeleteElementInList, DeleteNotExistingElement_expect_true) {
	list* mylist;
	int boolean = 0;
	mylist = createList();
	int size = 0;
	int i = 0;
	for (i = 0; i < 5; i++) {
		listInsert(&mylist, i, &size);
	}
	deleteEl(mylist->head, 10, &size);
	EXPECT_EQ(5, size);
}