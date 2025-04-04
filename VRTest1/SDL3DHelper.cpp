#include "SDL3DHelper.h"
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include "VertexStack3D.h"
#include "Player.h"
#include <thread>
#include "Model.h"
#include <vector>


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

void SDL3DHelper::renderDrawPoint(SDL_Renderer* renderer, Pos2D point)
{
	convertPos(&point);

	SDL_RenderDrawPoint(renderer, point.getX(), point.getY());
}
void SDL3DHelper::renderDrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
	int x = radius;
	int y = 0;
	int p = 1 - radius;

	while (x >= y) {
		renderDrawPoint(renderer, Pos2D(centerX + x, centerY + y));
		renderDrawPoint(renderer, Pos2D(centerX - x, centerY + y));
		renderDrawPoint(renderer, Pos2D(centerX + x, centerY - y));
		renderDrawPoint(renderer, Pos2D(centerX - x, centerY - y));
		renderDrawPoint(renderer, Pos2D(centerX + y, centerY + x));
		renderDrawPoint(renderer, Pos2D(centerX - y, centerY + x));
		renderDrawPoint(renderer, Pos2D(centerX + y, centerY - x));
		renderDrawPoint(renderer, Pos2D(centerX - y, centerY - x));

		y++;
		if (p <= 0) {
			p += 2 * y + 1;
		}
		else {
			x--;
			p += 2 * (y - x) + 1;
		}
	}
}

void SDL3DHelper::renderDrawCircleFill(SDL_Renderer* renderer, int centerX, int centerY, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
				renderDrawPoint(renderer, Pos2D(centerX + x, centerY + y));
            }
        }
    }
}

