#include <iostream>
#include <fstream>
//#include <thread>
 //as Camera.h contains ray.h which contains ownVEC3.h - but look it up to confirm if we can do this or if it is too expensive
#include "World5.h"

colour returnPixelColour(int,int,int);

World w;

int main()
{
    w.addObject(Object("Sphere1","Sphere",Vec3(2,2,-5),Vec3(255,255,255),2,Vec3(1,0,0)));
    w.addObject(Object("Sphere2","Sphere",Vec3(0,-20,-5),Vec3(0,255,0),20,Vec3(0,1,0)));
    w.addObject(Object("Sphere3","Sphere",Vec3(-2,2,-5),Vec3(255,255,255),2,Vec3(1,0,0)));
    //w.addLight(Light());

    int samplesPerPixel =20;
    //char* totTime =__TIME__;
    //__time64_t singleLineTime =__TIME__;

    std::fstream file;
    //file.clear();
    file.open("image.ppm",std::ios::out);
    file<<"P3\n"<<w.cam.imageWidth<<" "<<w.cam.imageHeight<<"\n255\n";

    //std::vector<Ray> camToPixelMemory;
    w.childRays.push_back(w.cam.returnRayToPixelRandom(0,0));

    for (int j = 0; j < w.cam.imageHeight; j++)
    {
        std::cout<<"Line no: "<<(j+1)<<"\n";
        for (int i = 0; i < w.cam.imageWidth; i++)
        {
            file<<returnPixelColourString(returnPixelColour(j,i,samplesPerPixel))<<'\n';
        }
    }    
    file.close();
    std::cout<<"Done";
}


/*void createThreads()
{
    std::thread t(returnPixelColour,2,2,1);
    int numThreads =100;
    int size = w.cam.imageHeight*w.cam.imageWidth;
    int numPixelsPerEachThread = size/numThreads;

    //std::vector<Thread> threads;
    // Create and launch the threads
    /*for (int i = 0; i < numThreads; ++i) {
        int start = i * numPixelsPerEachThread;
        int end = (i == numThreads - 1) ?size : start + numPixelsPerEachThread;

        threads.emplace_back(returnPixelColour, start, end);
    }

    // Join the threads
    for (auto& thread : threads) {
        thread.join();
    }
}*/


inline colour returnPixelColour(int row,int column,int samplesPerPixel)
{
    colour pixelColour;
    
    for (int a = 0; a < samplesPerPixel; a++)
    {
        w.childRays[0] = w.cam.returnRayToPixelRandom(row,column);
        pixelColour += w.returnRayColour(w.childRays,20);
    }

    pixelColour*=double(1)/samplesPerPixel;
    pixelColour.e[0] = 255*pow(pixelColour.x()/255,0.5);
    pixelColour.e[1] = 255*pow(pixelColour.y()/255,0.5);
    pixelColour.e[2] = 255*pow(pixelColour.z()/255,0.5);

    return pixelColour;
}