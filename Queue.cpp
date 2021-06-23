#include "Queue.h"

Queue::Queue(size_t size)
{
	if (size == 0)
		throw std::invalid_argument("Invalid size");

	this->size = size;
	elNow = 0;
	head = tail = 0;
	data = new ADT * [size];
}
Queue::Queue(const Queue& right)
{
	this->size = right.size;
	elNow = right.elNow;
	head = right.head;
	tail = right.tail;
	data = new ADT * [size];
	for (size_t i = 0; i < size; i++)
	{
		if (right.data[i] != nullptr) data[i] = right.data[i];
		else data[i] = nullptr;
	}
}

Queue& Queue::Add(const ADT * right, size_t pos)
{
	if (pos == SIZE_MAX) pos = elNow;
	if (pos > elNow)
		throw std::out_of_range("Index was out of range");
	if (size == elNow)
		throw std::out_of_range("Number of elements is max");

	if (pos == elNow)
	{
		data[(pos + head) % size] = (ADT*) right;
	}
	else
	{
		for (size_t i = elNow; i > pos; i--)
			data[(i + head) % size] = data[(i - 1 + head) % size];

		data[(pos + head) % size] = (ADT*)right;
	}
	tail = (tail + 1) % size;
	elNow++;
	return *this;
}
Queue& Queue::Remove(size_t pos)
{
	if (elNow == 0)
		throw std::out_of_range("There is no elements");

	for (size_t i = pos; i != tail; i = (i + 1) % size)
		data[i % size] = data[(i + 1) % size];

	data[tail] = nullptr;
	tail = (tail - 1 + size) % size;
	elNow--;
	return *this;
}

size_t Queue::lenght()
{
	return elNow;
}

Queue& Queue::Push(const ADT * right)
{
	if (size == elNow)
		throw std::out_of_range("Number of elements is max");

	if(tail == head) head = (head + 1) % size;
	tail = (tail + 1) % size;
	data[tail] = (ADT*) right;
	elNow++;
	return *this;
}
ADT* Queue::Pop()
{
	if (elNow == 0)
		throw std::out_of_range("There is no elements");

	head = (head + 1) % size;
	return data[(head - 1 + size) % size];
}

ADT* Queue::operator[](const size_t right)
{
	if (right > elNow)
		throw std::out_of_range("Index was out of range");

	return data[(right + head) % size];
}