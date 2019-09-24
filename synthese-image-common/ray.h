#pragma once
#include <cmath>
#include <iostream>
#include "vec.h"

using namespace std;

struct Ray
{
	Vec3<float> origin;
	Vec3<float> direction;
};
