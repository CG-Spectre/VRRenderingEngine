#pragma once
#include "FaceNode.h"
class FaceStack
{
	public:
		FaceStack();
		void add(FaceNode* face);
		FaceNode* getLast();
		FaceNode* getFront();
	private:
		FaceNode* front;
		FaceNode* last;
};
