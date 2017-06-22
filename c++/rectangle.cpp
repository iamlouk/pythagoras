//
//  rectangle.cpp
//  SDLHalloWelt
//
//  Created by Lou Knauer on 02.10.16.
//  Copyright © 2016 Lou Knauer. All rights reserved.
//

#include "rectangle.hpp"
#include "vector.hpp"
#include <SDL.h>


Rectangle::Rectangle(Vector _A, Vector _vec1, Vector _vec2, double shift) {
    A = _A;
    vec1 = _vec1;
    vec2 = _vec2;

    B = Vector(A.x + vec1.x, A.y + vec1.y);

    C = Vector(B.x + vec2.x, B.y + vec2.y);

    D = Vector(A.x + vec2.x, A.y + vec2.y);

    recalcP(shift);
}

void Rectangle::recalcP(double shift) {
    P = Vector(B.x + (vec2.x / 2), B.y + (vec2.y / 2));

    double s = SDL_sin(shift);
    double c = SDL_cos(shift);
    double x = vec1.x / 2;
    double y = vec1.y / 2;

    P.x += (x * c) - (y * s);
    P.y += (x * s) + (y * c);
}

void Rectangle::drawRect(SDL_Renderer * renderer) {
    SDL_RenderDrawLine(renderer, A.x, A.y, B.x, B.y);
    SDL_RenderDrawLine(renderer, C.x, C.y, D.x, D.y);
    SDL_RenderDrawLine(renderer, B.x, B.y, C.x, C.y);
    SDL_RenderDrawLine(renderer, D.x, D.y, A.x, A.y);
}

Rectangle Rectangle::nextRectLeft(double shift) {
    Vector vec1 = Vector(P.x - C.x, P.y - C.y);
    Vector vec2 = Vector(P.x - B.x, P.y - B.y);

    vec1.toLength( vec2.length() );
    // vec1.toLength( vec2.length() * random(0.75, 1.25));

    return Rectangle(this->B, vec1, vec2, shift);
}

Rectangle Rectangle::nextRectRight(double shift) {
    Vector vec1 = Vector(P.x - B.x, P.y - B.y);
    Vector vec2 = Vector(C.x - P.x, C.y - P.y);

    vec1.toLength( vec2.length() );
    // vec1.toLength( vec2.length() * random(0.75, 1.25));

    return Rectangle(this->P, vec1, vec2, shift);
}
