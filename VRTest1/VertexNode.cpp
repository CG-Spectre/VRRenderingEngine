#include "VertexNode.h"

VertexNode::VertexNode(Vertex info) : info(info), next(nullptr)
{
}

VertexNode::VertexNode(Vertex info, VertexNode* next) : info(info), next(next)
{

}

VertexNode* VertexNode::getNext()
{
	return this->next;
}

Vertex* VertexNode::getInfo()
{
	return &this->info;
}

void VertexNode::setNext(VertexNode* next)
{
	this->next = next;
}
