#pragma once
#include "VertexNode3D.h"
class Faceface
{
	public:
		Faceface();
		void add(VertexNode3D* node);
		void remove(VertexNode3D* node);
		VertexNode3D* getFront();
		VertexNode3D* getLast();
	private:
		VertexNode3D* front;
		VertexNode3D* last;
};
