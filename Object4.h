#ifndef OBJECT4_H
#define OBJECT4_H

#include <iostream>
#include <cstdlib>
#include "MeshData3.h"
#include "Material4.h"
#include <array>
//#include "ray.h"

class Object
{
    public:
        point3 objectPosition;
        std::string meshType;
        std::string objectName;
        colour objectColour;
        Material mat;
        double radius;
        static std::vector<Ray> childRays;
        static std::vector<Ray> childRaysCopy;
        static int childRaysCount;

        Object ()
        {
            objectName = "Object1";
            objectPosition = Vec3(0,0,0);
            meshType = "Sphere";
            objectColour = Vec3(255,0,0);
            radius =2;
            mat.lightInteraction = Vec3(1,0,0);
            mat.reflectance = Vec3(1,0,0);
            //GeneratePointsOnSphere();
        }

        Object (std::string name,std::string meshName,const Vec3 &pos,colour col,double r,const Vec3 &ref)
        {
            objectName =name;
            meshType = meshName;
            objectPosition = pos;
            objectColour = col;
            radius =r;
            mat.lightInteraction = Vec3(0.6,0.4,0);
            mat.reflectance = ref;
            //if(objectName =="Sphere1")
               // GeneratePointsOnSphere(); //Check and change
        }

        std::array<Vec3,3> returnHitInfo(Ray r)
        {
            if(meshType == "Sphere")
                return Sphere(Vec3(0,0,-5),2,r);
        }

        inline double random_double() 
        {
            // Returns a random real in [0,1).
            return rand() / (RAND_MAX + 1.0);
        }

        inline double diffuse() 
        {
            double theta = 2 * M_PI * random_double();
            theta = sqrt(-2 * log(1-random_double()))*cos(theta);
            return theta;
        }
        
        void  GeneratePointsOnSphere()
        {
            childRays.resize(0);
            childRaysCopy.resize(0);
            int numChildRays = childRaysCount - static_cast<int>(childRaysCount*mat.reflectance.e[0]);
            double increment = M_PI * (3 - sqrt(5));
            double y= -1;

            for(int i=0;i<numChildRays;i++)
            {
                y = 1 - (double(i) / (numChildRays- 1)) * 2;  
                double radius =sqrt(double(1) - (y * y));
            
                double x = cos(increment * double(i)) * radius;
                double z = sin(increment * double(i)) * radius;
                std::cout<<x<<" "<<y<<" "<<z<<" "<<"\n";
                childRays.push_back(Ray(Vec3(),Vec3(x,y,z)));    
                childRaysCopy.push_back(Ray(Vec3(),Vec3(x,y,z)));
            }

            for (int i=numChildRays;i<childRaysCount;i++)
            {
                childRays.push_back(Ray(Vec3(),Vec3()));  
                //childRaysCopy.push_back(Ray(Vec3(),Vec3()));
            }
            
        }

        std::vector<Ray> BRDF(Ray &r,Vec3 hitPoint,Vec3 normal,double intensity)
        {
            //intensity/=childRaysCount;
            int numChildRays = childRaysCount - static_cast<int>(childRaysCount*mat.reflectance.e[0]);
            std::vector<Ray> cr;
        
            for (int i = numChildRays; i < childRaysCount; i++)
            //for (int i = 0; i < 1; i++)
            {
                //schildRays[i] = Ray(hitPoint,reflect(r.rayDirection,normal));
                cr.push_back(Ray(hitPoint,reflect(r.rayDirection,normal)));
            }
            
            while (numChildRays>0)
            {
                double x = diffuse();
                double y = diffuse();
                double z = diffuse();

                float a = dot(Vec3(x,y,z)*1000.0,normal*1000.0);
                a = (a>0) - (a<0);
                cr.push_back(Ray(hitPoint,Vec3(x,y,z)*((int)a)));

                numChildRays-=1;
            }
            return cr;
        } 
};


std::vector<Ray> Object::childRays;
std::vector<Ray> Object::childRaysCopy;
int Object::childRaysCount =10;

/*inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}
*/
#endif