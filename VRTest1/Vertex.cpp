#include "Vertex.h"

Vertex::Vertex(Pos2D pos) : pos(pos)
{
}
Pos2D* Vertex::getPos()
{
	return &this->pos;
}
void Vertex::addConnection(Vertex* vertex)
{
	this->connections.push_back(vertex);
}

void Vertex::removeConnection(Vertex* vertex)
{
	connections.erase(std::remove(connections.begin(), connections.end(), vertex), connections.end());
}
