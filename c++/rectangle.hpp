//
//  rectangle.hpp
//  SDLHalloWelt
//
//  Created by Lou Knauer on 02.10.16.
//  Copyright © 2016 Lou Knauer. All rights reserved.
//

#ifndef rectangle_hpp
#define rectangle_hpp

#include "vector.hpp"
#include "SDL2/SDL.h"

class Rectangle {
protected:
    Vector A; // Untere linke ecke
    Vector B; // Obere linke ecke
    Vector C; // Obere rechte ecke
    Vector D; // Untere rechte ecke
    
    Vector vec1; // Von A zu B (Nach "oben")
    Vector vec2; // Von A zu D (Nach "rechts")
    
    Vector P; // Die "Dachspitze"
    
public:
    Rectangle(Vector _A, Vector _vec1, Vector _vec2, double shift);
    
    void recalcP(double shift);
    
    void drawRect(SDL_Renderer * renderer);
        
    Rectangle nextRectLeft(double shift);
    
    Rectangle nextRectRight(double shift);
};

#endif /* rectangle_hpp */
