#ifndef _UTILS_h
#define _UTILS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Point {
public:
	uint8_t x, y;
	Point(uint8_t x, uint8_t y);
	Point();
};

template <class T>
class LinkedList
{
public:
	class Node
	{
	public:
		Node* next;
		T data;
	};
	uint8_t length;
	Node* head;

	LinkedList();
	~LinkedList();
	void add(T);
	void clear();
};


// The duty calls implementation here for some sort of weird compiler template necessity later needed in code

template <class T>
LinkedList<T>::LinkedList() {
	this->length = 0;
	this->head = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node* next = head;
	Node* cur = NULL;
	while (next != NULL) {
		cur = next;
		next = next->next;
		delete cur;
	}
}

template <class T>
void LinkedList<T>::add(T data) {
	Node* node = new Node();
	node->data = data;
	node->next = this->head;
	this->head = node;
	this->length++;
}

template <class T>
void LinkedList<T>::clear() {
	Node* next = head;
	Node* cur = NULL;
	while (next != NULL) {
		cur = next;
		next = next->next;
		delete cur;
	}
	this->length = 0;
}

#endif