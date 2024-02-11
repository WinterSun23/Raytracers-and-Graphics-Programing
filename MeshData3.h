#ifndef MESHDATA3_H
#define MESHDATA3_H

#include <iostream>
//#include "Vec3.h"
#include "Ray2.h"
#include <array>

bool approximatelyEqual(double a, double b, double epsilon)
{
    return fabs(a - b) <= ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool definitelyLessThan(double a, double b, double epsilon)
{
    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}

inline std::array<Vec3,3> Sphere(Vec3 sphereCentre,double radius,Ray r)
{
    std::array<Vec3,3> hitInfo;
    auto increaseAccuracy =10000.0;
    //auto correctionFactor =0;
    auto c = (sphereCentre - r.startPoint).magnitudeSquared() - radius*radius;
    auto a = r.rayDirection.magnitudeSquared();
    auto b = dot(r.rayDirection,r.startPoint-sphereCentre);
    //using c instead od new variable 'det'
    c = (b*b*increaseAccuracy -a*c*increaseAccuracy);
    c = c*(c>=0) + b*b*increaseAccuracy*(c<0); //making atleast one of t1,t2 as zero so factor becomes zero and also det must be positive
    c = sqrt(c*increaseAccuracy);
    auto t1 = (-b*increaseAccuracy - c)/(a*increaseAccuracy);
    auto t2 = (-b*increaseAccuracy + c)/(a*increaseAccuracy);
    auto f= t1; //'t1' is a random choice only
    //if(c==c)

    //To remove errors
    if(approximatelyEqual(abs(t1),0,0.00000001)) //decide if 10 to the powe of -6 or -5
        t1=0;
    if(approximatelyEqual(abs(t2),0,0.00000001))
        t2=0;
    if(t1>0 && t2>0) //here not equal to zero as we that means we dont want that result. refer det's comment
    {   
        f = t1*(t1<t2) + t2*(t1>t2); // min of t1 and t2
        hitInfo[0] = Vec3(5,0,0);
        hitInfo[2] = (r.pointAtDist(f)*increaseAccuracy - sphereCentre*increaseAccuracy);
        hitInfo[1] = (r.pointAtDist(f)*increaseAccuracy - r.startPoint*increaseAccuracy);//-unit_vector(hitInfo[2])*correctionFactor;

        if(dot(hitInfo[1],hitInfo[2])>0)
        {
            //f = std::max(t1,t2);
            f = t1*(t1>t2) + t2*(t1<t2); //alternative statement
            hitInfo[2] = (r.pointAtDist(f)*increaseAccuracy - sphereCentre*increaseAccuracy);
            hitInfo[1] = (r.pointAtDist(f)*increaseAccuracy - r.startPoint*increaseAccuracy);//-unit_vector(hitInfo[2])*correctionFactor;

            if(dot(hitInfo[1],hitInfo[2])>0)
                hitInfo[0] = Vec3(0,0,0);
        }

    }
    else
    {
        if(t1*t2 <0)
        {
            f = t1*(t1>t2) + t2*(t1<t2);
            hitInfo[0] = Vec3(5,0,0);
            hitInfo[2] = (r.pointAtDist(f)*increaseAccuracy - sphereCentre*increaseAccuracy);
            hitInfo[1] = (r.pointAtDist(f)*increaseAccuracy - r.startPoint*increaseAccuracy);//-unit_vector(hitInfo[2])*correctionFactor;
            
            if(dot(hitInfo[1],hitInfo[2])>0)
                hitInfo[0] = Vec3(0,0,0);
            
        }
        else
        {
            hitInfo[0] = Vec3(0,0,0);
        }
    }
    hitInfo[2]/=increaseAccuracy; //<- this can be skipped as only magnitude is affected not direction
    hitInfo[1]/=increaseAccuracy; //<- this cannot be skipped as we add r.startPos in world.h
    //hitInfo[0].x() tells if it hit or not
    return hitInfo;
}

#endif