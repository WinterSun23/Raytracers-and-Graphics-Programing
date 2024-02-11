#ifndef RAY2_H
#define RAY2_H

#include <iostream>
#include <cmath>

#include "Vec31.h"
//#include "Colour2.h" // own Colour2.h has own Vec3.h

class Ray
{   
    public:
        Vec3 startPoint;
        Vec3 rayDirection;
        //point3 hitPoint;
        Ray ()
        {
            startPoint = Vec3(0,0,0);
            rayDirection = Vec3(0,0,0);
        }

        Ray (const Vec3 &start,const Vec3 &dir)
        {
            startPoint = start;
            rayDirection = dir;
        }

        point3 pointAtDist(double t) const
        {
            return point3(startPoint + t*(this->normalizedRay()));
        }

        Vec3 normalizedRay() const
        {
            return unit_vector(rayDirection);
        }
};

#endif