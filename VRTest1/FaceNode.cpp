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

FaceNode* FaceNode::getNext()
{
	return this->next;
}
