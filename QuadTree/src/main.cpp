




#include <SDL.h>
#include <vector>
#include <memory>
#include <iostream>
#include "QuadTree.h"




int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << "\n";
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Quadtree Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    

    bool running = true;
    SDL_Event event;

    int x = 0;
    int y = 0;
    int w = 800;
    int h = 800;

    SDL_Rect r = { x,y,w,h };
    

    Rectangle box(x, y, w, h);
    QuadTree quadTree(box, 4);

    int pointx = 100;
    int pointy = 100;

    while (running) {
        while (SDL_PollEvent(&event)) {

            int mx, my;
            SDL_GetMouseState(&mx, &my);
            //printf("%d , %d", mx, my);
            const Uint8* state = SDL_GetKeyboardState(NULL);
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Point* p = new Point(mx, my);
                quadTree.insert(p);
                break;
               
            }

            if (state[SDL_SCANCODE_0])
            {
                quadTree.deleteLast(2);
            }
            if (state[SDL_SCANCODE_1])
            {
                quadTree.deleteLast(5);
            }
        }
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        quadTree.render(renderer);
        
        SDL_RenderPresent(renderer);
    }
        
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
