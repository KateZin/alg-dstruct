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
	list myList = { &head, &tail};
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

	list myList = { &head, &tail, NULL};
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

// to do: 3 level
// too do: values chnge
// to do: ���������� ���������� ����� �������


TEST(PuttingElementInList, listInsert_AddingElementInEmptyist_ExpectEquel) {    
	node tail = { INFINITY, NULL, NULL };
	node head = { (-1) * INFINITY, &tail, NULL };
	list myList = { &head, &tail };
	list* ptrList = &myList;
	listInsert(&myList, 5);
	EXPECT_EQ(ptrList->head->next->value, 5);
}


// to do: ��������� ��� ��������� ������ ������� (EXPECT_TRUE(list-> down))

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
	EXPECT_TRUE(ptr->down);
	free(elem1);
	free(elem2);
	free(elem3);
	free(elem4);
}



TEST(PuttingElementInList, listInsert_AddingExistingElements1_ExpectEquel) {
	node tail { INFINITY, NULL, NULL };
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




TEST(DeleteElementInList, deleteElement_DeleteExistingElementInTwoLevelList_ExpectEquel) {
	node tail{ INFINITY, NULL, NULL };
	node fourth = { 13, &tail, NULL };
	node* third = (node*)malloc(sizeof(node));
	third->next = &fourth;
	third->down = NULL;
	third->value = 5;
	node second = { 3, third, NULL };
	node first = { -5, &second, NULL };
	node head = { (-1) * INFINITY, &first, NULL };

	node tail2{ INFINITY, NULL, NULL };
	node* third2 = (node*)malloc(sizeof(node));
	third2->next = &tail2;
	third2->down = third;
	third2->value = 5;
	node first2 = { -5, third2, &first };
	node head2 = { (-1) * INFINITY, &first2, NULL };

	list myList = { &head, &tail, NULL };
	list myList2 = { &head, &tail, &myList };
	list* ptr = &myList2;
	deleteElement(ptr, 5);
	EXPECT_EQ((&second)->next->value, (&fourth)->value);
	EXPECT_EQ((&first2)->next->value, (&tail2)->value);

}


//TEST(DeleteElementInList, deleteEl_DeleteElementInTwoLevelList_ExpectEquel) {
//	node tail{ INFINITY, NULL, NULL };
//	node fourth = { 13, &tail, NULL };
//	node third = { 5, &fourth,    NULL };
//	node second = { 3, &third, NULL };
//	node first = { -5, &second, NULL };
//	node fourth2 = { 13, &tail, &fourth };
//	node third2 = { 5, &fourth, &third };
//	node second2 = { 3, &third2, &second };
//	node first2 = { -5, &second2, &first };
//	node head = { (-1) * INFINITY, &first2, NULL };
//	list mylist = { &head, &tail };
//	int size = 4;
//	//int boolean = deleteEl( &head, 5);
//	//EXPECT_EQ(0, boolean);
//	EXPECT_EQ(3, size);
//	node* p1 = &second2;
//	node* p2 = &fourth2;
//	node* p3 = &second;
//	node* p4 = &fourth;
//	EXPECT_EQ(p1->next->value, p2->value);
//	EXPECT_EQ(p3->next->value, p4->value);
//}
//
//
//
