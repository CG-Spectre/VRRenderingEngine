#include "VertexNode3DNode.h"

VertexNode3DNode::VertexNode3DNode(VertexNode3D* info) : info(info), next(nullptr), previous(nullptr)
{
	
}

VertexNode3DNode* VertexNode3DNode::getNext()
{
	return this->next;
}

void VertexNode3DNode::setNext(VertexNode3DNode* node)
{
	this->next = node;
}

VertexNode3DNode* VertexNode3DNode::getPrevious()
{
	return this->previous;
}

void VertexNode3DNode::setPrevious(VertexNode3DNode* node)
{
	this->previous = node;
}

VertexNode3D* VertexNode3DNode::getInfo()
{
	return this->info;
}

void VertexNode3DNode::addFaceConnection(VertexNode3DNode* vertex)
{
	this->faceConnections.push_back(vertex);
}
void VertexNode3DNode::removeFaceConnectionTmp(VertexNode3DNode* vertex)
{
	faceConnectionsTmp.erase(std::remove(faceConnectionsTmp.begin(), faceConnectionsTmp.end(), vertex), faceConnectionsTmp.end());
}
void VertexNode3DNode::addConnection(Vertex3D* vertex)
{
	this->connections.push_back(vertex);
}
