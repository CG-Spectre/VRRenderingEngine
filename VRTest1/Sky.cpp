#include "Sky.h"
#include <iostream>

int Sky::getObjectType()
{
	return 1;
}

Sky::Sky(Color* color) : color(color)
{

}

void Sky::render(SDL_Renderer* renderer, Player* player)
{
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a); // Black
	SDL_RenderClear(renderer);
}