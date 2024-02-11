#ifndef Vec31_H
#define Vec31_H

#include<iostream>
#include <cmath>
// Try to create a common class for all vec types such as vec2 vec4 and so on.

class Vec3
{
    public:
        double e[3];
        Vec3 ()
        {
            e[0] = 0;
            e[1] = 0;
            e[2] = 0;
        }
        Vec3 (double e0,double e1, double e2)
        {
            e[0] = e0;
            e[1] = e1;
            e[2] = e2;
        }

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        void operator=(const Vec3 &v)
        {
            e[0] = v.x();
            e[1] = v.y();
            e[2] = v.z();
            //return *this;
        }
        Vec3& operator-()
        {
            e[0] = -e[0];
            e[1] = -e[1];
            e[2] = -e[2];
            return *this;
        }
        void operator+=(const Vec3 &v)
        {
            e[0]+=v.x();
            e[1]+=v.y();
            e[2]+=v.z();
            //return *this;
        }
        void operator-=(const Vec3 &v)
        {
            e[0]-=v.x();
            e[1]-=v.y();
            e[2]-=v.z();
            //return *this;
        }
        void operator*=(double v)
        {
            e[0]*=v;
            e[1]*=v;
            e[2]*=v;
            //return *this;
        }
        void operator/=(double v)
        {
            e[0]/=v;
            e[1]/=v;
            e[2]/=v;
            //return *this;
        }

        double magnitudeSquared () const 
        {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(v.e[0]*t,v.e[1]*t,v.e[2]*t);
}

inline Vec3 operator*(const Vec3 v, double t) {
    return t * v;
}

inline Vec3 operator/(const Vec3 &v, double t) {
    return (1/t) * v;
}

inline double dot(const Vec3 &u, const Vec3 &v) {
    return u.e[0] * v.e[0]+ u.e[1] * v.e[1]+ u.e[2] * v.e[2];
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],u.e[2] * v.e[0] - u.e[0] * v.e[2],u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline Vec3 unit_vector(const Vec3 &v) {
    if(v.magnitudeSquared()!=0)
        return v /sqrt(v.magnitudeSquared()); // update with the quake 3 algorithm.
    else
        return Vec3(0,0,0);
}

inline Vec3 reflect(const Vec3 &v,const Vec3 &normal) {
    Vec3 n = unit_vector(normal);
    return v-2*dot(v,n)*n;
    //return 2*dot(v,n)*n-v; //<-this is done for fun only - the above is the correct one.
}

using colour = Vec3;
using point3 = Vec3;
#endif