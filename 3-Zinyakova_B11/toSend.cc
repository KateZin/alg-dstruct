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


int meminit(void* pMemory, int size) {
	if (size <= memgetminimumsize()) {
		return 0;
	}
	myList.size = size;
	myList.desc = (uint32_t*)pMemory;
	*BlockSizeHead(pMemory) = *BlockSizeEnd(pMemory, size) = size;
	*NextBlock(myList.desc) = NULL; // next 
	*PrevBlock(myList.desc) = NULL; // prev
	*isFree(myList.desc) = TRUE; // IS free
	FIRST = (uint32_t*)pMemory;
	SIZE = (uint32_t)size;
	return OK;
}


//void memdone() {
//	uint32_t* head = myList.desc;
//	int bytes = 0;
//	while (head != NULL) {
//		bytes = bytes + (*head + DESC_SIZE);
//		head = *NextBlock(head);
//	}
//
//	if (bytes != SIZE) {
//		fprintf(stderr, "Memory leak was detected! You lost %i bytes\n", (int)SIZE - bytes);
//	}
//}
//

void* memalloc(int size) {
	if (size < 1 || size > myList.size - memgetblocksize()) {
		return NULL;
	}
	char flag = 1;
	uint32_t* start = myList.desc;
	if (start == NULL) {
		return NULL;
	}
	while (*start < (size + DESC_SIZE)) { // while suitable block not found
		if (*NextBlock(start) == NULL) { // if next == NULL, there's no free blocks left
			return NULL;
		}
		start = *NextBlock(start); // move to next block
	}
	if (*start - size - DESC_SIZE > DESC_SIZE) {
		uint32_t* nextBlock = (uint32_t*)((char*)start + DESC_SIZE + size);
		int restMemSize = *start - size - DESC_SIZE; ///////?????
		*BlockSizeHead(nextBlock) = *BlockSizeEnd(nextBlock, restMemSize) = restMemSize;
		*isFree(nextBlock) = TRUE;
		*NextBlock(nextBlock) = *NextBlock(start);
		*PrevBlock(nextBlock) = *PrevBlock(start);
		*BlockSizeEnd(nextBlock, *BlockSizeHead(nextBlock)) = *BlockSizeHead(nextBlock);
		*isFree(nextBlock) = TRUE;
		if (*PrevBlock(start) != NULL) {
			*NextBlock(*PrevBlock(start)) = nextBlock;
		}
		else {
			myList.desc = nextBlock;
		}
		if (*NextBlock(start) != NULL) {
			*PrevBlock(*NextBlock(start)) = nextBlock;
		}
		*start = size + DESC_SIZE;
		*BlockSizeHead(start) = *BlockSizeEnd(start, *start) = *start;
	}

	else {
		uint32_t* nextBlock = *NextBlock(start);
		uint32_t* prevBlock = *PrevBlock(start);
		if (nextBlock == NULL && prevBlock == NULL) {
			myList.desc = NULL;
		}
		else if (prevBlock == NULL) {
			*PrevBlock(nextBlock) = NULL;
			myList.desc = nextBlock;
		}
		else if (nextBlock == NULL) {
			*NextBlock(prevBlock) = NULL;
		}
		else {
			*NextBlock(prevBlock) = nextBlock;
			*PrevBlock(nextBlock) = prevBlock;
		}
	}
	*isFree(start) = FALSE;
	*NextBlock(start) = NULL;
	*PrevBlock(start) = NULL;
	return (void*)((char*)start + DESC_SIZE - sizeof(uint32_t));
}

void memfree(void* p) {
	if (p == NULL) {
		return;
	}
	uint32_t* start = (uint32_t*)((char*)p - DESC_SIZE + sizeof(uint32_t));
	*isFree(start) = TRUE;
	uint32_t sizePrev = *(uint32_t*)((char*)start - sizeof(uint32_t));;
	uint32_t* right = NULL;
	uint32_t* left = NULL;
	char flagLeft = 0;
	char flagRight = 0;
	if ((uint32_t*)((char*)start + *start) <= (uint32_t*)((char*)FIRST + myList.size)) { ///???????
		right = (uint32_t*)((char*)start + *start);
	}
	if ((uint32_t*)((char*)start - sizeof(uint32_t)) >= (uint32_t*)FIRST) {
		left = (uint32_t*)((char*)start - sizePrev);
	}
	if (left != NULL && *isFree(left) == TRUE) {
		*left = *left + *start;
		*BlockSizeEnd(left, *left) = *left;
		start = left;
		flagLeft = 1;
	}
	if (right != NULL && *isFree(right) == TRUE) {
		flagRight = 1;
		if (flagLeft == 0) {
			*NextBlock(start) = myList.desc;
			*PrevBlock(myList.desc) = start;
			*PrevBlock(start) = NULL;
			myList.desc = start;
		}
		if (right == myList.desc) {
			myList.desc = *NextBlock(right);
			*PrevBlock(myList.desc) = NULL;
		}
		else {
			*NextBlock(*PrevBlock(right)) = *NextBlock(right);
			if (*NextBlock(right) != NULL)
				*PrevBlock(*NextBlock(right)) = *PrevBlock(right);
		}
		*start = *start + *right;
		*BlockSizeEnd(start, *start) = *start;
	}
	if (flagLeft == 0 && flagRight == 0) {
		*NextBlock(start) = myList.desc;
		if (myList.desc != NULL) {
			*PrevBlock(myList.desc) = start;
		}
		*PrevBlock(start) = NULL;
		myList.desc = start;

	}
}



void memdone() {
	uint32_t* start = FIRST;
	while ((char*)start < (char*)FIRST + myList.size) {
		if (*isFree(start) == FALSE) {
			fprintf(stderr, "Memory leak was detected at %p!\n", (char*)start + DESC_SIZE - sizeof(uint32_t));
		}
		start = (uint32_t*)((char*)start + *start);
	}
}



int memgetminimumsize() {
	return DESC_SIZE;
}

int memgetblocksize() {
	return DESC_SIZE;
}