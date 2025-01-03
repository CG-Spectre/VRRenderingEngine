#include "VertexStack.h"
#include <iostream>

VertexStack::VertexStack(VertexNode* node)
{
	this->front = node;
	this->last = this->front;
}

VertexStack::VertexStack()
{
	this->front = nullptr;
	this->last = nullptr;
}

void VertexStack::add(VertexNode* node)
{
	if (this->front == nullptr) {
		this->front = node;
		this->last = this->front;
		return;
	}
	this->last->setNext(node);
	this->last = this->last->getNext();
}

VertexNode* VertexStack::getFront()
{
	return this->front;
}

VertexNode* VertexStack::getLast()
{
	return this->last;
}

void VertexStack::render(SDL_Renderer* renderer)
{
	VertexNode* currentNode = this->front;
	while (currentNode != nullptr) {
		Vertex* currentVertex = currentNode->getInfo();
		for (Vertex* i : currentVertex->connections) {
			SDL_RenderDrawLine(renderer, currentVertex->getPos()->getX(), currentVertex->getPos()->getY(), i->getPos()->getX(), i->getPos()->getY());
		}
		currentNode = currentNode->getNext();
	}
}
