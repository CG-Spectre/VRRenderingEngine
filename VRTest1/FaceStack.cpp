#include "FaceStack.h"

FaceStack::FaceStack() : last(nullptr), front(nullptr)
{
}

void FaceStack::add(FaceNode* face)
{
	if (front == nullptr) {
		front = face;
		last = front;
		return;
	}
	last->setNext(face);
	face->setPrevious(last);
	last = last->getNext();
}

FaceNode* FaceStack::getLast()
{
	return last;
}

FaceNode* FaceStack::getFront()
{
	return front;
}

void FaceStack::setFront(FaceNode* node)
{
	this->front->setPrevious(node);
	this->front = node;
}