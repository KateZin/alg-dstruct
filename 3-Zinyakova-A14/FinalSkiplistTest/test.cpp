#include "pch.h"
#include"Header.h"
#include <math.h>
#include <assert.h>
#include <stdlib.h>

class TestMemory : public ::testing::Test {
protected:
	_CrtMemState s1, s2, s3;

	void SetUp() {
		_CrtMemCheckpoint(&s1);
	}

	void TearDown() {
		_CrtMemCheckpoint(&s2);
		if (_CrtMemDifference(&s3, &s1, &s2)) {
			_CrtMemDumpStatistics(&s3);
			FAIL();
		}
	}
};

class ListCreation : public TestMemory {};
class SearchElementByfirstNode : public TestMemory {};
class SearchElementInList : public TestMemory {};
class PuttingElementByFirstNode : public TestMemory {};
class PuttingElementInList : public TestMemory {};
class DeleteElementByNode : public TestMemory {};
class DeleteElementInList : public TestMemory {};
class DeleteList : public TestMemory {};

TEST_F(ListCreation, createList_CreateNewList_ExpectTrue) {
	list* newList = createList();
	EXPECT_TRUE(newList);
	EXPECT_TRUE(newList->head);
	EXPECT_TRUE(newList->tail);
	EXPECT_EQ(newList->head->value, (-1) * INFINITY);
	EXPECT_EQ(newList->tail->value, INFINITY);
	free(newList->head);
	free(newList->tail);
	free(newList);
}

TEST_F(SearchElementByfirstNode, search_SearchExistingElementInOneLevel_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node third = { 4, &tail, nullptr };
	node second = { 2, &third, nullptr };
	node head = { (-1) * INFINITY, &second, nullptr };
	list myList = { &head, &tail };
	node* toFind = search(&head, 2);
	EXPECT_TRUE(toFind);
	EXPECT_EQ(toFind, (&myList)->head->next);
	EXPECT_EQ(toFind->value, 2);
}

TEST_F(SearchElementByfirstNode, search_SearchNotExistingElementInOneLevel_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node third = { 4, &tail, nullptr };
	node second = { 2, &third, nullptr };
	node head = { (-1) * INFINITY, &second, nullptr };
	list myList = { &head, &tail, nullptr };
	node* toFind = search(&head, 1);
	EXPECT_FALSE(toFind);
}

TEST_F(SearchElementInList, searchElement_SearchExistingElementInOneLevel_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node third = { 5, &tail, nullptr };
	node second = { 3, &third, nullptr };
	node head = { (-1) * INFINITY, &second, nullptr };
	list myList = { &head, &tail };
	int boolean = searchElement(&myList, 3);
	EXPECT_EQ(boolean, 1);
}

TEST_F(SearchElementInList, searchElement_SearchNotExistingElementInOneLevel_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node third = { 5, &tail, nullptr };
	node second = { 3, &third, nullptr };
	node head = { (-1) * INFINITY, &second, nullptr };
	list myList = { &head, &tail };
	int boolean = searchElement(&myList, 2);
	EXPECT_EQ(boolean, 0);
}

TEST_F(SearchElementInList, searchElement_SearchExistingElementInTwoFullLevels_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node third = { 5, &fourth, nullptr };
	node second = { 3, &third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };

	node tail2 = { INFINITY, nullptr, nullptr };
	node fourth2 = { 13, &tail2, &fourth };
	node third2 = { 5, &tail, &third };
	node second2 = { 3, &third, &second };
	node first2 = { -5, &second, &first };
	node head2 = { (-1) * INFINITY, &first2, nullptr };

	list myList = { &head, &tail, nullptr };
	list myList2 = { &head, &tail, &myList };
	int boolean = searchElement(&myList2, 3);
	EXPECT_EQ(boolean, 1);
}

TEST_F(SearchElementInList, searchElement_SearchExistingElementInTwoNotFullLevels_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node third = { 5, &fourth, nullptr };
	node second = { 3, &third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };

	node tail2 = { INFINITY, nullptr, nullptr };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, nullptr };

	list myList = { &head, &tail, nullptr };
	list myList2 = { &head, &tail, &myList };
	int boolean = searchElement(&myList, 13);
	EXPECT_EQ(boolean, 1);
}

