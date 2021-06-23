#ifndef Array_h
#define Array_h

#include "ADT.h"
#include <cstddef>

class Array
{
private:
	ADT** data;
	size_t size;
	size_t elNow;
public:
	Array(const size_t size = 0);
	Array(const Array& right);
   ~Array();

	Array& Add(const ADT* element, size_t pos = SIZE_MAX);
	Array& Remove(const size_t pos);

	size_t lenght();

	ADT* operator[](const size_t right);
};

#endif // Array_h
