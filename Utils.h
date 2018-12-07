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
private:
	uint8_t length;
public:
	class Node
	{
	public:
		Node* next;
		Node* previous;
		T data;
	};

	Node* head;
	Node* tail;
	

	LinkedList();
	~LinkedList();
	void add(T);
	void remove_tail();
	void clear();
	// Can handle redeletion of nodes
	void remove(Node*);

	T getHead();
	T getTail();
	Node* getHeadPointer();
	uint8_t getLength();
};


// The duty calls implementation here for some sort of weird compiler template necessity later needed in code

template <class T>
LinkedList<T>::LinkedList() {
	this->length = 0;
	this->head = NULL;
	this->tail = NULL;
}

template <class T>
LinkedList<T>::~LinkedList() {
	Node* next = this->head;
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
	node->previous = NULL;

	this->head = node;
	this->length++;
	
	if (this->length == 1) this->tail = this->head;
	else if (this->length >= 2) {
		this->head->next->previous = this->head;
	}
}

template <class T>
void LinkedList<T>::clear() {
	Node* next = this->head;
	Node* cur = NULL;
	while (next != NULL) {
		cur = next;
		next = next->next;
		delete cur;
	}
	this->length = 0;
	this->head = NULL;
	this->tail = NULL;
}

template <class T>
void LinkedList<T>::remove_tail() {
	if (this->tail != NULL) {
		Node* aux = this->tail->previous;
		delete this->tail;
		this->tail = aux;
		if (this->tail != NULL) {
			this->tail->next = NULL;
			this->length--;
		}
	}
}

template <class T>
void LinkedList<T>::remove(LinkedList<T>::Node* node) {
	if (this->length == 0) return;
	if (this->length == 1) {
		this->head = this->tail = NULL;
		return;
	}
	bool exists = false;
	for (LinkedList<T>::Node* it; (it != NULL) && (!exists); it = it->next) {
		if (it == node) exists = true;
	}
	if (exists) {
		node->next->previous = node->previous;
		node->previous->next = node->next;
		delete node;
		this->length--;
	}
}

template <class T>
T LinkedList<T>::getHead() {
	return this->head->data;
}

template <class T>
T LinkedList<T>::getTail() {
	return this->tail->data;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getHeadPointer() {
	return this->head;
}

template <class T>
uint8_t LinkedList<T>::getLength() {
	return this->length;
}

#endif