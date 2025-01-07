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