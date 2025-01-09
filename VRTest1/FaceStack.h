#pragma once
#include "FaceNode.h"
class FaceStack
{
	public:
		FaceStack();
		void add(FaceNode* face);
		FaceNode* getLast();
		FaceNode* getFront();
		void setFront(FaceNode* node);
	private:
		FaceNode* front;
		FaceNode* last;
};

