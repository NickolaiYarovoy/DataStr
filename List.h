#ifndef List_h
#define List_h

#include "ADT.h"
#include <cstddef>

struct Node
{
	ADT* data;
	Node* next;

	explicit Node(const ADT* dataN, Node* nextN = nullptr) : data((ADT*)dataN), next(nextN) {};
};

class List
{
private:
	Node* head;
	size_t elNow;
public:
	List();
	List(const List& right);

   ~List();

	List& Add(const ADT* right, size_t pos = SIZE_MAX);
	List& Remove(const size_t pos);

	size_t lenght();

	ADT* operator[](size_t right);
};

#endif // List_h
