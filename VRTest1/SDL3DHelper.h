#pragma once
#include "Pos2D.h"
#include <SDL.h>
#include "VertexStack.h"
#include "VertexStack3D.h"
#include "FaceStack.h";
class SDL3DHelper
{
	public:
		static int SCREEN_WIDTH;
		static int SCREEN_HEIGHT;
		static float FOCAL_LENGTH;
		static Uint16 SDL_DELAY;
		static Uint16 SDL_SCALE;
		static void convertPos(Pos2D* pos);
		static Pos2D convertPosR(Pos2D pos);
		static void renderDrawLine(SDL_Renderer* renderer, Pos2D from, Pos2D to);
		
		static FaceStack getFaces(VertexStack3D* vertices);
		static void renderFillFace(SDL_Renderer* renderer, VertexNode3DNode front);
		static bool isWithinBounds(int x, int y);
		//static void renderFillFace(SDL_Renderer* renderer, VertexStack vertices);
		static void drawLineCustom(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
		static bool compareY(const SDL_Point& a, const SDL_Point& b);
		static int interpolateX(const SDL_Point& p1, const SDL_Point& p2, int y);
		static void fillQuadrilateral(SDL_Renderer* renderer, SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4);
		static void fillTriangle(SDL_Renderer* renderer, SDL_Point p1, SDL_Point p2, SDL_Point p3);
		static void fillQuadrilateralPos(SDL_Renderer* renderer, Pos2D p1, Pos2D p2, Pos2D p3, Pos2D p4);
};
