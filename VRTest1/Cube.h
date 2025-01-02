#pragma once
#include "Pos.h"
#include "RenderableObject.h"
#include "Color.h"
class Cube : public RenderableObject
{
	public:
		Pos* pos;
		Color* color;
		Cube(Pos* pos, float size, Color* color);
		float* getSize();
		int getObjectType() override;
		void render(SDL_Renderer* renderer, Player* player) override;
	private:
		float size;
};

