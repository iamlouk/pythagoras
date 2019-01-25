#include <iostream>
#include <time.h>
#include <SDL.h>

#include "rectangle.hpp"
#include "vector.hpp"

//>---<>---<>---<//

double random(double min, double max) {
    double x = (double) rand() / RAND_MAX;
    return min + (x * (max - min));
}

//>---<>---<>---<//
//> Globals:

const int WIDTH = 1500;
const int HEIGHT = 1000;

const int TREE_DEPTH = 15;
const int ticksPerFrame = 1000 / 30;

SDL_Window * window = nullptr;
SDL_Surface * surface = nullptr;
SDL_Renderer * renderer = nullptr;

double shift = 0.0;

//>---<>---<>---<//
//> Methods to draw something:

void drawBDP(Rectangle * prevRect, int counter) {
    Rectangle left = prevRect->nextRectLeft(shift);
    Rectangle right = prevRect->nextRectRight(shift);

    left.drawRect(renderer);
    right.drawRect(renderer);

    if (counter > 0) {
        drawBDP(&left, counter - 1);
        drawBDP(&right, counter - 1);
    }
}

void drawCircle(Vector center, int radius, int accuracy) {
    Vector start_vec = Vector(0, radius);

    double prevX = center.x + start_vec.x;
    double prevY = center.y + start_vec.y;

    double step = (M_PI * 2) / accuracy;
    double angle = 0;

    while (angle < M_PI * 2) {
        angle += step;

        Vector vec = start_vec.rotated(angle);

        double x = center.x + vec.x;
        double y = center.y + vec.y;

        SDL_RenderDrawLine(renderer, prevX, prevY, x, y);

        prevX = x;
        prevY = y;
    }
}

void drawSpecialCircle(Vector center, double shift) {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

    Vector vec1 = Vector(0, 100);
    Vector vec2 = Vector(0, 1000 * shift);
    Vector vec3 = Vector(0, 10);

    double prevX = center.x + vec1.x + vec2.x + vec3.x;
    double prevY = center.y + vec1.y + vec2.y + vec3.y;

    double step = (M_PI * 2) / 1000;
    double angle = 0;

    while (angle < M_PI * 2) {
        angle += step;

        vec1.rotate(step);
        vec2.rotate(step * 6);
        vec3.rotate(step * 12);

        double x = center.x + vec1.x + vec2.x + vec3.x;
        double y = center.y + vec1.y + vec2.y + vec3.y;

        SDL_RenderDrawLine(renderer, prevX, prevY, x, y);

        prevX = x;
        prevY = y;
    }
}

//>---<>---<>---<//
//> Helper:

void clear() {
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderClear( renderer );
}

void render() {
    //Update screen
    SDL_RenderPresent( renderer );
}

void cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//>---<>---<>---<//
//> Main:

int animateBaumDesPythagoras(void) {
    SDL_Event evt;
    unsigned int i = 0;
    unsigned int averageTicksPerFrame = 0;

    const int RECT_WIDTH = WIDTH * 0.15;

    Rectangle firstRect(Vector((WIDTH / 2) - (RECT_WIDTH / 2), HEIGHT), Vector(0, -RECT_WIDTH), Vector(RECT_WIDTH, 0), shift);

    while (true) {
        Uint32 ticks = SDL_GetTicks();

        clear();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        firstRect.drawRect(renderer);
        drawBDP(&firstRect, TREE_DEPTH);

        render();

        while (SDL_PollEvent(&evt)) {
            if ((evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) || (evt.type == SDL_QUIT)) {
                cleanUp();
                return 0;
            }
        }

        firstRect.recalcP(shift);

        i += 1;
        shift = SDL_sin(((double) i) * 0.01) * 0.1;

        if (i % 100 == 0) {
            std::cout << "FPS: " << (1000 / averageTicksPerFrame) << std::endl;
            averageTicksPerFrame = 0;
        }

        ticks = SDL_GetTicks() - ticks;

        int correction = ticksPerFrame - ticks;
        if (correction > 0) {
            ticks += correction;
            SDL_Delay(correction);
        }

        averageTicksPerFrame = (averageTicksPerFrame + ticks) / 2;
    }
}

int drawBaumDesPythagoras(void) {
    shift = 0.075;

    const int RECT_WIDTH = WIDTH * 0.15;

    Rectangle firstRect(Vector((WIDTH / 2) - (RECT_WIDTH / 2), HEIGHT), Vector(0, -RECT_WIDTH), Vector(RECT_WIDTH, 0), shift);

    clear();

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    firstRect.drawRect(renderer);
    drawBDP(&firstRect, TREE_DEPTH);

    render();

    SDL_Event evt;
    while (SDL_WaitEvent(&evt)) {
        if ((evt.type == SDL_KEYDOWN && evt.key.keysym.sym == SDLK_ESCAPE) || (evt.type == SDL_QUIT)) {
            cleanUp();
            return 0;
        }
    }

    return 1;
}

int main(int argc, const char * argv[]) {
    for (int i = 1; i < argc; i++)
        std::cout << "argv[ " << i << " ] = " << argv[i] << std::endl;

    // Make rand() Random!
    srand( (SDL_sin(time(nullptr)) + 1) * 100 );

    // Start SDL
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
    }

    window = SDL_CreateWindow("C++ SDL: Ein Baum des Pythagoras!", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    surface = SDL_GetWindowSurface(window);
    if (surface == nullptr) {
        std::cerr << "SDL_GetWindowSurface failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    renderer = SDL_GetRenderer(window);
    if (renderer == nullptr) {
        std::cerr << "SDL_GetRenderer failed: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // return animateBaumDesPythagoras();
    return drawBaumDesPythagoras();
}

//>---<>---<>---<//
