#ifndef Queue_h
#define Queue_h

#include "ADT.h"
#include <cstdlib>

class Queue
{
private:
	ADT** data;
	size_t size;
	size_t elNow;
	size_t head;
	size_t tail;
public:
	Queue(const size_t size = 1);
	Queue(const Queue& right);

	Queue& Add(const ADT * right, size_t pos = SIZE_MAX);
	Queue& Remove(size_t pos = SIZE_MAX);

	size_t lenght();

	Queue& Push(const ADT * right);
	ADT* Pop();

	ADT* operator[](const size_t right);
};

#endif // Queue_h
