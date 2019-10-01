#pragma once
#include <cmath>
#include <iostream>
#include "vec.h"

using namespace std;

struct Sphere
{
	Vec3<float> center;
	Vec3<float> albedo;
	float radius;
};
