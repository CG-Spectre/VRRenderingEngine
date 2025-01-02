#include "Cube.h"
#include <iostream>

Cube::Cube(Pos* pos, float size, Color* color) : pos(pos), size(size), color(color) {}

float* Cube::getSize() {
	return &this->size;
}

int Cube::getObjectType() {
	return 2;
}

void Cube::render(SDL_Renderer* renderer, Player* player)
{	
	
	int size = 200;
	int offset = 300;
	int difference = size / 2.5f;
	SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
	SDL_RenderDrawLine(renderer, offset, offset, offset, offset + size);
	SDL_RenderDrawLine(renderer, offset, offset, offset + size, offset);
	SDL_RenderDrawLine(renderer, offset, offset + size, offset + size, offset + size);
	SDL_RenderDrawLine(renderer, offset + size, offset, offset + size, offset + size);
	
	SDL_RenderDrawLine(renderer, offset + difference, offset + difference, offset + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + difference, offset + difference, offset + size + difference, offset + difference);
	SDL_RenderDrawLine(renderer, offset + difference, offset + size + difference, offset + size + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + size + difference, offset + difference, offset + size + difference, offset + size + difference);

	SDL_RenderDrawLine(renderer, offset, offset, offset + difference, offset + difference);
	SDL_RenderDrawLine(renderer, offset, offset + size, offset + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + size, offset + size, offset + size + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + size, offset, offset + size + difference, offset + difference);
	/*SDL_RenderDrawLine(renderer, offset + difference, offset + difference, offset + size + difference, offset + difference);
	SDL_RenderDrawLine(renderer, offset + difference, offset + size + difference, offset + size + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + size + difference, offset + difference, offset + size + difference, offset + size + difference);*/
}
