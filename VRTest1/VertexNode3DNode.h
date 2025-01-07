#pragma once
#include "VertexNode3D.h"
class VertexNode3DNode
{
	public:
		VertexNode3DNode(VertexNode3D* info);
		VertexNode3DNode* getNext();
		void setNext(VertexNode3DNode* node);
		VertexNode3DNode* getPrevious();
		void setPrevious(VertexNode3DNode* node);
		VertexNode3D* getInfo();
		std::vector<VertexNode3DNode*> faceConnections;
		std::vector<VertexNode3DNode*> faceConnectionsTmp;
		std::vector<Vertex3D*> connections;
		void addFaceConnection(VertexNode3DNode* vertex);
		void removeFaceConnectionTmp(VertexNode3DNode* vertex);
		void addConnection(Vertex3D* vertex);
		//void setFirst(VertexNode3D* node);
	private:
		VertexNode3D* info;
		VertexNode3DNode* next;
		VertexNode3DNode* previous;
};

