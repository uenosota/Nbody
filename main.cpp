#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

#include "body.hpp"
#include "integrator.hpp"
#include "diagnostics.hpp"


int main()
{
    // ============================================================
    // 1. 天体の初期条件
    // ============================================================

    std::vector<Body> bodies;


    // ------------------------------------------------------------
    // Body 1
    // ------------------------------------------------------------

    Body body1;

    body1.name = "Body1";
    body1.mass = 1.0e20;

    body1.r = {
        -5.0e6,
         0.0,
         0.0
    };

    body1.v = {
         0.0,
        -20.0,
         0.0
    };

    bodies.push_back(body1);


    // ------------------------------------------------------------
    // Body 2
    // ------------------------------------------------------------

    Body body2;

    body2.name = "Body2";
    body2.mass = 1.0e20;

    body2.r = {
         5.0e6,
         0.0,
         0.0
    };

    body2.v = {
         0.0,
         20.0,
         0.0
    };

    bodies.push_back(body2);


    // ------------------------------------------------------------
    // Body 3
    // ------------------------------------------------------------

    Body body3;

    body3.name = "Body3";
    body3.mass = 1.0e18;

    body3.r = {
         0.0,
         8.0e6,
         0.0
    };

    body3.v = {
        -25.0,
         0.0,
         0.0
    };

    bodies.push_back(body3);


    // ============================================================
    // 2. 時間積分条件
    // ============================================================

    double dt = 10.0;          // 時間刻み [s]

    double endTime = 1.0e6;    // 終了時刻 [s]

    int nSteps =
        static_cast<int>(endTime / dt);


    // CSVへの出力間隔
    int outputInterval = 100;


    // ============================================================
    // 3. 初期保存量
    // ============================================================

    double E0 =
        computeTotalEnergy(bodies);

    Vec3 L0 =
        computeTotalAngularMomentum(bodies);

    Vec3 P0 =
        computeLinearMomentum(bodies);

    Vec3 RCM0 =
        computeCenterOfMass(bodies);


    std::cout
        << std::setprecision(16);

    std::cout
        << "Initial energy = "
        << E0
        << "\n";

    std::cout
        << "Initial angular momentum = "
        << L0.x << ", "
        << L0.y << ", "
        << L0.z
        << "\n";

    std::cout
        << "Initial linear momentum = "
        << P0.x << ", "
        << P0.y << ", "
        << P0.z
        << "\n";

    std::cout
        << "Initial center of mass = "
        << RCM0.x << ", "
        << RCM0.y << ", "
        << RCM0.z
        << "\n";


    // ============================================================
    // 4. CSVファイルを開く
    // ============================================================

    std::ofstream file("nbody_result.csv");

    if (!file)
    {
        std::cerr
            << "Could not open output file.\n";

        return 1;
    }


    file
        << std::setprecision(16);


    // ============================================================
    // 5. CSVヘッダー
    // ============================================================

    file
        << "time,"
        << "body,"
        << "x,y,z,"
        << "vx,vy,vz,"
        << "energy_error,"
        << "angular_momentum_error"
        << "\n";


    // ============================================================
    // 6. 時間積分
    // ============================================================

    for (int step = 0;
         step <= nSteps;
         ++step)
    {
        double time =
            step * dt;


        // --------------------------------------------------------
        // 結果を出力
        // --------------------------------------------------------

        if (step % outputInterval == 0)
        {
            double E =
                computeTotalEnergy(bodies);

            Vec3 L =
                computeTotalAngularMomentum(bodies);


            double energyError =
                (E - E0)
                / std::abs(E0);


            double angularMomentumError =
                norm(L - L0)
                / norm(L0);


            for (const Body& body : bodies)
            {
                file
                    << time << ","
                    << body.name << ","

                    << body.r.x << ","
                    << body.r.y << ","
                    << body.r.z << ","

                    << body.v.x << ","
                    << body.v.y << ","
                    << body.v.z << ","

                    << energyError << ","
                    << angularMomentumError
                    << "\n";
            }


            std::cout
                << "time = "
                << time
                << " / "
                << endTime
                << "\n";
        }


        // 最終ステップではこれ以上進めない
        if (step == nSteps)
        {
            break;
        }


        // --------------------------------------------------------
        // Velocity Verletで1ステップ進める
        // --------------------------------------------------------

        velocityVerletStep(
            bodies,
            dt
        );
    }


    // ============================================================
    // 7. 最終保存量
    // ============================================================

    double E =
        computeTotalEnergy(bodies);

    Vec3 L =
        computeTotalAngularMomentum(bodies);

    Vec3 P =
        computeLinearMomentum(bodies);

    Vec3 RCM =
        computeCenterOfMass(bodies);


    std::cout
        << "\nCalculation finished.\n";


    std::cout
        << "Relative energy error = "
        << (E - E0) / std::abs(E0)
        << "\n";


    std::cout
        << "Relative angular momentum error = "
        << norm(L - L0) / norm(L0)
        << "\n";


    std::cout
        << "Linear momentum change = "
        << norm(P - P0)
        << "\n";


    std::cout
        << "Center of mass change = "
        << norm(RCM - RCM0)
        << "\n";


    file.close();

    return 0;
}