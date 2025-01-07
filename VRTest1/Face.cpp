#include "Face.h"
Faceface::Faceface()
{
	this->front = nullptr;
	this->last = nullptr;
}
/*
VertexStack3D::VertexStack3D()
{

}
*/
void Faceface::add(VertexNode3D* node)
{
	if (front == nullptr) {
		this->front = node;
		this->last = this->front;
		return;
	}
	last->setNext(node);
	node->setPrevious(last);
	last = last->getNext();
}

void Faceface::remove(VertexNode3D* node) {
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

VertexNode3D* Faceface::getFront()
{
	return this->front;
}

VertexNode3D* Faceface::getLast()
{
	return this->last;
}