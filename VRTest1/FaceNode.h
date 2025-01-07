#pragma once
#include "Face2.h"
class FaceNode
{
	public:
		FaceNode(Face2 info);
		Face2* getInfo();
		FaceNode* getNext();
		void setNext(FaceNode* next);
	private:
		Face2 info;
		FaceNode* next;
};

