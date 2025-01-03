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

int main(int argc, char* argv[]) {
    Pos pos(0, 0, 0, 0, 0, 0);
    const char* playerName = "Spectre";
    Player player(&pos, playerName);
    Color skyColor(0, 0, 0, 255);
    Sky sky(&skyColor);
    RenderNode skyNode(&sky);
    Pos cubePos(0, 0, 0, 0, 0, 0);
    Color cubeColor(255, 255, 255, 255);
    Cube cube(&cubePos, 2, &cubeColor);
    RenderNode cubenode(&cube);
    RenderStack renderStack(&skyNode);
    Model cubeModel = Model(&cubePos, 2, &cubeColor, "prism");
    RenderNode modelnode(&cubeModel);
    renderStack.add(&modelnode);
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

    // Main loop
    bool running = true;
    SDL_Event event;
    while (running) {
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
        RenderNode* currentNode = renderStack.getFront();
        bool isNext = true;
        while (isNext) {
            currentNode->getInfo()->render(renderer, &player);
            if (currentNode->getLink() == nullptr) {
                isNext = false;
                continue;
            }
            currentNode = currentNode->getLink();
        }
        // Present the renderer
        SDL_RenderPresent(renderer);

        // Delay for a short period
        SDL_Delay(16); // ~60 FPS
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}