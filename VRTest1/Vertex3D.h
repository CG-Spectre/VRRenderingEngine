#pragma once
#include <vector>
#include "Pos.h"
#include "Vertex.h"
class Vertex3D
{
	public:
		Vertex3D(Pos* pos);
		Vertex3D(Pos pos);
		void addConnection(Vertex3D* vertex);
		void addConnection(int vertexId);
		void removeConnection(Vertex3D* vertex);
		std::vector<Vertex3D*> connections;
		std::vector<int> pendingConnections;
		std::vector<int> pendingFaceConnections;
		Pos* getPos();
		Vertex* getVertex2d();
		void addFaceConnection(int vertexId);
		
	private:
		Pos pos;
		Vertex vertex2d;
};

