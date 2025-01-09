#include "LightRaySource.h"
#include "SDL3DHelper.h"
#include <iostream>

LightRaySource::LightRaySource(Pos pos) : pos(pos)
{
    this->name = "directionalLightRaySource";
} 

int LightRaySource::getObjectType()
{
    return 2;
}

void LightRaySource::render(SDL_Renderer* renderer, Player* player, RenderStack* renderStack)
{
    RenderNode* currentNode = renderStack->getFront();
    while (currentNode != nullptr) {
        bool skip = false;
        for (int i : renderBlackList) {
            if (i == currentNode->getInfo()->getObjectType()) {
                skip = true;
                break;
            }
        }
        if (skip) {
            currentNode = currentNode->getLink();
            continue;
        }
        SDL3DHelper::processLightInformation(renderer, currentNode->getInfo(), player, &this->pos);
        //std::cout << currentNode->getInfo() << std::endl;
        currentNode = currentNode->getLink();
    }
}
