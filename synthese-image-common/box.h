#pragma once
#include "vec.h"

using namespace std;

struct Box
{
	Vec3<float> min;
	Vec3<float> max;

	std::optional<float> intersect(Ray r) {
		float tmin = (min.x - r.origin.x) / r.direction.x;
		float tmax = (max.x - r.origin.x) / r.direction.x;

		if (tmin > tmax) swap(tmin, tmax);

		float tymin = (min.y - r.origin.y) / r.direction.y;
		float tymax = (max.y - r.origin.y) / r.direction.y;

		if (tymin > tymax) swap(tymin, tymax);

		if ((tmin > tymax) || (tymin > tmax))
			return {};

		if (tymin > tmin)
			tmin = tymin;

		if (tymax < tmax)
			tmax = tymax;

		float tzmin = (min.z - r.origin.z) / r.direction.z;
		float tzmax = (max.z - r.origin.z) / r.direction.z;

		if (tzmin > tzmax) swap(tzmin, tzmax);

		if ((tmin > tzmax) || (tzmin > tmax))
			return {};

		if (tzmin > tmin)
			tmin = tzmin;

		if (tzmax < tmax)
			tmax = tzmax;

		return std::min(tmin, tmax);
	}
};