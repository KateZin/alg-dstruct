#include "pch.h"
#include"skiplist.h"
#include"skiplist.c"
#include <math.h>

TEST(ListCreation, createList_CreateNewList_ExpectTrue) {
	list* newList = createList();
	EXPECT_TRUE(newList);
	EXPECT_TRUE(newList->head);
	EXPECT_TRUE(newList->tail);
	EXPECT_EQ(newList->size, 0);
}

TEST(SearchElementInList, search_SearchExistingElementInOneLevel_ExpectTrue) {

	node tail{ INFINITY, NULL, NULL };
	node third = { 5, &tail, NULL };
	node second = { 3, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 3);
	EXPECT_TRUE(elem);
}

TEST(SearchElementInList, search_SearchNotExistingElementInOneLevel_ExpectTrue) {

	node tail{ INFINITY, NULL, NULL };
	node third = { 5, &tail, NULL };
	node second = { 3, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 2);
	EXPECT_FALSE(elem);
}

TEST(SearchElementInList, search_SearchExistingElementInTwoFullLevels_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
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

	node tail{ INFINITY, NULL, NULL };
	node fourth = { 23, &tail, NULL };
	node third = { 15, &tail, NULL };
	node second = { 13, &third, NULL };
	node first = { -8, &second, NULL };
	node third2 = { 15, &tail, &third };
	node first2 = { -8, &second, &first };
	node head = { (-1) * INFINITY, &first2, NULL };
	list mylist = { &head, &tail, 2 };
	node* elem = search(&head, 15);
	EXPECT_TRUE(elem);
}

TEST(PuttingElementInList, insert_AddingElementInEmptyist_ExpectEquel) {    // test insert
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list mylist = { &head, &tail, 0 };
	list* ptrList = &mylist;
	int size = 0;
	insert(&head, 5, &size);
	node* elem = ptrList->head->next;
	EXPECT_EQ(elem->value, 5);
	EXPECT_EQ(size, 1);
}

TEST(PuttinfElementInList, insert_AddingElementsCheckOrder_ExpectEquel) {
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list mylist = { &head, &tail, 0 };
	list* ptrList = &mylist;
	int size = 0;
	insert(&head, 5, &size);
	insert(&head, 9, &size);
	insert(&head, 14, &size);
	insert(&head, 2, &size);
	node* elem = &head;
	node* elem1 = elem->next;
	node* elem2 = elem1->next;
	node* elem3 = elem2->next;
	node* elem4 = elem3->next;
	EXPECT_TRUE(elem1->value < elem2->value);
	EXPECT_TRUE(elem2->value < elem3->value);
	EXPECT_TRUE(elem3->value < elem4->value);
	EXPECT_EQ(size, 4);
}

TEST(PuttingElementInList, insert_AddingElementsCheckOrder_ExpectEquel) {
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list mylist = { &head, &tail, 0 };
	list* ptrList = &mylist;
	int size = 0;
	insert(&head, 14, &size);
	insert(&head, 9, &size);
	node* elem = &head;
	node* elem1 = elem->next;
	node* elem2 = elem1->next;
	EXPECT_TRUE(elem1->value < elem2->value);
	EXPECT_EQ(size, 2);
}

TEST(PuttingElementInList, insert_AddingExistingElements1_ExpectEquel) {
	struct node tail { INFINITY, NULL, NULL };
	struct node head = { (-1) * INFINITY, &tail, NULL };
	int size = 0;
	insert(&head, 7, &size);
	insert(&head, 3, &size);
	insert(&head, 7, &size);
	node* elem = &head;
	EXPECT_EQ(elem->next->value, 3);
	elem = elem->next;
	EXPECT_EQ(elem->next->value, 7);
	elem = elem->next;
	EXPECT_EQ(elem->next->value, INFINITY);
}

TEST(PuttingElementInList, insert_AddingExistingElements2_ExpectEquel) {
	struct node tail { INFINITY, NULL, NULL };
	struct node head = { (-1) * INFINITY, &tail, NULL };
	int size = 0;
	insert(&head, 11, &size);
	insert(&head, 2, &size);
	insert(&head, 11, &size);
	node* elem = &head;
	EXPECT_EQ(size, 2);
}

TEST(DeleteElementInList, deleteEl_DeleteExistingElement_ExpectEquel) {
	struct node tail { INFINITY, NULL, NULL };
	node second = { 15, &tail, NULL };
	node first = { 13, &second, NULL };
	struct node head = { (-1) * INFINITY, &first, NULL };
	int size = 2;
	EXPECT_EQ(deleteEl(&head, 13, &size), 0);
	EXPECT_EQ(1, size);
}

TEST(DeleteElementInList, deleteEl_DeleteNotExistingElement_ExpectEquel) {
	struct node tail { INFINITY, NULL, NULL };
	node second = { 3, &tail, NULL };
	node first = { 9, &second, NULL };
	struct node head = { (-1) * INFINITY, &first, NULL };
	int size = 2;
	EXPECT_EQ(deleteEl(&head, 18, &size), -1);
	EXPECT_EQ(2, size);
}

TEST(DeleteElementInList, deleteEl_DeleteElementInEmptyList_ExpectEquel) {
	struct node tail { INFINITY, NULL, NULL };
	struct node head = { (-1) * INFINITY, &tail, NULL };
	int size = 0;
	EXPECT_EQ(deleteEl(&head, 18, &size), -1);
	EXPECT_EQ(0, size);
}

TEST(DeleteElementInList, deleteEl_DeleteElementInTwoLevelList_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &fourth,    NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node fourth2 = { 13, &tail, &fourth };
	node third2 = { 5, &fourth, &third };
	node second2 = { 3, &third2, &second };
	node first2 = { -5, &second2, &first };
	node head = { (-1) * INFINITY, &first2, NULL };
	list mylist = { &head, &tail, 2 };
	int size = 4;
	int boolean = deleteEl(&head, 5, &size);
	EXPECT_EQ(0, boolean);
	EXPECT_EQ(3, size);
	node* p1 = &second2;
	node* p2 = &fourth2;
	node* p3 = &second;
	node* p4 = &fourth;
	EXPECT_EQ(p1->next->value, p2->value);
	EXPECT_EQ(p3->next->value, p4->value);
}