TEST_F(SearchElementInList, searchElement_SearchExistingElementInThreeNotFullLevels_ExpectTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node third = { 5, &fourth, nullptr };
	node second = { 3, &third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };

	node tail2 = { INFINITY, nullptr, &tail };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };

	node tail3 = { INFINITY, nullptr, &tail2 };
	node third3 = { 5, &tail3, &third2 };
	node head3 = { (-1) * INFINITY, &third3, &head2 };

	list myList = { &head, &tail, nullptr };
	list myList2 = { &head, &tail, &myList };
	list myList3 = { &head, &tail, &myList2 };
	int boolean = searchElement(&myList3, 13);
	EXPECT_TRUE(boolean, 1);
}

TEST_F(PuttingElementByFirstNode, insert_AddingElementInList_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node first = { -1, &tail, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };
	list myList = { &head, &tail };
	node* ptrList = (&myList)->head;
	srand(1);
	node* toInsert = insert(&head, 3);
	EXPECT_TRUE(toInsert);
	EXPECT_EQ(ptrList->next->next->value, 3);
	free(ptrList->next->next);
}


TEST_F(PuttingElementByFirstNode, insert_AddingElementInThreeLevelList_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node third = { 5, &fourth, nullptr };
	node second = { 3, &third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };
	node tail2 = { INFINITY, nullptr, &tail };
	node third2 = { 5, &tail2, &third };
	node first2 = { -5, &third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };
	node tail3 = { INFINITY, nullptr, &tail2 };
	node third3 = { 5, &tail3, &third2 };
	node head3 = { (-1) * INFINITY, &third3, &head2 };

	list myList = { &head, &tail, nullptr };
	list myList2 = { &head2, &tail2, &myList };
	list myList3 = { &head3, &tail3, &myList2 };
	list* ptrList = &myList3;
	listInsert(&ptrList, 1);
	EXPECT_EQ((&myList)->head->next->next->value, 1);
	EXPECT_EQ((&myList2)->head->next->next->value, 1);
	free((&myList)->head->next->next);
	free((&myList2)->head->next->next);

}

TEST_F(PuttingElementInList, listInsert_AddingElementInEmptyList_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node head = { (-1) * INFINITY, &tail, nullptr };
	list myList = { &head, &tail, nullptr };
	list* ptrList = &myList;
	srand(1);
	listInsert(&ptrList, 5);
	EXPECT_TRUE(ptrList->down);
	EXPECT_EQ(ptrList->head->next->value, 5);
	free(ptrList->tail);
	free(ptrList->head->next);
	free(ptrList->head);
	free(ptrList->down->head->next);
	free(ptrList);
}
//
TEST_F(PuttingElementInList, listInsert_AddingElementsCheckOrder_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node head = { (-1) * INFINITY, &tail, nullptr };
	list myList = { &head, &tail };
	list* ptr = &myList;
	srand(1);
	listInsert(&ptr, 5);
	listInsert(&ptr, 9);
	listInsert(&ptr, 2);
	node* elem = &head;
	node* elem1 = elem->next;
	node* elem2 = elem1->next;
	node* elem3 = elem2->next;
	EXPECT_TRUE(ptr->down);
	EXPECT_EQ(elem1->value, 2);
	EXPECT_EQ(elem2->value, 5);
	EXPECT_EQ(elem3->value, 9);
	free(elem1);
	free(elem2);
	free(elem3);
	free(ptr->tail);
	free(ptr->head->next->next);
	free(ptr->head->next);
	free(ptr->head);
	free(ptr);
}

TEST_F(PuttingElementInList, listInsert_AddingExistingElements1_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node head = { (-1) * INFINITY, &tail, nullptr };
	list myList = { &head, &tail };
	srand(1);
	list* ptr = &myList;
	listInsert(&ptr, 7);
	listInsert(&ptr, 3);
	listInsert(&ptr, 7);
	node* elem = &head;
	node* elem1 = elem->next;
	node* elem2 = elem1->next;
	node* elem3 = elem2->next;
	EXPECT_EQ(elem1->value, 3);
	EXPECT_EQ(elem2->value, 7);
	EXPECT_EQ(elem3->value, INFINITY);
	free(ptr->tail);
	free(ptr->head->next->next);
	free(ptr->head->next);
	free(ptr->head);
	free(ptr);
	free(elem1);
	free(elem2);
}

