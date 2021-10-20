#include <inttypes.h>
#include <stdio.h>
#include <math.h>
#include "memallocator.h"


#define OK 1
#define FALSE (uint32_t)0
#define TRUE (uint32_t)1
#define DESC_SIZE (2 * sizeof(uint32_t) + 2 * sizeof(uint32_t*) + sizeof(uint32_t)) 



typedef struct list_t {
	uint32_t* desc;
	uint32_t size;
}list_t;

uint32_t* FIRST;
uint32_t SIZE;
list_t myList;


uint32_t* BlockSizeHead(void* desc) {
	return (uint32_t*)desc;
}

uint32_t* BlockSizeEnd(void* desc, int size) {
	return ((uint32_t*)((char*)desc + size - sizeof(uint32_t)));
}

uint32_t* PrevSize(void* desc) {                           ///////////////???????
	return ((uint32_t*)((char*)desc - sizeof(uint32_t)));
}

uint32_t** NextBlock(void* desc) {
	return (uint32_t**)((char*)desc + sizeof(uint32_t));
}


uint32_t** PrevBlock(void* desc) {
	return (uint32_t**)((char*)desc + sizeof(uint32_t) + sizeof(uint32_t*));
}

uint32_t* isFree(void* desc) {
	return (uint32_t*)((char*)desc + sizeof(uint32_t) + 2 * sizeof(uint32_t*));
}

typedef struct testBlock {
	uint32_t size;
	uint32_t* next;
	uint32_t* prev;
	uint32_t isFree;
}testBlock;

int meminit(void* pMemory, int size) {
	myList.size = (uint32_t)size;
	myList.desc = (uint32_t*)pMemory;
	*(myList.desc) = (uint32_t)size;
	*NextBlock(myList.desc) = NULL; // next 
	*PrevBlock(myList.desc) = NULL; // prev
	*isFree(myList.desc) = TRUE; // IS free
	FIRST = (uint32_t*)pMemory;
	SIZE = (uint32_t)size;
	return OK;
}


void memdone() {
	uint32_t* start = FIRST;
	int count = 0;
	while (start != NULL) {
		count += *start;
		start = *NextBlock(start);
	}
	if (count != SIZE) {
		fprintf(stderr, "Memory leak was detected!\n");
	}
}


void* memalloc(int size) {
	uint32_t* start = myList.desc;
	while (*start < (size + DESC_SIZE)) {
		if (*NextBlock(start) == NULL) {   //блока подходящего размера нет
			return NULL;
		}
		start = *NextBlock(start);
	}
	if (*start - size - DESC_SIZE > DESC_SIZE) {
		uint32_t* nextBlock = (uint32_t*)((char*)start + DESC_SIZE + size);
		*BlockSizeHead(nextBlock) = *(BlockSizeHead(start)) - DESC_SIZE - size;
		*NextBlock(nextBlock) = *NextBlock(start);
		*PrevBlock(nextBlock) = *PrevBlock(start);
		*isFree(nextBlock) = TRUE;
		*PrevSize(nextBlock) = size;
		*BlockSizeHead(start) = size;

		if (*PrevBlock(start) != NULL) {
			uint32_t* prev = *PrevBlock(start);
			*NextBlock(prev) = nextBlock;
		}

		if (*NextBlock(nextBlock) != NULL) {
			uint32_t* nextNext = *NextBlock(nextBlock);
			*PrevBlock(nextNext) = nextBlock;
		}
		myList.size = myList.size - size - DESC_SIZE;

	}
	else {                    ////здесь надо переписать
		uint32_t* nextBlock = *NextBlock(start);
		uint32_t* prevBlock = *PrevBlock(start);
		*NextBlock(prevBlock) = nextBlock;
		*PrevBlock(nextBlock) = prevBlock;
		myList.size = myList.size - *start;
	}
	if (start = myList.desc) {
		myList.desc = *NextBlock(start);
	}

	*isFree(start) = FALSE;
	myList.size = myList.size - size - DESC_SIZE;
	return (void*)((char*)start + DESC_SIZE - sizeof(uint32_t));     // участок памяти с отступом на деск
}


