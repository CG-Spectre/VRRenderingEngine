#pragma once
#include "RenderableObject.h"
#include "Color.h"
#include "VertexStack.h"
#include "VertexStack3D.h"
#include "FaceStack.h"
#include <string>
class Model : public RenderableObject
{
	public:
		void render(SDL_Renderer* renderer, Player* player) override;
		Model(const char* objectname, Pos* pos, float size, Color* color, const char* modelname);
		int getObjectType() override;
		FaceStack* getFaces();
	private:
		std::vector<std::string> splitString(const std::string& str, const char* delimiter);
		Pos* pos;
		float size;
		Color* color;
		VertexStack3D data3d;
		FaceStack facesData;
};

