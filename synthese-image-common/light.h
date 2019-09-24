#pragma once
#include <cmath>
#include <iostream>
#include "vec.h"

using namespace std;

struct Light
{
	Vec3<float> origin;
	float intensity;
};