void SDL3DHelper::renderFillElipse3DInBounds(SDL_Renderer* renderer, Player* player, Vector3 p1, Vector3 p2, Vector3 p3) {
	Pos2D p1pos = convert3d2d(&p1, player);
	Pos2D p2pos = convert3d2d(&p2, player);
	Pos2D p3pos = convert3d2d(&p3, player);
	double x1 = p1pos.getX(), y1 = p1pos.getY();
	double x2 = p2pos.getX(), y2 = p2pos.getY();
	double x3 = p3pos.getX(), y3 = p3pos.getY();
	double M[3][4] = {
		{ x1 * x1, x1 * y1, y1 * y1, -1 },
		{ x2 * x2, x2 * y2, y2 * y2, -1 },
		{ x3 * x3, x3 * y3, y3 * y3, -1 }
	};
	double rhs[3] = { -x1, -x2, -x3 };
	double detM = M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[0][1] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
		M[0][2] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
	if (std::abs(detM) < 1e-6) return;
	double detA = rhs[0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
		M[0][1] * (rhs[1] * M[2][2] - M[1][2] * rhs[2]) +
		M[0][2] * (rhs[1] * M[2][1] - M[1][1] * rhs[2]);

	double detB = M[0][0] * (rhs[1] * M[2][2] - M[1][2] * rhs[2]) -
		rhs[0] * (M[1][0] * M[2][2] - M[1][2] * M[2][0]) +
		M[0][2] * (M[1][0] * rhs[2] - rhs[1] * M[2][0]);

	double detC = M[0][0] * (M[1][1] * rhs[2] - rhs[1] * M[2][1]) -
		M[0][1] * (M[1][0] * rhs[2] - rhs[1] * M[2][0]) +
		rhs[0] * (M[1][0] * M[2][1] - M[1][1] * M[2][0]);
	double A = detA / detM;
	double B = detB / detM;
	double C = detC / detM;
	double D = 0;
	double E = 0;
	double F = -1;
	double centerX = -D / (2 * A);
	double centerY = -E / (2 * C);
	double radiusX = sqrt(fabs(-F / A));
	double radiusY = sqrt(fabs(-F / C));

	// Draw ellipse by iterating through angles
	for (double theta = 0; theta < 2 * M_PI; theta += 0.01) {
		int x = static_cast<int>(centerX + radiusX * cos(theta));
		int y = static_cast<int>(centerY + radiusY * sin(theta));
		renderDrawPoint(renderer, Pos2D(x, y));
	}
	/*renderDrawPoint(renderer, p1pos);
	renderDrawPoint(renderer, p2pos);
	renderDrawPoint(renderer, p3pos);*/
	/*for (int y = -radius; y <= radius; y++) {
		for (int x = -radius; x <= radius; x++) {
			if (x * x + y * y <= radius * radius) {
				renderDrawPoint(renderer, Pos2D(centerX + x, centerY + y));
			}
		}
	}*/
}

Pos2D SDL3DHelper::convert3d2d(Vector3* point, Player* player) {
	float playerx = *player->getPos()->getX();
	float playery = *player->getPos()->getY();
	float playerz = *player->getPos()->getZ();
	float playeryaw = *player->getPos()->getYaw();
	float playerpitch = *player->getPos()->getPitch();
	float playerroll = *player->getPos()->getRoll();
	float cospitch = cos(playerpitch * (M_PI / 180));
	float sinpitch = sin(playerpitch * (M_PI / 180));
	float cosroll = cos(playerroll * (M_PI / 180));
	float sinroll = sin(playerroll * (M_PI / 180));
	float cosyaw = cos(playeryaw * (M_PI / 180));
	float sinyaw = sin(playeryaw * (M_PI / 180));
	float x = point->x - playerx;
	float y = point->y - playery;
	float z = point->z - playerz;

	float tmpx = x;
	x = x * cosyaw - z * sinyaw;
	z = z * cosyaw + tmpx * sinyaw;
	float tmpy = y;
	y = y * cospitch - z * sinpitch;
	z = z * cospitch + tmpy * sinpitch;
	tmpx = x;
	x = x * cosroll - y * sinroll;
	y = y * cosroll + tmpx * sinroll;
	if (z <= 0) {
		z = 0.00001;
	}
	point->x = x * SDL3DHelper::FOCAL_LENGTH / z;
	point->y = y * SDL3DHelper::FOCAL_LENGTH / z;
	point->z = 0;
	return Pos2D(point->x, point->y);
}

FaceStack SDL3DHelper::getFaces(VertexStack3D* vertices) {
	FaceStack stack;
	return stack;
}

Vector3 SDL3DHelper::getIntersection(Vector3 planePoint, Vector3 planeNormal, Vector3 rayPoint, Vector3 rayNormal) {
	float denom = planeNormal.dot(rayNormal);
	if (std::abs(denom) < 1e-6) {
		return Vector3(0, 0, 0);
	}
	float t = planeNormal.dot(planePoint - rayPoint) / denom;
	//std::cout << rayNormal.y << std::endl;
	//std::cout << t << std::endl;
	return rayPoint + rayNormal * t;
}

bool SDL3DHelper::isInside(FaceNode* face, Vector3 point, Model* model, Player* player) {
	float playerx = *player->getPos()->getX();
	float playery = *player->getPos()->getY();
	float playerz = *player->getPos()->getZ();
	float playeryaw = *player->getPos()->getYaw();
	float playerpitch = *player->getPos()->getPitch();
	float playerroll = *player->getPos()->getRoll();
	float cospitch = cos(playerpitch * (M_PI / 180));
	float sinpitch = sin(playerpitch * (M_PI / 180));
	float cosroll = cos(playerroll * (M_PI / 180));
	float sinroll = sin(playerroll * (M_PI / 180));
	float cosyaw = cos(playeryaw * (M_PI / 180));
	float sinyaw = sin(playeryaw * (M_PI / 180));
	int counter = 0;
	Vector3 origin = face->getInfo()->getFront()->getInfo()->getInfo()->getPos()->getAsVector3();
	bool inside = false;
	VertexNode3DNode* prevNode = face->getInfo()->getFront();
	VertexNode3DNode* startNode = prevNode;
	//std::cout << prevNode->faceConnections.size() << std::endl;
	if (prevNode->faceConnections.size() == 0) {
		return false;
	}
	prevNode->faceConnectionsTmp = prevNode->faceConnections;
	VertexNode3DNode* currentNode = prevNode->faceConnectionsTmp[0];
	
	currentNode->faceConnectionsTmp = currentNode->faceConnections;
	


	float x = point.x - playerx;
	float y = point.y - playery;
	float z = point.z - playerz;

	float tmpx = x;
	x = x * cosyaw - z * sinyaw;
	z = z * cosyaw + tmpx * sinyaw;
	float tmpy = y;
	y = y * cospitch - z * sinpitch;
	z = z * cospitch + tmpy * sinpitch;
	tmpx = x;
	x = x * cosroll - y * sinroll;
	y = y * cosroll + tmpx * sinroll;
	if (z <= 0) {
		z = 0.00001;
	}
	point.x = x * SDL3DHelper::FOCAL_LENGTH / z;
	point.y = y * SDL3DHelper::FOCAL_LENGTH / z;




	while (currentNode != startNode) {
		//std::cout << currentNode->faceConnectionsTmp.size() << std::endl;
		if (currentNode->faceConnectionsTmp.size() == 0) {
			currentNode->faceConnectionsTmp = currentNode->faceConnections;
		}
		float x3d = *currentNode->getInfo()->getInfo()->getPos()->getX() + *model->getPos()->getX();
		float z3d = *currentNode->getInfo()->getInfo()->getPos()->getZ() + *model->getPos()->getZ();
		float y3d = *currentNode->getInfo()->getInfo()->getPos()->getY() + *model->getPos()->getY();
		float xp3d = *prevNode->getInfo()->getInfo()->getPos()->getX() + *model->getPos()->getX();
		float zp3d = *prevNode->getInfo()->getInfo()->getPos()->getZ() + *model->getPos()->getZ();
		float yp3d = *prevNode->getInfo()->getInfo()->getPos()->getY() + *model->getPos()->getY();

		float x = x3d - playerx;
		float y = y3d - playery;
		float z = z3d - playerz;

		float tmpx = x;
		x = x * cosyaw - z * sinyaw;
		z = z * cosyaw + tmpx * sinyaw;
		float tmpy = y;
		y = y * cospitch - z * sinpitch;
		z = z * cospitch + tmpy * sinpitch;
		tmpx = x;
		x = x * cosroll - y * sinroll;
		y = y * cosroll + tmpx * sinroll;
		if (z <= 0) {
			z = 0.00001;
		}
		float x2d = x * SDL3DHelper::FOCAL_LENGTH / z;
		float y2d = y * SDL3DHelper::FOCAL_LENGTH / z;

		x = xp3d - playerx;
		y = yp3d - playery;
		z = zp3d - playerz;
		tmpx = x;
		x = x * cosyaw - z * sinyaw;
		z = z * cosyaw + tmpx * sinyaw;
		tmpy = y;
		y = y * cospitch - z * sinpitch;
		z = z * cospitch + tmpy * sinpitch;
		tmpx = x;
		x = x * cosroll - y * sinroll;
		y = y * cosroll + tmpx * sinroll;
		if (z <= 0) {
			z = 0.00001;
		}
		float xp2d = x * SDL3DHelper::FOCAL_LENGTH / z;
		float yp2d = y * SDL3DHelper::FOCAL_LENGTH / z;



		if (std::abs((x2d - xp2d) * (point.y - yp2d) - (y2d - yp2d) * (point.x - xp2d)) < 1e-6) {
			return true;
		}
		//std::cout << "start" << std::endl;
		//std::cout << x << ", " << z << std::endl;
		//std::cout << xp << ", " << zp << std::endl;
		//std::cout << point.x << ", " << point.z << std::endl;
		//std::cout << "end" << std::endl;
		if (((y2d > point.y) != (yp2d > point.y)) && (point.x < (xp2d - x2d) * ((point.y - y2d) / (yp2d - y2d)) + x2d)) {
			inside = !inside;
			
		}
		//counter++;
		VertexNode3DNode* currentNodeTmp = currentNode;
		currentNode = currentNode->faceConnections[0];
		if (currentNode == prevNode) {
			currentNode = currentNodeTmp->faceConnections[1];
		}
		prevNode = currentNodeTmp;
	}
	//std::cout << counter << std::endl;
	return inside;
}

void SDL3DHelper::processLightInformation(SDL_Renderer* renderer, RenderableObject* object, Player* player, Pos* lightPos) {
	Model* model = (Model*)object;
	FaceNode* currentFace = model->getFaces()->getFront();
	int count = 0;
	float playerx = *player->getPos()->getX();
	float playery = *player->getPos()->getY();
	float playerz = *player->getPos()->getZ();
	float playeryaw = *player->getPos()->getYaw();
	float playerpitch = *player->getPos()->getPitch();
	float playerroll = *player->getPos()->getRoll();
	float cospitch = cos(playerpitch * (M_PI / 180));
	float sinpitch = sin(playerpitch * (M_PI / 180));
	float cosroll = cos(playerroll * (M_PI / 180));
	float sinroll = sin(playerroll * (M_PI / 180));
	float cosyaw = cos(playeryaw * (M_PI / 180));
	float sinyaw = sin(playeryaw * (M_PI / 180));
	while (currentFace != nullptr) {
		Vector3 p1 = currentFace->getInfo()->getFront()->getInfo()->getInfo()->getPos()->getAsVector3() + model->getPos()->getAsVector3();
		Vector3 p2 = currentFace->getInfo()->getFront()->getNext()->getInfo()->getInfo()->getPos()->getAsVector3() + model->getPos()->getAsVector3();
		Vector3 p3 = currentFace->getInfo()->getFront()->getNext()->getNext()->getInfo()->getInfo()->getPos()->getAsVector3() + model->getPos()->getAsVector3();
		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		Vector3 normal = v1.cross(v2);
		Vector3 raynormal = lightPos->getNormalizedRotation();
		
		Vector3 intersection = SDL3DHelper::getIntersection(p1, normal, lightPos->getAsVector3(), raynormal);
		if (SDL3DHelper::isInside(currentFace, intersection, model, player)) {
			//std::cout << "Intersection: " << intersection.x << ", " << intersection.y << ", " << intersection.z << std::endl;
			float x = intersection.x - playerx;
			float y = intersection.y - playery;
			float z = intersection.z - playerz;
			//std::cout << "Intersection: " << x << ", " << y << ", " << z << std::endl;
			//std::cout << playery << std::endl;
			float tmpx = x;
			x = x * cosyaw - z * sinyaw;
			z = z * cosyaw + tmpx * sinyaw;
			float tmpy = y;
			y = y * cospitch - z * sinpitch;
			z = z * cospitch + tmpy * sinpitch;
			tmpx = x;
			x = x * cosroll - y * sinroll;
			y = y * cosroll + tmpx * sinroll;
			if (z <= 0) {
				z = 0.00001;
			}
			float x2d = x * SDL3DHelper::FOCAL_LENGTH / z;
			float y2d = y * SDL3DHelper::FOCAL_LENGTH / z;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			float radius = 0.1;
			/*Vector3 intersection2 = intersection + ((Vector3(1, 1, 1) - normal) * radius);
			Vector3 intersection3 = intersection + ((Vector3(1, 1, 1) - normal) * -radius);
			Vector3 intersection4 = intersection + */
			Vector3 arbitrary = std::abs(normal.x < 0.9) ? Vector3(1, 0, 0) : Vector3(0, 1, 0);
			Vector3 u = normal.cross(arbitrary).normalize();
			Vector3 v = normal.cross(u).normalize();
			Vector3 intersection2 = intersection + u * (radius * std::cos(0)) + v * (radius * std::sin(0));
			Vector3 intersection3 = intersection + u * (radius * std::cos(M_PI)) + v * (radius * std::sin(M_PI));
			Vector3 intersection4 = intersection + u * (radius * std::cos(M_PI/2)) + v * (radius * std::sin(M_PI/2));
			//std::cout << intersection2.x << ", " << intersection2.y << ", " << intersection2.z << std::endl;
			//std::cout << intersection3.x << ", " << intersection3.y << ", " << intersection3.z << std::endl;
			//std::cout << intersection4.x << ", " << intersection4.y << ", " << intersection4.z << std::endl;
			SDL3DHelper::renderDrawCircleFill(renderer, x2d, y2d, 4);
			SDL3DHelper::renderFillElipse3DInBounds(renderer, player, intersection2, intersection3, intersection4);
		}
		else {
			//std::cout << "Intersection: " << intersection.x << ", " << intersection.y << ", " << intersection.z << std::endl;
			//std::cout << "Wont render" << std::endl;
		}
		currentFace = currentFace->getNext();
	}
	//while (currentFace != nullptr) {
	//	int n = currentFace->getInfo()->getSize();
	//	if (n < 3) {
	//		currentFace = currentFace->getNext();
	//		continue; // Not a valid polygon
	//	}
	//	count++;
	//	Vector3 edge1 = currentFace->getInfo()->getFront()->getNext()->getInfo()->getInfo()->getPos()->getAsVector3() - currentFace->getInfo()->getFront()->getInfo()->getInfo()->getPos()->getAsVector3();
	//	Vector3 edge2= currentFace->getInfo()->getFront()->getNext()->getNext()->getInfo()->getInfo()->getPos()->getAsVector3() - currentFace->getInfo()->getFront()->getInfo()->getInfo()->getPos()->getAsVector3();
	//	Vector3 normal = edge1.cross(edge2);
	//	Vector3 lightAngleNormal = lightPos->getNormalizedRotation();
	//	float denom = lightAngleNormal.dot(normal);
	//	if (std::abs(denom) < 1e-6f) {
	//		currentFace = currentFace->getNext();
	//		continue; // Ray is parallel to the plane
	//	}
	//	float t = (currentFace->getInfo()->getFront()->getInfo()->getInfo()->getPos()->getAsVector3() - lightPos->getAsVector3()).dot(normal) / denom;
	//	if (t < 0) {
	//		currentFace = currentFace->getNext();
	//		continue; // Intersection is behind the ray
	//	}
	//	Vector3 intersectionPoint = lightPos->getAsVector3() + lightAngleNormal * t;
	//	//std::cout << intersectionPoint.z << std::endl;
	//	//std::cout << n << std::endl;
	//	VertexNode3DNode* vertexNode = currentFace->getInfo()->getFront();
	//	std::vector<VertexNode3DNode*> vertices;
	//	vertices.push_back(vertexNode);
	//	vertexNode = vertexNode->getNext();
	//	int i = 1;
	//	bool anomally = false;
	//	/*auto isPointInPolygon3D = []() {

	//	};*/
	//	//std::cout << intersectionPoint.y << std::endl;
	//	while (vertexNode != nullptr) {
	//		//vertices.push_back(vertexNode);
	//		//Vector3 v0 = vertices[i - 1]->getInfo()->getInfo()->getPos()->getAsVector3();
	//		//Vector3 v1 = vertices[i%n]->getInfo()->getInfo()->getPos()->getAsVector3();
	//		//Vector3 edge = v1 - v0;
	//		//Vector3 toPoint = intersectionPoint - v0;
	//		//Vector3 edgeNormal = edge.cross(normal);
	//		//if (edgeNormal.dot(toPoint) < 0) {
	//		//	//std::cout << edgeNormal.dot(toPoint) << std::endl;
	//		//	//std::cout << edgeNormal.dot(toPoint) << std::endl;
	//		//	anomally = true;
	//		//	i++;
	//		//	break;
	//		//}
	//		//vertexNode = vertexNode->getNext();
	//		//i++;
	//		vertices.push_back(vertexNode);

	//		Vector3 v0 = vertices[i - 1]->getInfo()->getInfo()->getPos()->getAsVector3();
	//		Vector3 v1 = vertices[i % n]->getInfo()->getInfo()->getPos()->getAsVector3();

	//		std::cout << intersectionPoint.y << " : " << v0.y << std::endl;

	//		vertexNode = vertexNode->getNext();
	//		i++;
	//	}
	//	if (anomally) {
	//		
	//		currentFace = currentFace->getNext();
	//		continue;
	//	}
	//	std::cout << "collision!" << std::endl;
	//	//std::cout << "(" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ")" << std::endl;
	//	currentFace = currentFace->getNext();
	//}
	
	//std::cout << count << std::endl;
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



