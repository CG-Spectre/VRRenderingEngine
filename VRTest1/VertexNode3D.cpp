#include "VertexNode3D.h"

VertexNode3D::VertexNode3D(Vertex3D info) : info(info), next(nullptr), previous(nullptr)
{
}


VertexNode3D::VertexNode3D(Vertex3D info, VertexNode3D* next) : info(info), next(next), previous(nullptr)
{
}

VertexNode3D* VertexNode3D::getNext()
{
	return this->next;
}

VertexNode3D* VertexNode3D::getPrevious() {
	return this->previous;
}

Vertex3D* VertexNode3D::getInfo()
{
	return &this->info;
}

void VertexNode3D::setNext(VertexNode3D* next)
{
	this->next = next;
}

void VertexNode3D::setPrevious(VertexNode3D* next)
{
	this->previous = next;
}
