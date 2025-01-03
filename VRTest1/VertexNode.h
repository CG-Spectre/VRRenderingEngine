#pragma once
#include "Vertex.h"
class VertexNode
{
	public:
		VertexNode(Vertex info);
		VertexNode(Vertex info, VertexNode* next);
		VertexNode* getNext();
		Vertex* getInfo();
		void setNext(VertexNode* next);
	private:
		Vertex info;
		VertexNode* next;
};

