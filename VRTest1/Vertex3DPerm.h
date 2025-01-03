#pragma once
#include <vector>
#include "Pos.h"
class Vertex3DPerm
{
public:
	Vertex3DPerm(Pos* pos);
	void addConnection(Vertex3DPerm* vertex);
	void addConnection(int vertexId);
	void removeConnection(Vertex3DPerm* vertex);
	std::vector<Vertex3D*> connections;
	Pos* pos;
	std::vector<int> pendingConnections;
};

