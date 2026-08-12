#include "gravity.hpp"
#include "integrator.hpp"

void velocityVerletStep(std::vector<Body>& bodies, double dt)
{
    const std::size_t N = bodies.size();
    std::vector<Vec3> a_old = computeAccelerations(bodies);//前ステップの加速度を格納

    //半時間後の速度を計算
    for (std::size_t i = 0; i < N; ++i)
    {
        bodies[i].v = bodies[i].v + a_old[i] * (0.5 * dt);
    }

    //位置を1ステップ進める
    for (std::size_t i = 0; i < N; ++i)
    {
        bodies[i].r = bodies[i].r + bodies[i].v * dt;
    }

    //新しい位置での加速度を計算
    std::vector<Vec3> a_new = computeAccelerations(bodies);

    //残り半ステップ速度を進める
    for (std::size_t i = 0; i < N; ++i)
    {
        bodies[i].v = bodies[i].v + a_new[i] * (0.5 * dt);
    }
}