#include "RenderableObject.h"
#include <iostream>
int RenderableObject::getObjectType() {
	return -1;
}

void RenderableObject::render(SDL_Renderer* renderer, Player* player) {
	std::cout << "Attempted to render null object type." << std::endl;
}