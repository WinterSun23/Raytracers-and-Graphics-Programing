#ifndef WORLD5_H
#define WORLD5_H 

#include <iostream>
#include <vector>
#include "Camera3.h" // - has vec3 and ray
#include "Object4.h"
#include "Light3.h"
class World
{
    public:
        std::string worldName = "";
        colour backGroundColour = Vec3(255,255,255);
        Camera cam;
        std::vector<Object> objectList;
        std::vector<Light> lightList;

        std::vector<Ray> childRays;
        //std::vector<Ray> *childRaysPointer = &childRays;

        //Maybe for default world name - add counter and name them world 1,2,etc...
        void addObject(Object o)
        {
            objectList.push_back(o);
        }
        void addLight(Light l)
        {
            lightList.push_back(l);
        }

        bool definitelyLessThan(double a, double b, double epsilon)
        {
            return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
        }
        
        colour returnRayColour(std::vector<Ray> rayList,int maxReflections)
        {
            colour finalColour;
            int hitTimes =0;
            std::array<Vec3,3> hitInfo;
            std::array<Vec3,3> bestHitInfo;
            double t = __DBL_MAX__;
            Object ideal;
            Light idealLight;
            int got = -1;  

                for (Ray r:rayList)
                {
                    got=-1;
                    t = __DBL_MAX__;
                     
                    for(Light x:lightList)
                    {
                        hitInfo = Sphere(x.lightPosition,x.radius,r);
                        if(hitInfo[0].x()>0.1 && definitelyLessThan(hitInfo[1].magnitudeSquared(),t,0.000001)) //here we have only hitPoint[1] as it already is a ray from the start pos to the hit point
                        {
                            idealLight = x;
                            t=hitInfo[1].magnitudeSquared();
                            got = 0;
                        }
                    }
                    for(Object x:objectList)
                    {
                        hitInfo = Sphere(x.objectPosition,x.radius,r);
                        if(hitInfo[0].x()>0.1 && definitelyLessThan(hitInfo[1].magnitudeSquared(),t,0.000001))
                        {
                            ideal =x;
                            t=hitInfo[1].magnitudeSquared();
                            bestHitInfo = hitInfo;
                            got = 1;                 
                        }
                    }
                    if(got==0)
                    {
                        if(maxReflections>=0)
                        {
                            finalColour += idealLight.emission;
                            hitTimes+=1;
                        }
                        //if(maxReflections!=10)
                            //std::cout<<'l';
                    }
                    else if(got==1)
                    {
                        if(maxReflections>=1)
                        {
                            childRays = ideal.BRDF(r,bestHitInfo[1]+r.startPoint,bestHitInfo[2],sqrt(r.rayDirection.magnitudeSquared()));
                            //colour temp = unit_vector(ideal.objectColour); 
                            colour temp = returnRayColour(childRays,maxReflections-1)*(ideal.mat.lightInteraction.e[0]); 
                            //temp = unit_vector(temp*ideal.objectColour)*sqrt(temp.magnitudeSquared());
                            temp=temp*ideal.objectColour;
                            finalColour+=temp;//*unit_vector(ideal.objectColour);
                            hitTimes+=1;
                        }
                        if(maxReflections==0)
                        {
                            finalColour+=Vec3(0,0,0);//*unit_vector(ideal.objectColour);
                            hitTimes+=1;
                        }
                        //finalColour += returnRayColour(childRays,maxReflections-1)*(ideal.mat.lightInteraction.e[0])*temp;//sqrt(r.rayDirection.magnitudeSquared());  
                    }
                    /*
                    else
                    {  
                        if(maxReflections>=0)
                        {
                            finalColour+=backGroundColour;
                            hitTimes+=1;
                        }
                    }
                    */
                }
                if(hitTimes>0)
                    return finalColour*(double(1)/hitTimes);
                else   
                    return backGroundColour;
        }
        
};
#endif