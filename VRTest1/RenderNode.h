#pragma once
#include "RenderableObject.h"
class RenderNode
{
	public:
		RenderNode(RenderableObject* obj);
		RenderNode(RenderableObject* obj, RenderNode* link);
		RenderableObject* getInfo();
		RenderNode* getLink();
		void setLink(RenderNode* node);
	private:
		RenderableObject* info;
		RenderNode* link;

};

