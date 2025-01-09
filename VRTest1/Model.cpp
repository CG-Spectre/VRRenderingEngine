#include "Model.h"
#include "iostream"
#include <fstream>
#include <vector>
#include "VertexStack.h"
#include "cmath"
#include <chrono>
#include "SDL3DHelper.h"
#include "VertexNode3DNode.h"
#include <algorithm>

void Model::render(SDL_Renderer* renderer, Player* player)
{
    Vertex vertex1(Pos2D(0, 0));
    Vertex vertex2(Pos2D(0, 100));
    Vertex vertex3(Pos2D(100, 0));
    Vertex vertex4(Pos2D(100, 110));
    
    VertexNode vertexNode1(vertex1);
    VertexNode vertexNode2(vertex2);
    VertexNode vertexNode3(vertex3);
    VertexNode vertexNode4(vertex4);

    vertexNode1.getInfo()->addConnection(vertexNode2.getInfo());
    vertexNode1.getInfo()->addConnection(vertexNode3.getInfo());
    vertexNode2.getInfo()->addConnection(vertexNode1.getInfo());
    vertexNode2.getInfo()->addConnection(vertexNode4.getInfo());
    vertexNode3.getInfo()->addConnection(vertexNode1.getInfo());
    vertexNode3.getInfo()->addConnection(vertexNode4.getInfo());
    vertexNode4.getInfo()->addConnection(vertexNode4.getInfo());
    vertexNode4.getInfo()->addConnection(vertexNode4.getInfo());

    VertexStack shape(&vertexNode1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    VertexNode3D* currentNode = data3d.getFront();
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
    while (currentNode != nullptr) {
        float x = *currentNode->getInfo()->getPos()->getX() + *this->pos->getX() - playerx;
        float y = *currentNode->getInfo()->getPos()->getY() + *this->pos->getY() - playery;
        float z = *currentNode->getInfo()->getPos()->getZ() + *this->pos->getZ() - playerz;
        float tmpx = x;
        x = x*cosyaw - z*sinyaw;
        z = z * cosyaw + tmpx * sinyaw;
        float tmpy = y;
        y = y * cospitch - z * sinpitch;
        z = z * cospitch + tmpy * sinpitch;
        tmpx = x;
        x = x * cosroll - y * sinroll;
        y = y * cosroll + tmpx * sinroll;
        currentNode->getInfo()->virtualZ = z;
        if (z <= 0) {
            z = 0.00001;
        }
        float x2d = x * SDL3DHelper::FOCAL_LENGTH / z;
        float y2d = y * SDL3DHelper::FOCAL_LENGTH / z;
        currentNode->getInfo()->getVertex2d()->getPos()->setX((int)x2d);
        currentNode->getInfo()->getVertex2d()->getPos()->setY((int)y2d);
        currentNode = currentNode->getNext();
    }
    //FaceStack facesSorted;
    //FaceNode* currentFace = facesData.getFront();
    //while (currentFace != nullptr) {
    //    FaceNode* currentFaceInner = facesSorted.getFront();
    //    bool sorted = false;
    //    float sum = 0;
    //    int count = 0;
    //    VertexNode3DNode* currentNode = currentFace->getInfo()->getFront();
    //    while (currentNode != nullptr) {
    //        count++;
    //        sum += currentNode->getInfo()->getInfo()->virtualZ;
    //        currentNode = currentNode->getNext();
    //    }
    //    float average = sum / count;
    //    bool abort = false;
    //    while (currentFaceInner != nullptr && !abort) {
    //        sum = 0;
    //        count = 0;
    //        VertexNode3DNode* currentNodeInner = currentFaceInner->getInfo()->getFront();
    //        while (currentNodeInner != nullptr) {
    //            count++;
    //            sum += currentNodeInner->getInfo()->getInfo()->virtualZ;
    //            currentNodeInner = currentNodeInner->getNext();
    //        }
    //        float averageInner = sum / count;
    //        std::cout << (currentFaceInner == nullptr) << std::endl;
    //        if (average < averageInner) {
    //            currentFaceInner->getPrevious()->setNext(currentFace);
    //            currentFaceInner->setPrevious(currentFace);
    //            currentFace->setNext(currentFaceInner);
    //            if (facesSorted.getFront() == currentFaceInner) {
    //                facesSorted.setFront(currentFace);
    //            }
    //            abort = true;
    //            sorted = true;
    //        }
    //        currentFaceInner = currentFaceInner->getNext();
    //    }
    //    //std::cout << sorted << std::endl;
    //    if (!sorted) {
    //        facesSorted.add(currentFace);
    //    }
    //    currentFace = currentFace->getNext();
    //}
    //std::vector<Face2> facesSorted;
    //FaceNode* currentFace = facesData.getFront();
    //while (currentFace != nullptr) {
    //    VertexNode3DNode* innerNode = currentFace->getInfo()->getFront();
    //    int count = 0;
    //    float sum = 0;
    //    while (innerNode != nullptr) {
    //        sum += innerNode->getInfo()->getInfo()->virtualZ;
    //        count++;
    //        innerNode = innerNode->getNext();
    //    }
    //    currentFace->getInfo()->average = sum / count;
    //    currentFace = currentFace->getNext();
    //    facesSorted.push_back(*currentFace->getInfo());
    //}
    //
    //std::sort(facesSorted.begin(), facesSorted.end(), [](const Face2& a, const Face2& b) {
    //    return a.average < b.average; // Sort by descending depth
    //});
    //int counter = 0;
    //int color = false;
    //for (Face2 i : facesSorted) {
    //    if (!color) {
    //        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    //    }
    //    else {
    //        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //    }
    //    color = ~color;
    //    SDL3DHelper::renderFillFace(renderer, *i.getFront());
    //}
    FaceNode* currentNodeRender = facesData.getFront();
    int counter = 0;
    int color = false;
    while (currentNodeRender != nullptr) {
        if (!color) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        color = ~color;
        SDL3DHelper::renderFillFace(renderer, *currentNodeRender->getInfo()->getFront());
        currentNodeRender = currentNodeRender->getNext();
    }
}

Model::Model(const char* objname, Pos* pos, float size, Color* color, const char* modelname) : pos(pos), size(size), color(color), data3d(nullptr)
{
    this->name = objname;
	std::ifstream modelFile("models/" + std::string(modelname) + ".vrobj");
	if (!modelFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}
	std::string line;
    VertexStack3D vertexStack;
    bool fline = false;
    std::vector<std::vector<int>> facest;
	while (std::getline(modelFile, line)) {
        int index = 0;
        float posX = NULL;
        float posY = NULL;
        float posZ = NULL;
        std::vector<std::string> tokens = this->splitString(line, " ");
        std::vector<int> pendingConnections;
        std::vector<int> pendingFaceConnections;
        for (std::string& token : tokens) {
            if (!fline) {
                switch (index) {
                    case 0:
                        if (token == "f") {
                            fline = true;
                            break;
                        }
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
            }
            else {
                pendingFaceConnections.push_back(std::stoi(token));
            }
            
            index++;
        }
        if (!fline) {
            Vertex3D vertex(Pos(posX, posY, posZ));
            for (int index : pendingConnections) {
                vertex.addConnection(index);
            }
            vertexStack.add(new VertexNode3D(vertex));
        }
        else if(pendingFaceConnections.size() != 0){
            facest.push_back(pendingFaceConnections);
        }
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
    FaceStack faces;
    
    for(std::vector<int> k : facest) {
        Face2 face;
        for (int index : k) {
            VertexNode3D* currentNodeInner = data3d.getFront();
            for (int i = 0; i < index; i++) {
                currentNodeInner = currentNodeInner->getNext();
            }
            face.add(new VertexNode3DNode(currentNodeInner));
            face.getLast()->connections = currentNodeInner->getInfo()->connections;
        }
        faces.add(new FaceNode(face));
        VertexNode3DNode* current = face.getFront();
    }

    FaceNode* currentFace = faces.getFront();
    while (currentFace != nullptr) {
        VertexNode3DNode* front = currentFace->getInfo()->getFront();
        while (front != nullptr) {
            for (Vertex3D* i : front->connections) {
                VertexNode3DNode* currentVertexInner = currentFace->getInfo()->getFront();
                while (currentVertexInner != nullptr) {
                    if (currentVertexInner->getInfo()->getInfo() == i) {
                        front->addFaceConnection(currentVertexInner);
                    }
                    currentVertexInner = currentVertexInner->getNext();
                }
            }
            front = front->getNext();
        }
        currentFace = currentFace->getNext();
    }
    facesData = faces;
}

int Model::getObjectType()
{
    return 1;
}

FaceStack* Model::getFaces()
{
    return &facesData;
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
