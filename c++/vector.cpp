//
//  vector.cpp
//  SDLHalloWelt
//
//  Created by Lou Knauer on 02.10.16.
//  Copyright © 2016 Lou Knauer. All rights reserved.
//

#include "vector.hpp"
#include <SDL2/SDL.h>

Vector::Vector(double _x, double _y) {
    x = _x;
    y = _y;
}

Vector::Vector(void) {
    x = 0;
    y = 0;
}

void Vector::multiply(double factor) {
    x *= factor;
    y *= factor;
}

double Vector::length(void) {
    return SDL_sqrt((x * x) + (y * y));
}

void Vector::toLength(double len) {
    double cl = length();
    x = (x / cl) * len;
    y = (y / cl) * len;
}

void Vector::rotate(double angle) {
    double s = SDL_sin(angle);
    double c = SDL_cos(angle);

    double _x = (x * c) - (y * s);
    double _y = (x * s) + (y * c);

    x = _x;
    y = _y;
}

Vector Vector::rotated(double angle) {
    double s = SDL_sin(angle);
    double c = SDL_cos(angle);

    double _x = (x * c) - (y * s);
    double _y = (x * s) + (y * c);

    return Vector(_x, _y);
}
