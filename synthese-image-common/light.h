#pragma once
#include <cmath>
#include <iostream>
#include "vec.h"

using namespace std;

struct Light
{
	Vec3<float> origin;
	Vec3<float> color;
	float intensity;
};
