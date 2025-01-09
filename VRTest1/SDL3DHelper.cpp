#include "SDL3DHelper.h"
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include "VertexStack3D.h"
#include "Player.h"
#include <thread>


int SDL3DHelper::SCREEN_HEIGHT = 0;
int SDL3DHelper::SCREEN_WIDTH = 0;
float SDL3DHelper::FOCAL_LENGTH = 1000.0;
Uint16 SDL3DHelper::SDL_DELAY = 1;
Uint16 SDL3DHelper::SDL_SCALE = 100;

void SDL3DHelper::convertPos(Pos2D* pos)
{
	pos->setX(pos->getX() + SCREEN_WIDTH / 2);
	pos->setY(-pos->getY() + SCREEN_HEIGHT / 2);
}
Pos2D SDL3DHelper::convertPosR(Pos2D pos)
{
	pos.setX(pos.getX() + SCREEN_WIDTH / 2);
	pos.setY(-pos.getY() + SCREEN_HEIGHT / 2);
	return pos;
}
void SDL3DHelper::renderDrawLine(SDL_Renderer* renderer, Pos2D from, Pos2D to)
{
	convertPos(&from);
	convertPos(&to);
	
	SDL_RenderDrawLine(renderer, from.getX(), from.getY(), to.getX(), to.getY());
}


FaceStack SDL3DHelper::getFaces(VertexStack3D* vertices) {
	FaceStack stack;
	return stack;
}

void SDL3DHelper::processLightInformation(SDL_Renderer* renderer, RenderableObject* object, Player* player, Pos* lightPos) {
	lightPos->setYaw(5);
	lightPos->setPitch(5);
	lightPos->setRoll(5);
	std::cout << lightPos->getNormalizedRotation().x << std::endl;
}

void SDL3DHelper::renderFillFace(SDL_Renderer* renderer, /*VertexStack vertices*/ VertexNode3DNode front)
{	

	bool isNext = true;
	front.faceConnectionsTmp = front.faceConnections;
	VertexNode3DNode* currentVertex1 = &front;
	VertexNode3DNode* currentVertex2 = &front;
	if (currentVertex1 == nullptr) {
		return;
	}
	std::vector<VertexNode3DNode*> seen;
	int times = 1;
	int count = 0;
	int sawn = 0;
	while (isNext) {

		VertexNode3DNode* nextVertex1 = currentVertex1->faceConnectionsTmp[0];
		if (nextVertex1 == currentVertex2) {
			isNext = false;
			break;
		}
		
		nextVertex1->faceConnectionsTmp = nextVertex1->faceConnections;
		for (VertexNode3DNode* i : currentVertex1->faceConnections) {
			Pos* posi = i->getInfo()->getInfo()->getPos();
			Pos* currentPos = nextVertex1->getInfo()->getInfo()->getPos();
			if (posi == currentPos) {
				currentVertex1->removeFaceConnectionTmp(i);
			}
		}
		for (VertexNode3DNode* i : nextVertex1->faceConnections) {
			Pos* posi = i->getInfo()->getInfo()->getPos();
			Pos* currentPos = currentVertex1->getInfo()->getInfo()->getPos();
			if (posi == currentPos) {
				nextVertex1->removeFaceConnectionTmp(i);
			}
		}
		
		VertexNode3DNode* nextVertex2 = currentVertex2->faceConnectionsTmp[0];
		
		nextVertex2->faceConnectionsTmp = nextVertex2->faceConnections;
		for (VertexNode3DNode* i : currentVertex2->faceConnections) {
			Pos* posi = i->getInfo()->getInfo()->getPos();
			Pos* currentPos = nextVertex2->getInfo()->getInfo()->getPos();
			if (posi == currentPos) {
				currentVertex2->removeFaceConnectionTmp(i);
			}
		}
		for (VertexNode3DNode* i : nextVertex2->faceConnections) {
			Pos* posi = i->getInfo()->getInfo()->getPos();
			Pos* currentPos = currentVertex2->getInfo()->getInfo()->getPos();
			if (posi == currentPos) {
				nextVertex2->removeFaceConnectionTmp(i);
			}
		}
		
		SDL_Point p1 = { SDL3DHelper::convertPosR(*currentVertex1->getInfo()->getInfo()->getVertex2d()->getPos()).getX(), SDL3DHelper::convertPosR(*currentVertex1->getInfo()->getInfo()->getVertex2d()->getPos()).getY() };
		SDL_Point p2 = { SDL3DHelper::convertPosR(*nextVertex1->getInfo()->getInfo()->getVertex2d()->getPos()).getX(), SDL3DHelper::convertPosR(*nextVertex1->getInfo()->getInfo()->getVertex2d()->getPos()).getY() };
		SDL_Point p3 = { SDL3DHelper::convertPosR(*currentVertex2->getInfo()->getInfo()->getVertex2d()->getPos()).getX(), SDL3DHelper::convertPosR(*currentVertex2->getInfo()->getInfo()->getVertex2d()->getPos()).getY() };
		SDL_Point p4 = { SDL3DHelper::convertPosR(*nextVertex2->getInfo()->getInfo()->getVertex2d()->getPos()).getX(), SDL3DHelper::convertPosR(*nextVertex2->getInfo()->getInfo()->getVertex2d()->getPos()).getY() };
		
		if ((p1.x != p3.x || p1.y != p3.y)/* && (isWithinBounds(p1.x, p1.y) && isWithinBounds(p2.x, p2.y) && isWithinBounds(p3.x, p3.y))*/) {
			convertWithinBounds(&p1, &p2, &p3, &p4);
			SDL3DHelper::fillTriangle(renderer, p1, p2, p3);
		}
		if ((p2.x != p4.x || p2.y != p4.y)/* && (isWithinBounds(p4.x, p4.y) && isWithinBounds(p2.x, p2.y) && isWithinBounds(p3.x, p3.y))*/) {
			convertWithinBounds(&p1, &p2, &p3, &p4);
			SDL3DHelper::fillTriangle(renderer, p4, p2, p3);
		}
		currentVertex1 = nextVertex1;
		currentVertex2 = nextVertex2;
		count++;
		if (currentVertex1 == currentVertex2) {
			isNext = false;
			break;
		}
	}
}

