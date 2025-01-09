#include "FaceNode.h"

FaceNode::FaceNode(Face2 info) : info(info), next(nullptr)
{

}

Face2* FaceNode::getInfo()
{
	return &this->info;
}

void FaceNode::setNext(FaceNode* next) {
	this->next = next;
}

void FaceNode::setPrevious(FaceNode* prev)
{
	this->previous = prev;
}

FaceNode* FaceNode::getNext()
{
	return this->next;
}

FaceNode* FaceNode::getPrevious()
{
	return this->previous;
}
