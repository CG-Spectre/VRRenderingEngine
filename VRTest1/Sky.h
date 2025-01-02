#pragma once
#include "RenderableObject.h"
#include "Color.h"
#include <SDL.h>
class Sky : public RenderableObject
{
	public:
		int getObjectType() override;
		Sky(Color* color);
		Color* color;
		void render(SDL_Renderer* renderer, Player* player) override;
};

