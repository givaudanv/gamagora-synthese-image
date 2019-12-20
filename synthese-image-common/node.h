#pragma once
#include "../synthese-image-common/box.h"
#include "../synthese-image-common/tree.h"

struct Node : public Tree
{
	Box box;
	std::unique_ptr<Tree> left;
	std::unique_ptr<Tree> right;

	Node(Box b) {
		box = b;
		left = nullptr;
		right = nullptr;
	}

	Node(Box b, std::unique_ptr<Tree> l, std::unique_ptr<Tree> r) {
		box = b;
		left = std::move(l);
		right = std::move(r);
	}

	std::optional<float> intersect(Ray ray) {
		return box.intersect(ray);
	}
};