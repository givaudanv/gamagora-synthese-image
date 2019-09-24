#pragma once
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include <optional>

std::optional<float> intersect(Ray ray, Sphere sphere);