TEST_F(DeleteElementByNode, deleteEl_DeleteExistingElementList_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node* first = (node*)malloc(sizeof(node));
	ASSERT_NE(first, nullptr);
	first->next = &tail;
	first->down = nullptr;
	first->value = 5;
	node head = { (-1) * INFINITY, first, nullptr };
	list myList = { &head, &tail, nullptr };
	node* elem = (&myList)->head;
	deleteEl(elem, 5);
	EXPECT_EQ((&myList)->head->next->value, (&tail)->value);
}

TEST_F(DeleteElementInList, deleteElement_DeleteExistingElementInTwoLevelList_ExpectEquel) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node* third = (node*)malloc(sizeof(node));
	ASSERT_NE(third, nullptr);
	third->next = &fourth;
	third->down = nullptr;
	third->value = 5;
	node second = { 3, third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };

	node tail2 = { INFINITY, nullptr, &tail };
	node* third2 = (node*)malloc(sizeof(node));
	ASSERT_NE(third2, nullptr);
	third2->next = &tail2;
	third2->down = third;
	third2->value = 5;
	node first2 = { -5, third2, &first };
	node head2 = { (-1) * INFINITY, &first2, &head };
	list myList = { &head, &tail, nullptr };
	list myList2 = { &head2, &tail2, &myList };
	list* ptr = &myList2;
	deleteElement(&ptr, 5);
	EXPECT_EQ((&second)->next->value, (&fourth)->value);
	EXPECT_EQ((&first2)->next->value, (&tail2)->value);
}

TEST_F(DeleteElementInList, deleteElement_DeleteElementCheckUpperLevelDelete_ExpectEquelTrue) {
	node tail = { INFINITY, nullptr, nullptr };
	node fourth = { 13, &tail, nullptr };
	node* third = (node*)malloc(sizeof(node));
	ASSERT_NE(third, nullptr);
	third->next = &fourth;
	third->down = nullptr;
	third->value = 5;
	node second = { 3, third, nullptr };
	node first = { -5, &second, nullptr };
	node head = { (-1) * INFINITY, &first, nullptr };
	node* tail2 = (node*)malloc(sizeof(node));
	ASSERT_NE(tail2, nullptr);
	tail2->value = INFINITY;
	tail2->next = nullptr;
	tail2->down = &tail;
	node* third2 = (node*)malloc(sizeof(node));
	ASSERT_NE(third2, nullptr);
	third2->next = tail2;
	third2->down = third;
	third2->value = 5;
	node* head2 = (node*)malloc(sizeof(node));
	ASSERT_NE(head2, nullptr);
	head2->value = -1 * INFINITY;
	head2->next = third2;
	head2->down = &head;
	list myList = { &head, &tail, nullptr };
	list* myList2 = (list*)malloc(sizeof(list));
	ASSERT_NE(myList2, nullptr);
	myList2->head = head2;
	myList2->tail = tail2;
	myList2->down = &myList;
	deleteElement(&myList2, 5);
	EXPECT_EQ((&second)->next->value, (&fourth)->value);
	EXPECT_FALSE(myList2->down);
}

TEST_F(DeleteList, deleteList_DeleteTwoLevelList_ExpectEquel) {
	node* tail = (node*)malloc(sizeof(node));
	ASSERT_NE(tail, nullptr);
	tail->down = nullptr;
	tail->next = nullptr;
	tail->value = INFINITY;
	node* elem1 = (node*)malloc(sizeof(node));
	ASSERT_NE(elem1, nullptr);
	elem1->value = 1;
	elem1->next = tail;
	elem1->down = nullptr;
	node* head = (node*)malloc(sizeof(node));
	ASSERT_NE(head, nullptr);
	head->value = -1 * INFINITY;
	head->down = nullptr;
	head->next = elem1;
	list* myList1 = (list*)malloc(sizeof(list));
	ASSERT_NE(myList1, nullptr);
	myList1->head = head;
	myList1->tail = tail;
	myList1->down = nullptr;
	deleteList(myList1);
}

int main(int* argc, char** argv) {
	int argn = 1;
	testing::InitGoogleTest(&argn, argv);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	RUN_ALL_TESTS();
	return 0;
}