#pragma once
#include "vec.h"

using namespace std;

struct Sphere
{
	Vec3<float> center;
	float radius;
	Vec3<float> albedo;

	std::optional<float> intersect(Ray ray) {
		float a = 1;
		float b = 2 * (dot(ray.origin, ray.direction) - dot(center, ray.direction));
		float c = squaredNorm(ray.origin) + squaredNorm(center) - 2 * dot(center, ray.origin) - (radius * radius);

		float delta = b * b - 4 * c;
		float t = 0;

		if (delta < 0) {
			return {};
		}
		else {
			t = (-b - sqrt(delta)) / (2 * a);
			if (t < 0) {
				t = (-b + sqrt(delta)) / (2 * a);
				if (t < 0)
					return {};
			}
		}
		return t;
	}
};
