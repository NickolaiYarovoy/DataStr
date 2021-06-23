#include "List.h"

List::List()
{
	elNow = 0;
	head = nullptr;
}
List::List(const List& right)
{
	elNow = right.elNow;

	head = new Node(right.head->data, new Node(head->next->data));
	Node* now = head->next;
	Node* nowCopy = right.head->next;
	for (size_t i = 1; i < elNow - 1; i++)
	{
		now->next = new Node(nowCopy->data);
		now = now->next;
		nowCopy = nowCopy->next;
	}
	now->data = nowCopy->data;
}

List::~List()
{
    delete[] head;
}

List& List::Add(const ADT* right, size_t pos)
{
	if (pos == SIZE_MAX) pos = elNow;

	if (pos > elNow)
		throw std::out_of_range("Index was out of range");

	if (pos == 0)
    {
        head = new Node((ADT*)right, head);
	}
	else
	{
		Node* el = head;

        for (size_t i = 1; i < pos; i++) el = el->next;

		Node* element = new Node((ADT*)right, el);
		el->next = element;
	}
	elNow++;
	return *this;
}
List& List::Remove(const size_t pos)
{
	if (elNow == 0)
		throw std::out_of_range("There is no elements in list");

	if (pos == 0)
	{
		Node* temp = head;
		head = head->next;
		temp->next = nullptr;
		delete[] temp;
	}
	else
	{
		Node* now = head;
		for (size_t i = 1; i < pos; i++) now = now->next;
		Node* temp = now->next;
		now->next = now->next->next;
		temp->next = nullptr;
		delete[] temp;
	}
	return *this;
}

size_t List::lenght()
{
	return elNow;
}

ADT* List::operator[](size_t right)
{
	Node* now = head;
    for (size_t i = 0; i < right; i++)
    {
        if(now->next != nullptr) now = now->next;
        else throw std::out_of_range("Index was out of range");
    }
	return now->data;
}
