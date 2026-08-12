#include "diagnostics.hpp"
#include <cmath>
#include "vec3.hpp"

constexpr double G = 6.67430e-11; // Gravitational constant

double computeTotalEnergy(const std::vector<Body>& bodies)//エネルギーの計算
{
    double kinetic = 0.0;
    double potential = 0.0;
    const std::size_t N = bodies.size();

    //運動エネルギーの計算
    for (std::size_t i = 0; i < N; ++i)
    {
        kinetic += 0.5 * bodies[i].mass * dot(bodies[i].v, bodies[i].v);
    }
    //位置エネルギーの計算
    for (std::size_t i = 0; i < N; ++i)
    {
        for(std::size_t j=i+1; j<N; j++){
            Vec3 dr = bodies[j].r - bodies[i].r;
            double distance = norm(dr);
            potential -= G * bodies[i].mass * bodies[j].mass / distance;
        }
    }

    return kinetic + potential;
}

Vec3 computeTotalAngularMomentum(const std::vector<Body>& bodies){//角運動量の計算
    Vec3 L={0.0, 0.0, 0.0};
    for(const Body& body : bodies){
        L = L + cross(body.r, body.v) * body.mass;
    }
    return L;
}

Vec3 computeLinearMomentum(const std::vector<Body>& bodies){//全角運動量の計算
    Vec3 P={0.0, 0.0, 0.0};
    for(const Body& body : bodies){
        P = P + body.v * body.mass;
    }
    return P;
}

Vec3 computeCenterOfMass(const std::vector<Body>& bodies){//重心の計算
    Vec3 com={0.0, 0.0, 0.0};
    double total_mass=0.0;
    for(const Body& body : bodies){
        com = com + body.r * body.mass;
        total_mass += body.mass;
    }
    return com / total_mass;
}