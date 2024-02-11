#ifndef COLOUR2_H
#define COLOUR2_H

#include <iostream>
#include <cstring>
#include "Vec31.h"


std::string returnPixelColourString(const colour &pixelColour)
{
    std::string str1 = std::to_string(pixelColour.x()) +" "+ std::to_string(pixelColour.y()) +" "+ std::to_string(pixelColour.z());
    return str1;
}

#endif