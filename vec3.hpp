#pragma once
#include <cmath>
struct Vec3{
    double x,y,z;
    Vec3 operator+(const Vec3& other) const{
        return {
            x+other.x,
            y+other.y,
            z+other.z
        };
    }
    Vec3 operator-(const Vec3& other) const{
        return {
            x-other.x,
            y-other.y,
            z-other.z
        };
    }
    Vec3 operator*(double scalar) const{
        return {
            x*scalar,
            y*scalar,
            z*scalar
        };
    }
    Vec3 operator/(double scalar) const{
        return {
            x/scalar,
            y/scalar,
            z/scalar
        };
    }
};

inline double norm(const Vec3& a){
    return { 
        std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
    };
}
inline double dot(const Vec3& a, const Vec3& b){
    return {
        a.x * b.x + a.y * b.y + a.z * b.z
    };
}
inline Vec3 cross(const Vec3& a, const Vec3& b){
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