void SDL3DHelper::convertWithinBounds(SDL_Point* p1, SDL_Point* p2, SDL_Point* p3, SDL_Point* p4) {
	int leftBounds = 0;
	int rightBounds = SCREEN_WIDTH;
	int topBounds = 0;
	int bottomBounds = SCREEN_HEIGHT;
	p1->x = std::min(std::max(leftBounds, p1->x), rightBounds);
	p2->x = std::min(std::max(leftBounds, p2->x), rightBounds);
	p3->x = std::min(std::max(leftBounds, p3->x), rightBounds);
	p4->x = std::min(std::max(leftBounds, p4->x), rightBounds);
	p1->y = std::min(std::max(topBounds, p1->y), bottomBounds);
	p2->y = std::min(std::max(topBounds, p2->y), bottomBounds);
	p3->y = std::min(std::max(topBounds, p3->y), bottomBounds);
	p4->y = std::min(std::max(topBounds, p4->y), bottomBounds);
}

bool SDL3DHelper::isWithinBounds(int x, int y) {
	int leftBounds = 0;
	int rightBounds = SCREEN_WIDTH;
	int topBounds = 0;
	int bottomBounds = SCREEN_HEIGHT;
	return x > leftBounds && x < rightBounds && y < bottomBounds && y > topBounds;

}

void SDL3DHelper::drawLineCustom(SDL_Renderer* renderer, int x1, int y1, int x2, int y2) {
	int dx = abs(x2 - x1);  // Difference in x-coordinates
	int dy = abs(y2 - y1);  // Difference in y-coordinates
	int sx = (x1 < x2) ? 1 : -1;  // Step in x direction
	int sy = (y1 < y2) ? 1 : -1;  // Step in y direction
	int err = dx - dy;  // Error term for Bresenham's algorithm

	while (true) {
		// Draw a point at (x1, y1)
		SDL_RenderDrawPoint(renderer, x1, y1);

		// If we have reached the endpoint, stop
		if (x1 == x2 && y1 == y2) {
			break;
		}

		// Calculate the error term for the next point
		int e2 = err * 2;

		if (e2 > -dy) {
			err -= dy;
			x1 += sx;
		}

		if (e2 < dx) {
			err += dx;
			y1 += sy;
		}
	}
}
bool SDL3DHelper::compareY(const SDL_Point& a, const SDL_Point& b) {
	return a.y < b.y;
}
int SDL3DHelper::interpolateX(const SDL_Point& p1, const SDL_Point& p2, int y) {
	if (p1.y == p2.y) return p1.x; // Handle horizontal edges
	return p1.x + (p2.x - p1.x) * (y - p1.y) / (p2.y - p1.y);
}
void SDL3DHelper::fillQuadrilateral(SDL_Renderer* renderer, SDL_Point p1, SDL_Point p2, SDL_Point p3, SDL_Point p4) {
	
}

void SDL3DHelper::fillTriangle(SDL_Renderer* renderer, SDL_Point p1, SDL_Point p2, SDL_Point p3) {
	// Sort points by y-coordinate (ascending order)
	SDL_Point points[3] = { p1, p2, p3 };
	std::sort(points, points + 3, [](const SDL_Point& a, const SDL_Point& b) {
		return a.y < b.y;
		});

	// Helper function to interpolate x-coordinates between two points
	auto InterpolateX = [](const SDL_Point& a, const SDL_Point& b, int y) {
		if (a.y == b.y) return a.x; // Avoid division by zero
		return a.x + (b.x - a.x) * (y - a.y) / (b.y - a.y);
		};

	// Draw scanlines between points
	for (int y = points[0].y; y <= points[2].y; ++y) {
		
		if (y < points[1].y) {
			// Top part of the triangle
			int x1 = InterpolateX(points[0], points[1], y);
			int x2 = InterpolateX(points[0], points[2], y);
			if (x1 > x2) std::swap(x1, x2);
			SDL_RenderDrawLine(renderer, x1, y, x2, y);
		}
		else {
			// Bottom part of the triangle
			int x1 = InterpolateX(points[1], points[2], y);
			int x2 = InterpolateX(points[0], points[2], y);
			if (x1 > x2) std::swap(x1, x2);
			SDL_RenderDrawLine(renderer, x1, y, x2, y);
		}
	}
}

void SDL3DHelper::fillQuadrilateralPos(SDL_Renderer* renderer, Pos2D p1, Pos2D p2, Pos2D p3, Pos2D p4)
{
	SDL3DHelper::fillQuadrilateral(renderer, {p1.getX(), p1.getY()}, { p2.getX(), p2.getY() }, { p3.getX(), p3.getY() }, { p4.getX(), p4.getY() });
}



