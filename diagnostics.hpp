#pragma once
#include <vector>
#include "body.hpp"

double computeTotalEnergy(const std::vector<Body>& bodies);
Vec3 computeTotalAngularMomentum(const std::vector<Body>& bodies);
Vec3 computeLinearMomentum(const std::vector<Body>& bodies);
Vec3 computeCenterOfMass(const std::vector<Body>& bodies);