#pragma once
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/tree.h"

struct Leaf : public Tree
{
	Sphere* sphere;

	Leaf(Sphere* s) {
		sphere = s;
	}

	std::optional<float> intersect(Ray ray) {
		float a = 1;
		float b = 2 * (dot(ray.origin, ray.direction) - dot(sphere->center, ray.direction));
		float c = squaredNorm(ray.origin) + squaredNorm(sphere->center) - 2 * dot(sphere->center, ray.origin) - (sphere->radius * sphere->radius);

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