#pragma once
#include "RenderNode.h"
class RenderStack
{
	public:
		RenderStack(RenderNode* node);
		void add(RenderNode* node);
		RenderNode* getFront();
		RenderNode* getLast();
	private:
		RenderNode* front;
		RenderNode* last;

};

