#include "VertexStack3D.h"
#include <iostream>

VertexStack3D::VertexStack3D(VertexNode3D* node)
{
	this->front = node;
	this->last = this->front;
}

VertexStack3D::VertexStack3D()
{
	this->front = nullptr;
	this->last = nullptr;
}
/*
VertexStack3D::VertexStack3D()
{

}
*/
void VertexStack3D::add(VertexNode3D* node)
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

void VertexStack3D::remove(VertexNode3D* node) {
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

VertexNode3D* VertexStack3D::getFront()
{
	return this->front;
}

VertexNode3D* VertexStack3D::getLast()
{
	return this->last;
}

void VertexStack3D::render(SDL_Renderer* renderer)
{
	std::cout << "Cannot render a 3D vertex stack directly!" << std::endl;
}
