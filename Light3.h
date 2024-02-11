#ifndef LIGHT3_H
#define LIGHT3_H

#include "Vec31.h"
  
class Light
{
    public:
        point3 lightPosition;
        std::string lightName;
        double radius;
        colour emission;

        Light ()
        {
            lightName = "Light1";
            lightPosition = Vec3(0,4,-550);
            radius = 250;
            emission = colour(255,255,255);
        }
        
};


#endif