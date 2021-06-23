#ifndef Stack_h
#define Stack_h

#include "ADT.h"
#include <cstddef>

class Stack
{
private:
	ADT** data;
	size_t size;
	size_t elNow;
public:
	Stack(const size_t = 0);
	Stack(const Stack& right);
	~Stack();

	Stack& pushEnd(const ADT* right);
	ADT* popEnd();
	Stack& pushStart(const ADT* right);
	ADT* popStart();

	Stack& Add(const ADT* element, size_t pos = SIZE_MAX);
	Stack& Remove(const size_t pos);

	size_t lenght();

	ADT* operator[](const size_t right);
};

#endif // Stack_h