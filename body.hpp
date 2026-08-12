#pragma once

#include "vec3.hpp"
#include <string>

struct Body{
    std::string name;
    double mass;

    Vec3 r;
    Vec3 v;
    Vec3 a;
};