#pragma once
#include "VertexNode.h"
#include <SDL.h>
class VertexStack
{
	public:
		VertexStack(VertexNode* node);
		VertexStack();
		void add(VertexNode* node);
		VertexNode* getFront();
		VertexNode* getLast();
		void render(SDL_Renderer* renderer);
	private:
		VertexNode* front;
		VertexNode* last;
};

