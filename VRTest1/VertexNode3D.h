#pragma once
#include "Vertex3D.h"
class VertexNode3D
{
	public:
		VertexNode3D(Vertex3D info);
		VertexNode3D(Vertex3D info, VertexNode3D* next);
		VertexNode3D* getNext();
		VertexNode3D* getPrevious();
		Vertex3D* getInfo();
		void setNext(VertexNode3D* next);
		void setPrevious(VertexNode3D* next);
	private:
		Vertex3D info;
		VertexNode3D* next;
		VertexNode3D* previous;
};

