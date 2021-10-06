#include "pch.h"
#include"skiplist.h"
#include"skiplist.c"
#include <math.h>

TEST(ListCreation, createList_CreateNewList_ExpectTrue) {
	list* newList = createList();
	EXPECT_TRUE(newList);
	EXPECT_TRUE(newList->head);
	EXPECT_TRUE(newList->tail);
	free(newList->head);
	free(newList->tail);
	free(newList);
}

TEST(SearchElementByfirstNode, search_SearchExistingElementInOneLevel_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node third = { 4, &tail, NULL };
	node second = { 2, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list myList = { &head, &tail };
	EXPECT_TRUE(search(&head, 2));
}

TEST(SearchElementByfirstNode, search_SearchNotExistingElementInOneLevel_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node third = { 4, &tail, NULL };
	node second = { 2, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list myList = { &head, &tail };
	EXPECT_FALSE(search(&head, 1));
}

TEST(SearchElementInList, searchElement_SearchExistingElementInOneLevel_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node third = { 5, &tail, NULL };
	node second = { 3, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list myList = { &head, &tail };
	EXPECT_TRUE(searchElement(&myList, 3));
}

TEST(SearchElementInList, searchElement_SearchNotExistingElementInOneLevel_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node third = { 5, &tail, NULL };
	node second = { 3, &third, NULL };
	node head = { (-1) * INFINITY, &second, NULL };
	list myList = { &head, &tail };
	EXPECT_FALSE(searchElement(&myList, 2));
}

TEST(SearchElementInList, searchElement_SearchExistingElementInTwoFullLevels_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &fourth, NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2{ INFINITY, NULL, NULL };
	node fourth2 = { 13, &tail2, &fourth };
	node third2 = { 5, &tail, &third };
	node second2 = { 3, &third, &second };
	node first2 = { -5, &second, &first };
	node head2 = { (-1) * INFINITY, &first2, NULL };

	list myList = { &head, &tail, NULL };
	list myList2 = { &head, &tail, &myList };
	EXPECT_TRUE(searchElement(&myList2, 5));
}

TEST(SearchElementInList, searchElement_SearchExistingElementInTwoNotFullLevels_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &fourth, NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2{ INFINITY, NULL, NULL };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, NULL };

	list myList = { &head, &tail, NULL };
	list myList2 = { &head, &tail, &myList };
	EXPECT_TRUE(searchElement(&myList2, 13));
}

TEST(SearchElementInList, searchElement_SearchExistingElementInThreeNotFullLevels_ExpectTrue) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &fourth, NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2 = { INFINITY, NULL, &tail };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };

	node tail3 = { INFINITY, NULL, &tail2 };
	node third3 = { 5, &tail3, &third2 };
	node head3 = { (-1) * INFINITY, &third3, &head2 };

	list myList = { &head, &tail, NULL };
	list myList2 = { &head, &tail, &myList };
	list myList3 = { &head, &tail, &myList2 };
	EXPECT_TRUE(searchElement(&myList3, 13));
}

TEST(PuttingElementByFirstNode, insert_AddingElementInList_ExpectEquel) {
	node tail = { INFINITY, NULL, NULL };
	node first = { -1, &tail, NULL };
	node head = { (-1) * INFINITY, &first, NULL };
	list myList = { &head, &tail };
	node* ptrList = (&myList)->head;
	insert(&head, 3);
	EXPECT_EQ(ptrList->next->next->value, 3);
}

TEST(PuttingElementByFirstNode, insert_AddingElementInThreeLevelList_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node third = { 5, &fourth, NULL };
	node second = { 3, &third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2 = { INFINITY, NULL, &tail };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };

	node tail3 = { INFINITY, NULL, &tail2 };
	node third3 = { 5, &tail3, &third2 };
	node head3 = { (-1) * INFINITY, &third3, &head2 };

	list myList = { &head, &tail, NULL };
	list myList2 = { &head, &tail, &myList };
	list myList3 = { &head, &tail, &myList2 };
	listInsert(&myList3, 1);
	EXPECT_EQ((&myList)->head->next->next->value, 1);
	EXPECT_EQ((&myList2)->head->next->next->value, 1);
	EXPECT_EQ((&myList3)->head->next->value, 1);
}

TEST(PuttingElementInList, listInsert_AddingElementInEmptyList_ExpectEquel) {
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list myList = { &head, &tail };
	list* ptrList = &myList;
	listInsert(&myList, 5);
	EXPECT_EQ(ptrList->head->next->value, 5);
}

