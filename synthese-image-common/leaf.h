#pragma once
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/tree.h"

struct Leaf : public Tree
{
	std::unique_ptr<Sphere> sphere;

	Leaf(Sphere s) {
		sphere = std::unique_ptr<Sphere>(new Sphere(s));
	}

	std::optional<float> intersect(Ray ray) {
		return sphere->intersect(ray);
	}
};