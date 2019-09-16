#include "vec.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

int main()
{
     ofstream f1("./res1.csv");
     ofstream f2("./res2.csv");

     float t = 0.0;
     const float dt = 1.0;
     const float m = 85.0;
     const float g = 9.8;
     const float c = m * g / (50 * 50);
     const Vec3 z{0.0, 0.0, 1.0};
     const Vec3 gravity = -m * g * z;

     Vec3 pos = {0.0, 0.0, 4000.0};
     Vec3 speed = {50.0, 0.0, 0.0};
     Vec3 accel = {0.0, 0.0, 0.0};
     Vec3 drag = {0.0, 0.0, 0.0};

     while (t < 60)
     {
         drag = -c * norm(speed) * speed;
         accel = (gravity + drag) / m;
         speed = speed + dt * accel;
        pos = pos + dt * speed;
         f1 << pos << "\n";

		 t += dt;
     }
}