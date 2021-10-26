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

uint32_t* PrevSize(void* desc) {                           
	return ((uint32_t*)((char*)desc - sizeof(uint32_t)));
}

uint32_t** NextBlock(void* desc) {
	return (uint32_t**)((char*)desc + sizeof(uint32_t));
}

uint32_t** PrevBlock(void* desc) {
	return (uint32_t**)((char*)desc + sizeof(uint32_t) + sizeof(uint32_t*));
}

uint32_t* IsFree(void* desc) {
	return (uint32_t*)((char*)desc + sizeof(uint32_t) + 2 * sizeof(uint32_t*));
}

int meminit(void* pMemory, int size) {
	if (size <= memgetminimumsize()) {
		return 0;
	}
	myList.size = size;
	myList.desc = (uint32_t*)pMemory;
	*BlockSizeHead(pMemory) = *BlockSizeEnd(pMemory, size) = size;
	*NextBlock(myList.desc) = NULL; 
	*PrevBlock(myList.desc) = NULL; 
	*IsFree(myList.desc) = TRUE;
	FIRST = (uint32_t*)pMemory;
	SIZE = (uint32_t)size;
	return OK;
}

void* memalloc(int size) {
	if (size < 1 || size > myList.size - memgetblocksize()) {
		return NULL;
	}
	uint32_t* start = myList.desc;
	if (start == NULL) {
		return NULL;
	}
	while (*BlockSizeHead(start) < (size + DESC_SIZE)) {
		if (*NextBlock(start) == NULL) { 
			return NULL;
		}
		start = *NextBlock(start); 
	}
	if (*BlockSizeHead(start) - size - DESC_SIZE > DESC_SIZE) {
		uint32_t* nextBlock = (uint32_t*)((char*)start + DESC_SIZE + size);
		int restMemSize = *BlockSizeHead(start) - size - DESC_SIZE;
		*BlockSizeHead(nextBlock) = *BlockSizeEnd(nextBlock, restMemSize) = restMemSize;
		*IsFree(nextBlock) = TRUE;
		*NextBlock(nextBlock) = *NextBlock(start);
		*PrevBlock(nextBlock) = *PrevBlock(start);
		*BlockSizeEnd(nextBlock, *BlockSizeHead(nextBlock)) = *BlockSizeHead(nextBlock);
		*IsFree(nextBlock) = TRUE;
		if (*PrevBlock(start) != NULL) {
			*NextBlock(*PrevBlock(start)) = nextBlock;
		}
		else {
			myList.desc = nextBlock;
		}
		if (*NextBlock(start) != NULL) {
			*PrevBlock(*NextBlock(start)) = nextBlock;
		}
		*BlockSizeHead(start) = size + DESC_SIZE;
		*BlockSizeHead(start) = *BlockSizeEnd(start, *BlockSizeHead(start)) = *BlockSizeHead(start);
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
	*IsFree(start) = FALSE;
	*NextBlock(start) = NULL;
	*PrevBlock(start) = NULL;
	return (void*)((char*)start + DESC_SIZE - sizeof(uint32_t));
}

void memfree(void* p) {
	if (p == NULL) {
		return;
	}
	uint32_t* start = (uint32_t*)((char*)p - DESC_SIZE + sizeof(uint32_t));
	*IsFree(start) = TRUE;
	uint32_t sizePrev = *(uint32_t*)((char*)start - sizeof(uint32_t));
	uint32_t* right = NULL;
	uint32_t* left = NULL;
	char flagLeft = 0;
	char flagRight = 0;
	if ((uint32_t*)((char*)start + *BlockSizeHead(start)) <= (uint32_t*)((char*)FIRST + myList.size)) {
		right = (uint32_t*)((char*)start + *BlockSizeHead(start));
	}
	if ((uint32_t*)((char*)start - sizeof(uint32_t)) >= FIRST) {
		left = (uint32_t*)((char*)start - sizePrev);
	}
	if (left != NULL && *IsFree(left) == TRUE) {
		*BlockSizeHead(left) = *BlockSizeHead(left) + *BlockSizeHead(start);
		*BlockSizeEnd(left, *BlockSizeHead(left)) = *BlockSizeHead(left);
		start = left;
		flagLeft = 1;
	}
	if (right != NULL && *IsFree(right) == TRUE) {
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
		*BlockSizeHead(start) = *BlockSizeHead(start) + *BlockSizeHead(right);
		*BlockSizeEnd(start, *BlockSizeHead(start)) = *BlockSizeHead(start);
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
		if (*IsFree(start) == FALSE) {
			fprintf(stderr, "Memory leak was detected at %p!\n", (char*)start + DESC_SIZE - sizeof(uint32_t));
		}
		start = (uint32_t*)((char*)start + *BlockSizeHead(start));
	}
}

int memgetminimumsize() {
	return DESC_SIZE;
}

int memgetblocksize() {
	return DESC_SIZE;
}