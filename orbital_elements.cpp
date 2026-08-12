#include "orbital_elements.hpp"
#include "vec3.hpp"

#include <cmath>

constexpr double G = 6.67430e-11;

OrbitalElements computeOrbitalElements(
    const Body& body1,
    const Body& body2
)
{
    Vec3 r = body2.r - body1.r;
    Vec3 v = body2.v - body1.v;

    double mu
        = G * (body1.mass + body2.mass);

    double rmag = norm(r);
    double v2   = dot(v, v);

    // 比角運動量
    Vec3 h = cross(r, v);
    double hmag = norm(h);

    // 離心率ベクトル
    Vec3 eVec
        = cross(v, h) / mu
        - r / rmag;

    double e = norm(eVec);

    // 比軌道エネルギー
    double energy
        = 0.5 * v2
        - mu / rmag;

    // 長半径
    double a
        = -mu / (2.0 * energy);

    // 軌道傾斜角
    double inclination
        = std::acos(h.z / hmag);

    // 昇交点ベクトル
    Vec3 k = {0.0, 0.0, 1.0};

    Vec3 n = cross(k, h);

    double nmag = norm(n);

    // 昇交点赤経
    double Omega
        = std::atan2(n.y, n.x);

    if (Omega < 0.0)
    {
        Omega += 2.0 * M_PI;
    }

    // 近点引数
    double omega
        = std::acos(
            dot(n, eVec)
            / (nmag * e)
        );

    if (eVec.z < 0.0)
    {
        omega
            = 2.0 * M_PI - omega;
    }

    // 真近点角
    double nu
        = std::acos(
            dot(eVec, r)
            / (e * rmag)
        );

    if (dot(r, v) < 0.0)
    {
        nu
            = 2.0 * M_PI - nu;
    }

    return {
        a,
        e,
        inclination,
        Omega,
        omega,
        nu
    };
}