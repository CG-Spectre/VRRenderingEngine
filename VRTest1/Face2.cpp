#include "Face2.h"
#include <iostream>

Face2::Face2()
{
    this->front = nullptr;
    this->last = nullptr;
}

void Face2::add(VertexNode3DNode* node)
{
	if (front == nullptr) {
		this->front = node;
		this->last = this->front;
		return;
	}
	last->setNext(node);
	node->setPrevious(last);
	last = node;
	//std::cout << (last->getNext() == nullptr) << std::endl;
}

void Face2::remove(VertexNode3DNode* node)
{
	if (node->getNext() == nullptr && node->getPrevious() == nullptr) {
		return;
	}
	if (node->getNext() == nullptr) {
		node->getPrevious()->setNext(nullptr);
		return;
	}
	if (node->getPrevious() == nullptr) {
		if (node == this->front) {
			this->front = node->getNext();
			return;
		}
		return;
	}
	node->getPrevious()->setNext(node->getNext());
}

VertexNode3DNode* Face2::getFront()
{
	return this->front;
}

VertexNode3DNode* Face2::getLast()
{
	return this->last;
}
