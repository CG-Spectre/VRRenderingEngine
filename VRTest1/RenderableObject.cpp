#include "RenderableObject.h"
#include <iostream>
int RenderableObject::getObjectType() {
	return -1;
}

RenderableObject::RenderableObject() : name(nullptr) {

}

void RenderableObject::render(SDL_Renderer* renderer, Player* player) {
	std::cout << "Attempted to render null object type." << std::endl;
}

const char* RenderableObject::getName()
{
	return name;
}

//void RenderableObject::render(SDL_Renderer* renderer, Player* player, RenderStack* renderStack)
//{
//	std::cout << "Attempted to render null object type." << std::endl;
//}


