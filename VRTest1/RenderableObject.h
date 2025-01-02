#pragma once
#include <SDL.h>
#include "Player.h"
class RenderableObject
{
	public:
		virtual int getObjectType();
		virtual void render(SDL_Renderer* renderer, Player* player);
};

