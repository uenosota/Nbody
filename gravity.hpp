#pragma once
#include <vector>
#include "body.hpp"
#include "vec3.hpp"

std::vector<Vec3> computeAccelerations(const std::vector<Body>& bodies);
