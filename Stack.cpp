#include "Stack.h"

Stack::Stack(const size_t size)
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
Stack::Stack(const Stack& right)
{
	size = right.size;
	elNow = right.elNow;
	if(size == 0)
	{
		this->data = nullptr;
		return;
	}
	for (size_t i = 0; i < elNow; i++) *data[i] = *right.data[i];
	for (size_t i = elNow; i < size; i++) data[i] = nullptr;
}
Stack::~Stack()
{
    delete[] data;
}

Stack& Stack::pushEnd(const ADT* right)
{
	if (elNow == size)
	{
        ADT** temp = data;
        data = new ADT * [(size == 0 ? 1 : size * 2)];
		for (size_t i = 0; i < size; i++)
            data[i] = temp[i];
        for (size_t i = size; i < size * 2; i++)
			data[i] = nullptr;
	}

	data[elNow] = (ADT*) right;
	elNow++;

	return *this;
}
ADT* Stack::popEnd()
{
	if (elNow == 0)
		throw std::out_of_range("No data");

	elNow--;
	return std::move(this->data[elNow]);
}
Stack& Stack::pushStart(const ADT* right)
{
	if (elNow == size)
	{
		ADT** temp = data;
        data = new ADT*[(size == 0 ? 1 : size * 2)];
		for (size_t i = 0; i < size; i++)
            data[i] = temp[i];
		for (size_t i = size; i < size * 2; i++)
			data[i] = nullptr;
	}

	for (size_t i = elNow; i > 0; i--)
		data[i] = data[i - 1];

	data[0] = (ADT*) right;
	elNow++;

	return *this;
}
ADT* Stack::popStart()
{
	if (elNow == 0)
		throw std::out_of_range("No data");

	ADT* temp = data[0];
	elNow--;

	for (size_t i = 0; i < elNow; i++)
		data[i] = data[i + 1];

	return std::move(temp);
}

Stack& Stack::Add(const ADT* element, size_t pos)
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
Stack& Stack::Remove(const size_t pos)
{
	if (pos > elNow) throw std::out_of_range("Index is out of range");

	for (size_t i = pos; i < elNow; i++)
	{
		data[i] = std::move(data[i + 1]);
	}
	delete data[elNow];
	data[elNow] = nullptr;
	elNow--;
	return *this;
}

size_t Stack::lenght()
{
	return elNow;
}

ADT* Stack::operator[](size_t right)
{
	if (right >= elNow)
		throw std::out_of_range("Index is out of range");

	return data[right];
}
