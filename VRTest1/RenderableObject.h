#pragma once
#include <SDL.h>
#include "Player.h"
class RenderableObject
{
	public:
		virtual int getObjectType();
		RenderableObject();
		virtual void render(SDL_Renderer* renderer, Player* player);
		const char* getName();
		//virtual void render(SDL_Renderer* renderer, Player* player, RenderStack* renderStack);
	protected:
		const char* name;
};

