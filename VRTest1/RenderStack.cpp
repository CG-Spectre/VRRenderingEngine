#include "RenderStack.h"

RenderStack::RenderStack(RenderNode* node)
{
	this->front = node;
	this->last = node;
}

void RenderStack::add(RenderNode* node)
{
	this->last->setLink(node);
	this->last = last->getLink();
}

RenderNode* RenderStack::getFront()
{
	return this->front;
}

RenderNode* RenderStack::getLast()
{
	return this->last;
}
