#include "Vertex3D.h"

Vertex3D::Vertex3D(Pos* pos) : pos(Pos(pos->getX(), pos->getY(), pos->getZ(), pos->getYaw(), pos->getPitch(), pos->getRoll())), vertex2d(Vertex(Pos2D(0, 0)))
{
}
Vertex3D::Vertex3D(Pos pos) : pos(pos), vertex2d(Vertex(Pos2D(0, 0)))
{
}
void Vertex3D::addConnection(Vertex3D* vertex)
{
	this->connections.push_back(vertex);
}

void Vertex3D::addConnection(int vertexId)
{
	this->pendingConnections.push_back(vertexId);
}

void Vertex3D::removeConnection(Vertex3D* vertex)
{
	connections.erase(std::remove(connections.begin(), connections.end(), vertex), connections.end());
}

Pos* Vertex3D::getPos()
{
	return &pos;
}

Vertex* Vertex3D::getVertex2d() {
	return &this->vertex2d;
}

void Vertex3D::addFaceConnection(int vertexId) {
	this->pendingFaceConnections.push_back(vertexId);
}


