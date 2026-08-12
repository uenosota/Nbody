#pragma once
#include <cmath>
#include <vector>
#include "vec3.hpp"
#include "body.hpp"

struct OrbitalElements{
    double a;//長半径
    double e;//離心率
    double i;//軌道傾斜角
    double Omega;//昇交点経度
    double omega;//近点引数
    double mu;//平均近点角
};

OrbitalElements computeOrbitalElements(
    const Body& body1,
    const Body& body2
);

