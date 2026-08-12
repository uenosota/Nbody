#pragma once
#include "body.hpp"
#include "vec3.hpp"
#include <vector>

void velocityVerletStep(
    std::vector<Body>& bodies,
    double dt
);

