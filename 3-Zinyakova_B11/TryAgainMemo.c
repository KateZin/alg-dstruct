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
	return ((uint32_t*)((char*)desc + DESC_SIZE + size - sizeof(uint32_t)));
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
	if (size <= memgetminimumsize()) {
		return 0;
	}
	myList.size = size - DESC_SIZE;
	myList.desc = (uint32_t*)pMemory;
	//в начало и в конец блока пишем разер нашего блока
	*(myList.desc) = *((uint32_t*)((char*)pMemory + size - sizeof(uint32_t))) = size - DESC_SIZE;
	*NextBlock(myList.desc) = NULL; // next 
	*PrevBlock(myList.desc) = NULL; // prev
	*isFree(myList.desc) = TRUE; // IS free
	FIRST = (uint32_t*)pMemory;
	SIZE = (uint32_t)size;
	return OK;
}


void memdone() {
	uint32_t* head = myList.desc;
	int bytes = 0;
	while (head != NULL) {
		bytes = bytes + (*head + DESC_SIZE);
		head = *NextBlock(head);
	}

	if (bytes != SIZE) {
		fprintf(stderr, "Memory leak was detected! You lost %i bytes\n", (int)SIZE - bytes);
	}
	if (myList.desc < FIRST || myList.desc >(uint32_t*)((char*)FIRST + SIZE)) {
		printf("\nyou are in restricted zone memdone");
	}
}


void* memalloc(int size) {
	if (size < 1 || size > myList.size - memgetblocksize()) {
		return NULL;
	}
	char flag = 1;
	uint32_t* start = myList.desc;// myList.desc - всегда начало списка, где храним размер блока
	while (flag) {
		if (*start >= size) {
			flag = 0;
			break;
		}
		start = *NextBlock(start);
	}
	if (flag)
		return NULL;
	// мы здесь если есть блок подходящего размера и мы смотрим на его начало

	// проверяем хватит ли нам памяти блоак чтобы его разделить
	if (*start - size > DESC_SIZE) {

		//1) делим блок
		// 2) создадим пустой блок
		// оставляем место для блока пользователя
		uint32_t* nextBlock = (uint32_t*)((char*)start + DESC_SIZE + size);
		// делим память и сохраняем в заголвке следующего блока остаток
		int restMemSize = *start - DESC_SIZE - size;
		*BlockSizeHead(nextBlock) = *BlockSizeEnd(nextBlock, restMemSize) = restMemSize;
		// отмечаем его свободным
		*isFree(nextBlock) = TRUE;
		// предыдущий блок сдедующего будет ссылаться теперь  предыдущий блок текущего блока
		*PrevBlock(nextBlock) = NULL;
		// следующий блок сдедующего будет ссылаться теперь  следующим блоком текущего блока
		*NextBlock(nextBlock) = *NextBlock(start);
		// 2.1. если у нас пока нет блоков то передвигаем начало на этот блок
		if (*PrevBlock(start) == NULL) { // проверяем что текущий блок первый в списке
		   //перемещаем указатель начала списка на новый блок
			myList.desc = nextBlock;
		}

		// 3) создаем блок который выделим юзеру
		*BlockSizeHead(start) = *BlockSizeEnd(start, size) = size;
		*isFree(start) = FALSE;
		myList.size = myList.size - size - DESC_SIZE;
	}
	else {
		// если делить нечего, отдаем пользователю всю память
		// удаляем блок из числа свободных
		*isFree(start) = FALSE;
		uint32_t* nextBlock = *NextBlock(start);
		uint32_t* prevBlock = *PrevBlock(start);
		if (nextBlock != NULL) {
			*PrevBlock(nextBlock) = prevBlock;
		}
		if (prevBlock != NULL) {
			*NextBlock(prevBlock) = nextBlock;
		}
		myList.size = myList.size - *start;
	}
	if (myList.desc < FIRST || myList.desc >(uint32_t*)((char*)FIRST + SIZE)) {
		printf("\nyou are in restricted zone");
	}
	return (void*)((char*)start + DESC_SIZE - sizeof(uint32_t));

}


