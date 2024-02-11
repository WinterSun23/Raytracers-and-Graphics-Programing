#ifndef MATERIAL4_H
#define MATERIA4_H

#include <iostream>
#include <vector>
#include "Ray2.h"

class Material
{
    public:
        colour matCol;
        Vec3 lightInteraction; // (reflectance,absorptance,transmittance)
        Vec3 reflectance; // (specular,diffuse,empty...)

};


#endif