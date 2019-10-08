#pragma once
#include "../synthese-image-common/ray.h"
#include <optional>

struct Tree
{
	virtual std::optional<float> intersect(Ray ray) = 0;
};