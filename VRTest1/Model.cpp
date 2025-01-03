#include "Model.h"
#include "iostream"
#include <fstream>
#include <vector>
#include "VertexStack.h"
#include "cmath"

float multiplier = 0;
float timer = 0;
float end = 100;

void Model::render(SDL_Renderer* renderer, Player* player)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    VertexNode3D* currentNode = data3d.getFront();
    while (currentNode != nullptr) {
        currentNode->getInfo()->getVertex2d()->getPos()->setX((int)(*currentNode->getInfo()->getPos()->getX() * 100) + (int)(*currentNode->getInfo()->getPos()->getZ()*multiplier));
        currentNode->getInfo()->getVertex2d()->getPos()->setY((int)(*currentNode->getInfo()->getPos()->getY() * 100) + (int)(*currentNode->getInfo()->getPos()->getZ() * multiplier));
        currentNode = currentNode->getNext();
    }

    currentNode = data3d.getFront();
    while (currentNode != nullptr) {
        for (Vertex3D* i : currentNode->getInfo()->connections) {
            SDL_RenderDrawLine(renderer, currentNode->getInfo()->getVertex2d()->getPos()->getX(), currentNode->getInfo()->getVertex2d()->getPos()->getY(), i->getVertex2d()->getPos()->getX(), i->getVertex2d()->getPos()->getY());
        }
        std::cout << currentNode->getInfo()->getVertex2d()->getPos()->getX() << ", " << currentNode->getInfo()->getVertex2d()->getPos()->getY() << std::endl;
        currentNode = currentNode->getNext();
    }
    //data3d->render(renderer);
	//std::cout << "Rendering model." << std::endl;
    multiplier += 3*sin((timer/end)*M_PI*2);
    timer++;
}

Model::Model(Pos* pos, float size, Color* color, const char* modelname) : pos(pos), size(size), color(color), data3d(nullptr)
{
	std::ifstream modelFile("models/" + std::string(modelname) + ".vrobj");
	if (!modelFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	std::string line;
    VertexStack3D vertexStack;
	while (std::getline(modelFile, line)) {
        int index = 0;
        float posX = NULL;
        float posY = NULL;
        float posZ = NULL;
        std::vector<std::string> tokens = this->splitString(line, " ");
        std::vector<int> pendingConnections;
        for (std::string& token : tokens) {
            switch (index) {
                case 0:
                    posX = std::stof(token);
                    break;
                case 1:
                    posY = std::stof(token);
                    break;
                case 2:
                    posZ = std::stof(token);
                    break;
                default:
                    pendingConnections.push_back(std::stoi(token));
                    break;
            }
            index++;
        }
        Vertex3D vertex(Pos(posX, posY, posZ, true));
        for (int index : pendingConnections) {
            vertex.addConnection(index);
        }
        vertexStack.add(new VertexNode3D(vertex));
	}
	modelFile.close();
    VertexNode3D* currentNode = vertexStack.getFront();
    while (currentNode != nullptr) {
        for (int index : currentNode->getInfo()->pendingConnections) {
            VertexNode3D* currentNodeInner = vertexStack.getFront();
            for (int i = 0; i < index; i++) {
                currentNodeInner = currentNodeInner->getNext();
            }
            currentNode->getInfo()->addConnection(currentNodeInner->getInfo());
        }
        currentNode = currentNode->getNext();
    }
    data3d = vertexStack;
}

std::vector<std::string> Model::splitString(const std::string& str, const char* delimiter) {
    std::vector<std::string> result;
    std::string token;
    for (const char ch : str) {
        if (ch == *delimiter) {
            if (!token.empty()) {
                result.push_back(token);
            }
            token.clear();
        }
        else {
            token += ch;
        }
    }
    if (!token.empty()) {
        result.push_back(token);
    }
    return result;
}
