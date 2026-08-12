#include "gravity.hpp"

constexpr double G = 6.67430e-11; // Gravitational constant

std::vector<Vec3> computeAccelerations(const std::vector<Body>& bodies)
{
    const std::size_t N = bodies.size();
    std::vector<Vec3> accelerations(N, {0.0, 0.0, 0.0});//全天体の加速度を格納するベクトル，初期値をゼロとする，

    //各天体の重力を計算
    for (std::size_t i = 0; i < N; ++i)
    {
        for (std::size_t j = 0; j < N; ++j)
        {
            if (i == j)
                continue;
            Vec3 dr = bodies[j].r - bodies[i].r;//天体iから見た天体jの位置ベクトル
            double distance = norm(dr);//距離の計算
            accelerations[i] = accelerations[i] + dr * (G * bodies[j].mass / (distance * distance * distance));//天体iの加速度を更新 
        }
    }
    return accelerations;
}

