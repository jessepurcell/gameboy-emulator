#include <SDL3/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    std::cout << "Starting SDL3 Test..." << std::endl;
    
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::cout << "SDL3 Initialized Successfully!" << std::endl;

    SDL_Window* window = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::cout << "Window Created Successfully!" << std::endl;
    SDL_Delay(3000);
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
