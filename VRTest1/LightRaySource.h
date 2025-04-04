#pragma once
#include "RenderableObject.h"
#include "RenderStack.h"
class LightRaySource : public RenderableObject
{
	public:
		LightRaySource(Pos pos);
		int getObjectType() override;
		void render(SDL_Renderer* renderer, Player* player, RenderStack* renderStack);
		//void render(SDL_Renderer* renderer, Player* player, RenderStack* renderStack) override;]
		Pos* getPos();
	private:
		Pos pos;
		int renderBlackList[2] = {0, 2};
};

