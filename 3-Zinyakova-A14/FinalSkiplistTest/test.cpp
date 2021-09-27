#include "pch.h"
#include"skiplist.h"
#include"skiplist.c"
#include <math.h>


TEST(SearchElementInList, search_SearchExistingElementInOneLevel_ExpectTrue) {
	
	node tail {(-1)*INFINITY, NULL, NULL};
	node third =  {5, &tail, NULL};
	node second = {3, &third, NULL};
	node head = { (-1)* INFINITY, &second, NULL };
	list mylist = {&head, &tail, 2};
	node* elem = search(&head, 3 );
	EXPECT_TRUE(elem);
}


TEST(SearchElementInList, search_SearchNotExistingElementInOneLevel_ExpectTrue) {

	struct node tail { (-1)* INFINITY, NULL, NULL };
	struct node third = { 5, &tail, NULL };
	struct node second = { 3, &third, NULL };
	struct node head = { (-1) * INFINITY, &second, NULL };
	struct list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 2);
	EXPECT_FALSE(elem);
}


TEST(SearchElementInList, search_SearchExistingElementInTwoFullLevels_ExpectTrue) {

	node tail { (-1)* INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &tail, NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node fourth2 = { 13, &tail, &fourth };
	node third2 = { 5, &tail, &third };
	node second2 = { 3, &third, &second };
	node first2 = { -5, &second, &first };
	node head = { (-1) * INFINITY, &first2, NULL };
	list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 5);
	EXPECT_TRUE(elem);
}



TEST(SearchElementInList, search_SearchExistingElementInTwoNotFullLevels_ExpectTrue) {

	node tail { (-1)* INFINITY, NULL, NULL };
	node fourth = { 23, &tail, NULL };
	node third = { 15, &tail, NULL };
	node second = { 13, &third, NULL };
	node first = { -8, &second, NULL };
	node third2 = { 15, &tail, &third };
	node first2 = { -8, &second, &first };
	node head = { (-1) * INFINITY, &first2, NULL };
	list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 5);
	EXPECT_TRUE(elem);
}

TEST(PuttinfElementInList, AddingElementInEmptyist_Expect) {
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
//
//
//TEST(DeleteElementInList, DeleteExistingElement_expect_true) {
//	list* mylist;
//	int boolean = 0;
//	mylist = createList();
//	int size = 0;
//	int i = 0;
//	for (i = 0; i < 5; i++) {
//		listInsert(&mylist, i, &size);
//	}
//	for (i = 0; i < 5; i++) {
//		deleteEl(mylist->head, i, &size);
//	}
//	EXPECT_EQ(0, size);
//}
//
//
//TEST(DeleteElementInList, DeleteNotExistingElement_expect_true) {
//	list* mylist;
//	int boolean = 0;
//	mylist = createList();
//	int size = 0;
//	int i = 0;
//	for (i = 0; i < 5; i++) {
//		listInsert(&mylist, i, &size);
//	}
//	deleteEl(mylist->head, 10, &size);
//	EXPECT_EQ(5, size);
//}