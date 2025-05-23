#include <SDL.h>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <iostream>
#include <cstring>
#include <string>
#include "Player.h"
#include "RenderableObject.h"
#include "Cube.h"
#include "Sky.h"
#include <vector>
#include "Color.h"
#include "RenderNode.h"
#include "RenderStack.h"
#include "Model.h"
#include "SDL3DHelper.h"
#include "LightRaySource.h";
#include <cmath>
#include <chrono>

int main(int argc, char* argv[]) {
    
    Pos pos(0.0f, 0, 0, 0, 0, 0);
    const char* playerName = "Spectre";
    Player player(&pos, playerName);
    Color skyColor(0, 0, 0, 255);
    Sky sky(&skyColor);
    RenderNode skyNode(&sky);
    Pos cubePos(0, -0.5, 5, 0, 0, 0);
    Pos planePos(0, 0, 7, 0, 0, 0);
    Color cubeColor(255, 255, 255, 255);
    Cube cube(&cubePos, 1, &cubeColor);
    RenderNode cubenode(&cube);
    RenderStack renderStack(&skyNode);
    Model planeModel = Model("plane", & planePos, 2, &cubeColor, "plane");
    //Model cubeModel = Model("triangularPrism", &cubePos, 2, &cubeColor, "cube");
    //RenderNode modelnode(&cubeModel);
    RenderNode modelnode2(&planeModel);
   // LightRaySource light(Pos(1, 7, 7.5, 0, 90, 0));
    
    LightRaySource light2(Pos(0.5, 7, 6.5, 0, 90, 0));
    LightRaySource light3(Pos(0.5, 7, 8.5, 0, 90, 0));
    LightRaySource light4(Pos(0.5, 7, 7.5, 0, 90, 0));
    LightRaySource light5(Pos(-0.5, 7, 7.5, 0, 90, 2));
    LightRaySource light6(Pos(1.5, 7, 7.5, 0, 90, -2));
    //LightRaySource light3(Pos(1, 7, 7.5, 0, 80, 0));
    
    ///renderStack.add(&modelnode);
    renderStack.add(&modelnode2);
    //renderStack.add(new RenderNode(&light));
    renderStack.add(new RenderNode(&light2));
    renderStack.add(new RenderNode(&light3));
    renderStack.add(new RenderNode(&light4));
    renderStack.add(new RenderNode(&light5));
    renderStack.add(new RenderNode(&light6));
    
    //renderStack.add(new RenderNode(&light3));
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }
    int targetDisplay = 1;
    SDL_Rect displayBounds;
    if (SDL_GetDisplayBounds(targetDisplay, &displayBounds) != 0) {
        std::cerr << "Failed to get display bounds: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Pixel Drawing",            // Window title
        displayBounds.x + 100,     // x position
        displayBounds.y + 100,     // y position
        800,                        // Width
        600,                        // Height
        SDL_WINDOW_SHOWN            // Flags
    );

    if (!window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    bool fullScreen = true;
    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
        std::cerr << "SDL Fullscreen Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set up random number generation
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    SDL_GetWindowSize(window, &SDL3DHelper::SCREEN_WIDTH, &SDL3DHelper::SCREEN_HEIGHT);
    // Main loop
    bool running = true;
    SDL_Event event;
    float movement = 0.01;
    int time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    while (running) {
        int dt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - time;
        time += dt;
        float diff = 9;
        //light2.getPos()->setPitch(90 + (std::sin((float)time/1000) + 1) * (diff / 2));
        //light2.getPos()->setRoll((std::sin((float)time / 1000)) * (diff / 2));
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                SDL_Keycode key = event.key.keysym.sym;
                const char* keyName = SDL_GetKeyName(key);
                if (strcmp(keyName, "F11") == 0) {
                    std::cout << "User toggled fullscreen" << std::endl;
                    fullScreen = !fullScreen;
                    if (fullScreen) {
                        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0) {
                            std::cerr << "SDL Screenchange Error: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 1;
                        }
                    }
                    else {
                        if (SDL_SetWindowFullscreen(window, SDL_WINDOW_RESIZABLE) != 0) {
                            std::cerr << "SDL Screenchange Error: " << SDL_GetError() << std::endl;
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 1;
                        }
                    }
                }
                
            }
        }
        const Uint8* state = SDL_GetKeyboardState(NULL);
        float dx = 0;
        float dz = 0;
        if (state[SDL_SCANCODE_W]) {
            dx += movement * sin(*player.getPos()->getYaw() * (M_PI / 180.0));
            dz += movement * cos(*player.getPos()->getYaw() * (M_PI / 180.0));
        }
        if (state[SDL_SCANCODE_A]) {
            dx -= movement * cos(-*player.getPos()->getYaw() * (M_PI / 180.0));
            dz -= movement * sin(-*player.getPos()->getYaw() * (M_PI / 180.0));
        }
        if (state[SDL_SCANCODE_S]) {
            dx -= movement * sin(*player.getPos()->getYaw() * (M_PI / 180.0));
            dz -= movement * cos(*player.getPos()->getYaw() * (M_PI / 180.0));

        }
        if (state[SDL_SCANCODE_D]) {
            dx += movement * cos(-*player.getPos()->getYaw() * (M_PI / 180.0));
            dz += movement * sin(-*player.getPos()->getYaw() * (M_PI / 180.0));

        }
        player.getPos()->setX(*player.getPos()->getX() + dx*dt);
        player.getPos()->setZ(*player.getPos()->getZ() + dz*dt);
        if (state[SDL_SCANCODE_LEFT]) {
            player.getPos()->setYaw(*player.getPos()->getYaw() - movement*12*dt);
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            player.getPos()->setYaw(*player.getPos()->getYaw() + movement*12*dt);
        }
        if (state[SDL_SCANCODE_UP]) {
            player.getPos()->setPitch(*player.getPos()->getPitch() + movement * 12 * dt);
        }
        if (state[SDL_SCANCODE_DOWN]) {
            player.getPos()->setPitch(*player.getPos()->getPitch() - movement * 12 * dt);
        }
        if (state[SDL_SCANCODE_1]) {
            player.getPos()->setRoll(*player.getPos()->getRoll() - movement * 12 * dt);
        }
        if (state[SDL_SCANCODE_2]) {
            player.getPos()->setRoll(*player.getPos()->getRoll() + movement * 12 * dt);
        }

        if (state[SDL_SCANCODE_SPACE]) {
            player.getPos()->setY(*player.getPos()->getY() + movement*dt);
        }
        if (state[SDL_SCANCODE_LSHIFT]) {
            player.getPos()->setY(*player.getPos()->getY() - movement * dt);
        }
        //std::cout << "(" << *player.getPos()->getX() << ", " << *player.getPos()->getY() << ", " << *player.getPos()->getZ() << ")" << std::endl;
        /*float dx = 0;
                float dz = 0;
                if (strcmp(keyName, "W") == 0) {
                    dx += movement * sin(*player.getPos()->getYaw() * (M_PI/180.0));
                    dz += movement * cos(*player.getPos()->getYaw() * (M_PI / 180.0));
                }
                if (strcmp(keyName, "A") == 0) {
                    dx -= movement * cos(-*player.getPos()->getYaw() * (M_PI / 180.0));
                    dz -= movement * sin(-*player.getPos()->getYaw() * (M_PI / 180.0));
                }
                if (strcmp(keyName, "S") == 0) {
                    dx -= movement * sin(*player.getPos()->getYaw() * (M_PI / 180.0));
                    dz -= movement * cos(*player.getPos()->getYaw() * (M_PI / 180.0));
                    
                }
                if (strcmp(keyName, "D") == 0) {
                    dx += movement * cos(-*player.getPos()->getYaw() * (M_PI / 180.0));
                    dz += movement * sin(-*player.getPos()->getYaw() * (M_PI / 180.0));
                    
                }

                player.getPos()->setX(*player.getPos()->getX() + dx);
                player.getPos()->setZ(*player.getPos()->getZ() + dz);

                if (strcmp(keyName, "Left") == 0) {
                    player.getPos()->setYaw(*player.getPos()->getYaw() - 1);
                }
                if (strcmp(keyName, "Right") == 0) {
                    player.getPos()->setYaw(*player.getPos()->getYaw() + 1);
                }

                if (strcmp(keyName, "Space") == 0) {
                    if()
                    player.getPos()->setYaw(*player.getPos()->getYaw() - 1);
                }

                std::cout << *player.getPos()->getYaw() << std::endl;*/
        SDL_GetWindowSize(window, &SDL3DHelper::SCREEN_WIDTH, &SDL3DHelper::SCREEN_HEIGHT);
        RenderNode* currentNode = renderStack.getFront();
        bool isNext = true;
        while (isNext) {
            if (currentNode->getInfo()->getObjectType() == 2) {
                ((LightRaySource*)currentNode->getInfo())->render(renderer, &player, &renderStack);
            }
            else {
                //std::cout << "rendering" << std::endl;
                currentNode->getInfo()->render(renderer, &player);
            }
            if (currentNode->getLink() == nullptr) {
                isNext = false;
                continue;
            }
            currentNode = currentNode->getLink();
        }
        // Present the renderer
        SDL_RenderPresent(renderer);
        //cubePos.setZ(*cubePos.getZ() + 0.05);
        //cubePos.setY(*cubePos.getY() + 0.025);
        //cubePos.setX(*cubePos.getX() + 0.025);
        // Delay for a short period
        SDL_Delay(SDL3DHelper::SDL_DELAY); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}