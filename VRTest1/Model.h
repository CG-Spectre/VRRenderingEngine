#pragma once
#include "RenderableObject.h"
#include "Color.h"
#include "VertexStack.h"
#include "VertexStack3D.h"
#include <string>
class Model : public RenderableObject
{
	public:
		void render(SDL_Renderer* renderer, Player* player) override;
		Model(Pos* pos, float size, Color* color, const char* modelname);
	private:
		std::vector<std::string> splitString(const std::string& str, const char* delimiter);
		Pos* pos;
		float size;
		Color* color;
		VertexStack3D data3d;
};

