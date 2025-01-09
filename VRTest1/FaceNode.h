#pragma once
#include "Face2.h"
class FaceNode
{
	public:
		FaceNode(Face2 info);
		Face2* getInfo();
		FaceNode* getNext();
		FaceNode* getPrevious();
		void setNext(FaceNode* next);
		void setPrevious(FaceNode* prev);
	private:
		Face2 info;
		FaceNode* next;
		FaceNode* previous;
};