void memfree(void* p) {
	// находим начало блока
	uint32_t* start = (uint32_t*)((char*)p - DESC_SIZE + sizeof(uint32_t));
	// отмечаем его свободным
	*isFree(start) = TRUE;
	uint32_t* next;
	uint32_t* prev;
	uint32_t* checkSize = &myList.size;


	uint32_t freeSize = *BlockSizeHead(start); // размер памяти которая была у юзера и которую будем освобождать
	// флаги занятости блоков слева и справва
	char flagLeft = 0;
	char flagRight = 0;

	//if (start != FIRST) {  
	if ((uint32_t*)((char*)start - sizeof(uint32_t)) >= (uint32_t*)FIRST) {    //!!!!!! сравнение указателей
		uint32_t sizePrev = *PrevSize(start);
		prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);
		if (*isFree(prev) == TRUE) {
			flagLeft = 1;  // можем мержить блок слева
		}
	}
	//if ((uint32_t*)((char*)start + DESC_SIZE + freeSize) < (uint32_t*)((char*)FIRST + SIZE)) { // если это не крайний блок справа 
	if ((uint32_t*)((char*)start + *start + DESC_SIZE) <= (uint32_t*)((char*)FIRST + SIZE)) {     // !!!! сравнение указателей
		uint32_t* tmp = (uint32_t*)((char*)start + DESC_SIZE + freeSize);
		if (*isFree(tmp) == TRUE) {
			flagRight = 1;
		}
	}

	// освобождаем текущий и добавляем его к списку
	if (flagLeft == 0 && flagRight == 0) {
		uint32_t* elem = myList.desc;
		while (*NextBlock(elem) != NULL) {
			elem = *NextBlock(elem);
		}
		// если мы здесь то elem есть последний элемент в списке
		*NextBlock(elem) = start;
		*NextBlock(start) = NULL;
		*PrevBlock(start) = elem;
		*isFree(start) = TRUE;
		myList.size = myList.size + *start + DESC_SIZE;   ///!!!! плюс размер деска
	}

	// элемент справа свободен. мержимся с ним и перестраиваем указатели и изменяем размер блока
	if (flagLeft == 0 && flagRight == 1) {
		// так мы должны попасть на начало сдежующего блока (если нет то еще попробовать + sizeof(uint32_t))
		next = (uint32_t*)((char*)start + freeSize + DESC_SIZE);
		// добавила
		myList.size = myList.size + *start + DESC_SIZE;    /// !!!! ошибка (была)
		//увеличиваем размер текущего блока на размер следующего + размер дескриптора
		int newMemSize = freeSize + DESC_SIZE + *next;
		// записываем в начало и конец блока
		*BlockSizeHead(start) = *BlockSizeEnd(start, newMemSize) = newMemSize;
		// перестраиваем указатели
		*NextBlock(start) = *NextBlock(next); // ок
		// если есть блок следующий за следующим, привязываем его прев к нашему блоку
		if (*NextBlock(next) != NULL) {
			uint32_t* nextNext = *NextBlock(*NextBlock(next));
			*PrevBlock(nextNext) = start;
		}
		*PrevBlock(start) = *PrevBlock(next);
		// если есть блок пред предыдущего, привязываем его некст к нашему блоку
		if (*PrevBlock(next) != NULL) {
			uint32_t* prevPrev = *PrevBlock(*PrevBlock(next));
			*NextBlock(prevPrev) = start;
		}
		if (next == myList.desc) {    //!!!! добавила
			myList.desc = start;
		}
	}

	// элемент слева свободен. мержимся с ним и изменяем размер блока
	if (flagLeft == 1 && flagRight == 0) {
		myList.size = myList.size + *start + DESC_SIZE;
		uint32_t sizePrev = *PrevSize(start);
		// находим начало левого блока
		prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);
		int newMemSize = sizePrev + *start + DESC_SIZE;
		// меняем размеры блоков
		*BlockSizeHead(prev) = *BlockSizeEnd(prev, newMemSize) = newMemSize;
	}

	// элементы слева и справа свободны. меняем размер. удаляем блок справа
	if (flagLeft == 1 && flagRight == 1) {
		myList.size = myList.size + *start + DESC_SIZE;
		// так мы должны попасть на начало сдежующего блока (если нет то еще попробовать + sizeof(uint32_t))
		next = (uint32_t*)((char*)start + freeSize + DESC_SIZE);
		uint32_t sizePrev = *PrevSize(start);
		// находим начало левого блока
		prev = (uint32_t*)((char*)start - sizePrev - DESC_SIZE);

		// если правый равен первому в списке
		if (next == myList.desc) {
			uint32_t* tmp = *PrevBlock(prev);
			*NextBlock(tmp) = *NextBlock(prev);
			// если предыдущий не последний в списке
			if (*NextBlock(prev) != NULL) {
				uint32_t* tmp2 = *NextBlock(prev);
				*PrevBlock(tmp2) = *PrevBlock(prev);
			}
			*NextBlock(prev) = *NextBlock(next);
			*PrevBlock(prev) = NULL;
			myList.desc = prev;
		}

		//если левый равен первому в списке
		else if (prev == myList.desc) {
			uint32_t* tmp3 = *PrevBlock(next);
			*NextBlock(tmp3) = *NextBlock(next);
			// если правый последний
			if (*NextBlock(next) == NULL) {
				uint32_t* tmp4 = *NextBlock(next);
				*PrevBlock(tmp4) = *PrevBlock(next);
			}
		}

		//если они в середине
		else if (prev != myList.desc && next != myList.desc) {
			uint32_t* prevOfNext = *PrevBlock(next);
			*NextBlock(prevOfNext) = *NextBlock(next);
			if (*NextBlock(next) != NULL) {
				uint32_t* nextOfNext = *NextBlock(next);
				*PrevBlock(nextOfNext) = *PrevBlock(next);
			}
		}

		// меняем размер блокоа
		int newMemSize = sizePrev + DESC_SIZE + *start + DESC_SIZE + *next;
		*BlockSizeHead(prev) = *BlockSizeEnd(prev, newMemSize) = newMemSize;

	}
	if (myList.desc < FIRST || myList.desc >(uint32_t*)((char*)FIRST + SIZE)) {
		printf("\nyou are in restricted zone");
	}
}


