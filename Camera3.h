#ifndef CAMERA3_H
#define CAMERA3_H

#include<iostream>
#include <cmath>

#include "Colour2.h"
#include "Ray2.h" //as Ray.h includes ownVec3.h

Vec3 worldUp = unit_vector(Vec3(0,1,0));

class Camera
{
    public:
        //CAMERA
        point3 cameraPosition;
        Ray forwardDirection;
        Ray upDirection; //with respect to camera's forward
        Ray rightDirection;  //with respect to camera's forward

        //IMAGE
        const float aspectRatio = 16.0/9.0;
        const int imageHeight = 400;
        const int imageWidth = static_cast<int>(imageHeight*aspectRatio);
        const int viewPortHeight = 2;
        const int viewPortWidth = static_cast<int>(aspectRatio*viewPortHeight);

        //LENS
        double focalLength =1.0;
        float lensRadius = 1.0;

        //APERTURE 
        float apertureRadius =5.0;

        
        point3 focalPlaneCentre;
        point3 upperLeftPos;
         
        Camera ()
        {
            AssignVariables(point3(0,5,1),Vec3(0,-1,-1));
        }
        Camera (const point3 &pos,const Vec3 &forwardDir)
        {
            AssignVariables(pos,forwardDir);
        }

        void AssignVariables(const point3 &pos,const Vec3 &forwardDir)
        {
            cameraPosition = pos;
            forwardDirection.startPoint = pos;
            rightDirection.startPoint  = pos;
            upDirection.startPoint = pos;
            
            forwardDirection.rayDirection= forwardDir;

            double dotProduct = dot(forwardDirection.normalizedRay(),worldUp);
            if(dotProduct== 1)
            {
                rightDirection.rayDirection = cross(forwardDir,worldUp);
                upDirection.rayDirection = cross(rightDirection.rayDirection,forwardDir);
            }
            else
            {
                if(dotProduct ==-1)
                {
                    rightDirection.rayDirection = Vec3(1,0,0);
                }
                else
                    rightDirection.rayDirection = cross(forwardDir,worldUp);
                upDirection.rayDirection = cross(rightDirection.rayDirection,forwardDir);
            }
            rightDirection.rayDirection = rightDirection.normalizedRay();
            forwardDirection.rayDirection = forwardDirection.normalizedRay();
            upDirection.rayDirection = upDirection.normalizedRay();

            focalPlaneCentre = forwardDirection.pointAtDist(focalLength);
            upperLeftPos = focalPlaneCentre + upDirection.rayDirection*viewPortHeight*0.5 - rightDirection.rayDirection*viewPortWidth*0.5;
        }

        Ray returnRayToPixelRandom(int rowNum,int colNum) const
        {
            auto u = double(rowNum)/(imageHeight-1);
            auto v = double(colNum)/(imageWidth-1);
            double halfPixelSide1 = double(viewPortHeight)*0.5/imageHeight;
            double halfPixelSide2 = double(viewPortWidth)*0.5/imageWidth;

            halfPixelSide1 = halfPixelSide1* (rand()-RAND_MAX/2)*2/(RAND_MAX+1); // return (-1 or +1) * halfPixelSide
            halfPixelSide2 = halfPixelSide2* (rand()-RAND_MAX/2)*2/(RAND_MAX+1);

            double x = 0;//(rand()-RAND_MAX/2)*2/(RAND_MAX+1)*apertureRadius;
            double y = 0;//(rand()-RAND_MAX/2)*2/(RAND_MAX+1)*apertureRadius;
            
            Ray camToPixel(cameraPosition + unit_vector(upDirection.rayDirection)*x + unit_vector(rightDirection.rayDirection)*y,(upperLeftPos + rightDirection.rayDirection*(v*viewPortWidth + halfPixelSide2) - upDirection.rayDirection*(u*viewPortHeight + halfPixelSide2))-(cameraPosition + unit_vector(upDirection.rayDirection)*x + unit_vector(rightDirection.rayDirection)*y)); // check for the rand/RANDMAX+1 giving only positive values
            
            return camToPixel;
        }

        void lookAt(const Vec3 &point)
        {
            AssignVariables(cameraPosition,point-cameraPosition);
        }

        /*Add zoom in/out functions
        */
};

#endif