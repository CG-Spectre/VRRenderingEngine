#include "Cube.h"
#include <iostream>
#include "Vertex.h"
#include "VertexStack.h"

Cube::Cube(Pos* pos, float size, Color* color) : pos(pos), size(size), color(color) {}

float* Cube::getSize() {
	return &this->size;
}

int Cube::getObjectType() {
	return 2;
}

void Cube::render(SDL_Renderer* renderer, Player* player)
{	
	
	/*
	int size = 200;
	int offset = 200;
	int differencex = 100;
	int differencey = 100;
	SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
	SDL_RenderDrawLine(renderer, offset, offset, offset, offset + size);
	SDL_RenderDrawLine(renderer, offset, offset, offset + size, offset);
	SDL_RenderDrawLine(renderer, offset, offset + size, offset + size, offset + size);
	SDL_RenderDrawLine(renderer, offset + size, offset, offset + size, offset + size);
	
	SDL_RenderDrawLine(renderer, offset + differencex, offset + differencey, offset + differencex, offset + size + differencey);
	SDL_RenderDrawLine(renderer, offset + differencex, offset + differencey, offset + size + differencex, offset + differencey);
	SDL_RenderDrawLine(renderer, offset + differencex, offset + size + differencey, offset + size + differencex, offset + size + differencey);
	SDL_RenderDrawLine(renderer, offset + size + differencex, offset + differencey, offset + size + differencex, offset + size + differencey);

	SDL_RenderDrawLine(renderer, offset, offset, offset + differencex, offset + differencey);
	SDL_RenderDrawLine(renderer, offset, offset + size, offset + differencex, offset + size + differencey);
	SDL_RenderDrawLine(renderer, offset + size, offset + size, offset + size + differencex, offset + size + differencey);
	SDL_RenderDrawLine(renderer, offset + size, offset, offset + size + differencex, offset + differencey);

	this->drawSecondCube(renderer, this->color);*/
	/*SDL_RenderDrawLine(renderer, offset + difference, offset + difference, offset + size + difference, offset + difference);
	SDL_RenderDrawLine(renderer, offset + difference, offset + size + difference, offset + size + difference, offset + size + difference);
	SDL_RenderDrawLine(renderer, offset + size + difference, offset + difference, offset + size + difference, offset + size + difference);*/
	//this->drawSecondCube(renderer, this->color);
}

void Cube::drawSecondCube(SDL_Renderer* renderer, Color* color) {
	/*Vertex vertex1(new Pos2D(500, 500));
	Vertex vertex2(new Pos2D(600, 500));
	Vertex vertex3(new Pos2D(600, 600));
	Vertex vertex4(new Pos2D(500, 600));

	Vertex vertex5(new Pos2D(550, 575));
	Vertex vertex6(new Pos2D(650, 550));
	Vertex vertex7(new Pos2D(650, 650));
	Vertex vertex8(new Pos2D(550, 650));
	
	vertex1.addConnection(&vertex2);
	vertex3.addConnection(&vertex2);
	vertex1.addConnection(&vertex4);
	vertex3.addConnection(&vertex4);

	vertex5.addConnection(&vertex6);
	vertex7.addConnection(&vertex6);
	vertex5.addConnection(&vertex8);
	vertex7.addConnection(&vertex8);

	vertex1.addConnection(&vertex5);
	vertex2.addConnection(&vertex6);
	vertex3.addConnection(&vertex7);
	vertex4.addConnection(&vertex8);

	VertexNode node1(vertex1);
	VertexNode node2(vertex2);
	VertexNode node3(vertex3);
	VertexNode node4(vertex4);
	VertexNode node5(vertex5);
	VertexNode node6(vertex6);
	VertexNode node7(vertex7);
	VertexNode node8(vertex8);

	VertexStack vertexStack(&node1);
	vertexStack.add(&node2);
	vertexStack.add(&node3);
	vertexStack.add(&node4);
	vertexStack.add(&node5);
	vertexStack.add(&node6);
	vertexStack.add(&node7);
	vertexStack.add(&node8);
	SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
	vertexStack.render(renderer);*/
	
	/*
	for (Vertex* i : vertex1.connections) {
		SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
		SDL_RenderDrawLine(renderer, vertex1.pos->getX(), vertex1.pos->getY(), i->pos->getX(), i->pos->getY());
	}
	for (Vertex* i : vertex2.connections) {
		SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
		SDL_RenderDrawLine(renderer, vertex2.pos->getX(), vertex2.pos->getY(), i->pos->getX(), i->pos->getY());
	}
	for (Vertex* i : vertex3.connections) {
		SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
		SDL_RenderDrawLine(renderer, vertex3.pos->getX(), vertex3.pos->getY(), i->pos->getX(), i->pos->getY());
	}
	for (Vertex* i : vertex4.connections) {
		SDL_SetRenderDrawColor(renderer, this->color->r, this->color->g, this->color->b, this->color->a);
		SDL_RenderDrawLine(renderer, vertex4.pos->getX(), vertex4.pos->getY(), i->pos->getX(), i->pos->getY());
	}*/

}