void memfree(void* p) {
	uint32_t* start = (uint32_t*)((char*)p - DESC_SIZE + sizeof(uint32_t));
	*isFree(start) = TRUE;
	uint32_t* next;
	uint32_t* prev;
	uint32_t freeSize = *BlockSizeHead(start);
	char flagLeft = 0;  // 0 занят
	char flagRight = 0;
	if (start != FIRST) {
		uint32_t sizePrev = *PrevSize(start);
		prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);
		printf("\nisFree %d\n", *isFree(prev));
		if (*isFree(prev) == TRUE) {
			flagLeft = 1;    //левый свободен
		}
	}
	if ((uint32_t*)((char*)start + freeSize + sizeof(uint32_t)) != (uint32_t*)(FIRST + SIZE)) {    /////???? 
		uint32_t* tmp = (uint32_t*)((char*)start + freeSize + sizeof(uint32_t));
		if (*isFree(tmp) == TRUE) {
			flagRight = 1;
		}
	}

	// левый занят, правый занят - добавляем в список блоков
	if (flagLeft == 0 && flagRight == 0) {
		uint32_t* elem = myList.desc;
		while (*NextBlock(elem) != NULL) {
			elem = *NextBlock(elem);
		}
		*NextBlock(elem) = start;
		*NextBlock(start) = NULL;
		*PrevBlock(start) = elem;
		*isFree(start) = TRUE; ////// перепроверить 
	}
	// левый занят, правый свободен - меняем размер, меняем указатели
	if (flagLeft == 0 && flagRight == 1) {
		uint32_t* next = (uint32_t*)((char*)start + freeSize + sizeof(uint32_t));
		*BlockSizeHead(start) = freeSize + DESC_SIZE + *BlockSizeHead(next);
		*PrevSize(next) = *BlockSizeHead(start);    ///очень много раз перепроверить
		*NextBlock(start) = *NextBlock(next);
		*PrevBlock(start) = *PrevBlock(next);
	}

	// левый свободен, правый занят - меняем размер
	if (flagLeft == 1 && flagRight == 0) {
		uint32_t sizePrev = *PrevSize(start);
		prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);
		int sizeStart = *start;
		//int sizePrev = *prev;
		start = prev;
		*start = sizePrev + sizeStart + DESC_SIZE;
		*BlockSizeEnd(start, *start) = *start;
		//uint32_t sizePrev = *PrevSize(start);
		//uint32_t* prev = (uint32_t*)((char*)start - DESC_SIZE - sizePrev);
		//*BlockSizeHead(prev) = sizePrev + freeSize + DESC_SIZE;
		//*BlockSizeEnd(start, sizePrev + freeSize) = sizePrev + freeSize + DESC_SIZE;
	}

	// левый свободен, правый свободен - считаем полный размер, меняем
	if (flagLeft == 1 && flagRight == 1) {
		uint32_t* next = (uint32_t*)((char*)start + freeSize + sizeof(uint32_t));
		uint32_t sizePrev = *PrevSize(start);
		uint32_t* prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);
		uint32_t sizeRight = freeSize + DESC_SIZE + *BlockSizeHead(next);
		uint32_t allSize = sizePrev + freeSize + sizeRight + 2 * DESC_SIZE;
		*BlockSizeHead(prev) = allSize;
		*BlockSizeEnd(next, allSize) = allSize;
		uint32_t* prevNext = *PrevBlock(next);
		uint32_t* nextNext = *NextBlock(next);
		*NextBlock(prevNext) = nextNext;
		*PrevBlock(nextNext) = prevNext;
	}
	*isFree(start) = TRUE;
	myList.size = myList.size + *start + DESC_SIZE;
}


int memgetminimumsize() {
	return DESC_SIZE;
}

int memgetblocksize() {
	return DESC_SIZE;
}

