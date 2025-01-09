#pragma once
#include "VertexNode3D.h"
#include "VertexNode3DNode.h"
class Face2
{
	public:
		Face2();
		void add(VertexNode3DNode*);
		void remove(VertexNode3DNode* node);
		VertexNode3DNode* getFront();
		VertexNode3DNode* getLast();
		float average;
	private:
		VertexNode3DNode* front;
		VertexNode3DNode* last;
};