TEST(PuttinfElementInList, listInsert_AddingElementsCheckOrder_ExpectEquel) {
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list myList = { &head, &tail };
	list* ptr = &myList;
	listInsert(ptr, 5);
	listInsert(ptr, 9);
	listInsert(ptr, 14);
	listInsert(ptr, 2);
	node* elem = &head;
	node* elem1 = elem->next;
	node* elem2 = elem1->next;
	node* elem3 = elem2->next;
	node* elem4 = elem3->next;
	EXPECT_EQ(elem1->value, 2);
	EXPECT_EQ(elem2->value, 5);
	EXPECT_EQ(elem3->value, 9);
	EXPECT_EQ(elem4->value, 14);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
}

TEST(PuttingElementInList, listInsert_AddingExistingElements1_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list myList = { &head, &tail };
	list* ptr = &myList;
	listInsert(ptr, 7);
	listInsert(ptr, 3);
	listInsert(ptr, 7);
	node* elem = &head;
	EXPECT_EQ(elem->next->value, 3);
	elem = elem->next;
	EXPECT_EQ(elem->next->value, 7);
	elem = elem->next;
	EXPECT_EQ(elem->next->value, INFINITY);
}

TEST(DeleteElementByNode, deleteEl_DeleteExistingElementList_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node* first = (node*)malloc(sizeof(node));
	if (first == NULL) {
		printf("error  in memory");
		exit;
	}
	first->next = &tail;
	first->down = NULL;
	first->value = 5;
	node head = { (-1) * INFINITY, first, NULL };
	list myList = { &head, &tail, NULL };
	node* elem = (&myList)->head;
	deleteEl(elem, 5);
	EXPECT_EQ((&myList)->head->next->value, (&tail)->value);
}

TEST(DeleteElementInList, deleteElement_DeleteExistingElementInTwoLevelList_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node* third = (node*)malloc(sizeof(node));
	if (third == NULL) {
		printf("error  in memory");
		exit;
	}
	third->next = &fourth;
	third->down = NULL;
	third->value = 5;
	node second = { 3, third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2{ INFINITY, NULL, &tail };
	node* third2 = (node*)malloc(sizeof(node));
	if (third2 == NULL) {
		printf("error in memory");
		exit;
	}
	third2->next = &tail2;
	third2->down = third;
	third2->value = 5;
	node first2 = { -5, third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };
	list myList = { &head, &tail, NULL };
	list myList2 = { &head2, &tail2, &myList };
	list* ptr = &myList2;
	deleteElement(ptr, 5);
	EXPECT_EQ((&second)->next->value, (&fourth)->value);
	EXPECT_EQ((&first2)->next->value, (&tail2)->value);
}

TEST(DeleteElementInList, deleteElement_DeleteElementCheckUpperLevelDelete_ExpectEquelTrue) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node* third = (node*)malloc(sizeof(node));
	if (third == NULL) {
		printf("error  in memory");
		exit;
	}
	third->next = &fourth;
	third->down = NULL;
	third->value = 5;
	node second = { 3, third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };
	node* tail2 = (node*)malloc(sizeof(node));
	if (tail2 == NULL) {
		printf("error  in memory");
		exit;
	}
	tail2->value = INFINITY;
	tail2->next = NULL;
	tail2->down = &tail;
	node* third2 = (node*)malloc(sizeof(node));
	if (third == NULL) {
		printf("error  in memory");
		exit;
	}
	third2->next = tail2;
	third2->down = third;
	third2->value = 5;
	node* head2 = (node*)malloc(sizeof(node));
	if (head2 == NULL) {
		printf("error  in memory");
		exit;
	}
	head2->value = -1 * INFINITY;
	head2->next = third2;
	head2->down = &head;
	list myList = { &head, &tail, NULL };
	list* myList2 = (list*)malloc(sizeof(list));
	if (myList2 == NULL) {
		printf("error  in memory");
		exit;
	}
	myList2->head = head2;
	myList2->tail = tail2;
	myList2->down = &myList;
	deleteElement(myList2, 5);
	EXPECT_EQ((&second)->next->value, (&fourth)->value);
	EXPECT_FALSE(myList2->down);
}

TEST(DeleteList, deleteList_DeleteTwoLevelList_ExpectEquel) {
	node* tail = (node*)malloc(sizeof(node));
	if (tail == NULL) {
		printf("error  in memory");
		exit;
	}
	tail->down = NULL;
	tail->next = NULL;
	tail->value = INFINITY;
	node* elem1 = (node*)malloc(sizeof(node));
	if (elem1 == NULL) {
		printf("error  in memory");
		exit;
	}
	elem1->value = 1;
	elem1->next = tail;
	elem1->down = NULL;
	node* head = (node*)malloc(sizeof(node));
	if (head == NULL) {
		printf("error  in memory");
		exit;
	}
	head->value = -1 * INFINITY;
	head->down = NULL;
	head->next = elem1;
	list* myList1 = (list*)malloc(sizeof(list));
	if (myList1 == NULL) {
		printf("error  in memory");
		exit;
	}
	myList1->head = head;
	myList1->tail = tail;
	myList1->down = NULL;
	deleteList(myList1);
}