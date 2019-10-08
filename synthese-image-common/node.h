#pragma once
#include "../synthese-image-common/box.h"
#include "../synthese-image-common/tree.h"
struct Node : public Tree
{
	Box* box;
	Tree* left;
	Tree* right;

	Node(Box* s) {
		box = s;
	}

	Node(Box* s, Tree* l, Tree* r) {
		box = s;
		left = l;
		right = r;
	}

	std::optional<float> intersect(Ray r) {
		float t;

		float t1 = (box->min.x - r.origin.x) * r.direction.x;
		float t2 = (box->max.x - r.origin.x) * r.direction.x;
		float t3 = (box->min.y - r.origin.y) * r.direction.y;
		float t4 = (box->max.y - r.origin.y) * r.direction.y;
		float t5 = (box->min.z - r.origin.z) * r.direction.z;
		float t6 = (box->max.z - r.origin.z) * r.direction.z;

		float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
		float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

		// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
		if (tmax < 0)
		{
			return {};
		}

		// if tmin > tmax, ray doesn't intersect AABB
		if (tmin > tmax)
		{
			return {};
		}

		t = tmin;
		return t;
	}
};