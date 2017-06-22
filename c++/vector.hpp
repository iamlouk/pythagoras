//
//  vector.hpp
//  SDLHalloWelt
//
//  Created by Lou Knauer on 02.10.16.
//  Copyright © 2016 Lou Knauer. All rights reserved.
//

#ifndef vector_hpp
#define vector_hpp

class Vector {
public:
    double x;
    double y;
    
    Vector(double _x, double _y);
    
    Vector(void);
        
    void multiply(double factor);
    
    double length(void);
    
    void toLength(double len);
    
    void rotate(double angle);
    
    Vector rotated(double angle);
};

#endif /* vector_hpp */
