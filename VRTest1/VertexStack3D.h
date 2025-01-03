#pragma once
#include "VertexNode3D.h"
#include <SDL.h>
class VertexStack3D
{
	public:
		VertexStack3D(VertexNode3D* node);
		VertexStack3D();
		void add(VertexNode3D* node);
		void remove(VertexNode3D* node);
		VertexNode3D* getFront();
		VertexNode3D* getLast();
		void render(SDL_Renderer* renderer);
	private:
		VertexNode3D* front;
		VertexNode3D* last;
};

