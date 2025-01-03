#pragma once
#include "Pos2D.h"
#include <vector>
class Vertex
{
	public:
		Vertex(Pos2D* pos);
		Vertex(Pos2D pos);
		Pos2D* getPos();
		void addConnection(Vertex* vertex);
		void removeConnection(Vertex* vertex);
		std::vector<Vertex*> connections;
	private:
		Pos2D pos;
};

