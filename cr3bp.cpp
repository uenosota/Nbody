#include "vec3.hpp"
#include <cmath>

Vec3 computeCR3BPAcceleration(
    const Vec3& r,
    const Vec3& v,
    double mu
)
{
    double x = r.x;
    double y = r.y;
    double z = r.z;

    double vx = v.x;
    double vy = v.y;

    double r1 = std::sqrt(
        (x + mu) * (x + mu)
        + y * y
        + z * z
    );

    double r2 = std::sqrt(
        (x - 1.0 + mu) * (x - 1.0 + mu)
        + y * y
        + z * z
    );

    double ax =
        x
        - (1.0 - mu) * (x + mu) / (r1 * r1 * r1)
        - mu * (x - 1.0 + mu) / (r2 * r2 * r2)
        + 2.0 * vy;

    double ay =
        y
        - (1.0 - mu) * y / (r1 * r1 * r1)
        - mu * y / (r2 * r2 * r2)
        - 2.0 * vx;

    double az =
        -(1.0 - mu) * z / (r1 * r1 * r1)
        - mu * z / (r2 * r2 * r2);

    return {ax, ay, az};
}

double computeJacobiConstant(
    const Vec3& r,
    const Vec3& v,
    double mu
)
{
    double x = r.x;
    double y = r.y;
    double z = r.z;

    double r1 = std::sqrt(
        (x + mu) * (x + mu)
        + y * y
        + z * z
    );

    double r2 = std::sqrt(
        (x - 1.0 + mu) * (x - 1.0 + mu)
        + y * y
        + z * z
    );

    double Omega =
        0.5 * (x * x + y * y)
        + (1.0 - mu) / r1
        + mu / r2;

    double v2 = dot(v, v);

    return 2.0 * Omega - v2;
}