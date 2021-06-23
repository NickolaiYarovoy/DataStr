#include "Array.h"
#include <stdexcept>


Array::Array(size_t size)
{
    this->size = size;
    if (size == 0)
    {
        this->data = nullptr;
        return;
    }
    data = new ADT * [size];
    elNow = 0;

    for (size_t i = 0; i < size; i++) data[i] = nullptr;
}
Array::Array(const Array& right)
{
	size = right.size;
	elNow = right.size;
	for (size_t i = 0; i < size; i++) *data[i] = *right.data[i];
}
Array::~Array()
{
	delete[] data;
}

Array& Array::Add(const ADT* element, size_t pos)
{
	if (elNow == size)
	{
		ADT** temp = data;
		data = new ADT * [(size != 0 ? size * 2 : 1)];
		for (size_t i = 0; i < size; i++)
		{
			data[i] = temp[i];
		}
		for (size_t i = size; i < size*2; i++) data[i] = nullptr;
		delete temp;
		size *= 2;
	}

	if (pos == SIZE_MAX) pos = elNow;

	if (pos > elNow)
		throw std::out_of_range("Index is out of range");

	if (pos == elNow)
	{
		data[pos] = (ADT*) element;
	}
	else
	{
		for (size_t i = elNow; i > pos; i--)
		{
			data[i] = data[i - 1];
		}
		data[pos] = (ADT*) element;
	}

	elNow++;

	return *this;
}
Array& Array::Remove(const size_t pos)
{
	if(pos > elNow) throw std::out_of_range("Index is out of range");

	for (size_t i = pos; i < elNow; i++)
	{
        data[i] = data[i + 1];
	}
	delete data[elNow];
	data[elNow] = nullptr;
	elNow--;
	return *this;
}

size_t Array::lenght()
{
	return elNow;
}

ADT* Array::operator[](size_t right)
{
	if (right >= elNow)
		throw std::out_of_range("Index is out of range");

	return data[right];
}

