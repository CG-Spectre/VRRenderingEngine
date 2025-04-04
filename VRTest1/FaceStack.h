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
		int getSize();
	private:
		int size = 0;
		FaceNode* front;
		FaceNode* last;
};