int memgetminimumsize() {
	return DESC_SIZE;
}

int memgetblocksize() {
	return DESC_SIZE;
}


//int main() {
//	void* p1 = 0, * p2 = 0, * p3 = 0;
//	int memsize = memgetminimumsize() + 2 * memgetblocksize() + 3;
//	void* ptr = malloc(memsize);
//	meminit(ptr, memsize);
//	p1 = memalloc(1); // Success!
//	p2 = memalloc(1); // Success!
//	p3 = memalloc(1); // Success!
	//	printf("after 20 %d\n", myList.size);
		//uint32_t* trial3 = (uint32_t*)memalloc(15*sizeof(uint32_t*));
	//	printf("after 15 %d\n", myList.size);
		//uint32_t* trial4 = (uint32_t*)memalloc(25 * sizeof(uint32_t*)); 
	//	printf("after 25 %d\n", myList.size);
		//uint32_t* trial5 = (uint32_t*)memalloc(15 * sizeof(uint32_t*));
	//	printf("afterl5 %d\n", myList.size);
		//uint32_t* trial6 = (uint32_t*)memalloc(15 * sizeof(uint32_t*));
		//memdone();
	//	printf("afterl6 %d\n", myList.size);
	//	if ( myList.desc < FIRST /*|| trial3 < fp || trial4 < fp || trial5 < fp || trial6 < fp*/) {
	//		printf("eeeeeee");
	//	}
		//printf("\n%d", sizeof(uint32_t*));
		//uint32_t* trial7 = (uint32_t*)memalloc(15 * sizeof(uint32_t*));
		//uint32_t* trial8 = (uint32_t*)memalloc(50 * sizeof(uint32_t*));*/
		//printf("%p, %p\n", trial, fp  );
		//printf("%d\n",  trial - fp);
		//printf("%d\n", trial2-trial);
		//printf("%d", trial3-trial2);


		//a1 = fp;
		//testBlock* a2 = (testBlock*)((char*)trial2 -DESC_SIZE + sizeof(uint32_t));
		//testBlock* a3 = (testBlock*)((char*)trial3 - DESC_SIZE + sizeof(uint32_t));
		//memfree(trial3);
		//memfree(trial);
		//memfree(trial2);
		//memfree(trial5);
		//memfree(trial4);
		//trial2 = (uint32_t*)memalloc(20 * sizeof(uint32_t*));
		//trial3 = (uint32_t*)memalloc(15 * sizeof(uint32_t*));

		//trial4 = (uint32_t*)memalloc(25 * sizeof(uint32_t*));
		// trial5 = (uint32_t*)memalloc(15 * sizeof(uint32_t*));
		//uint32_t* elem = myList.desc;
		//printf("%p\n", fp);
		//printf("%p , %p\n", *NextBlock(elem), *PrevBlock(elem));
		//uint32_t* second = *NextBlock(elem);
		//printf("%d", *BlockSizeHead(second));
//}

