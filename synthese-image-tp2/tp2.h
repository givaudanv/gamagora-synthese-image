#pragma once
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/PPM.h"
#include <optional>
#include <vector>

std::optional<float> intersect(Ray ray, Sphere sphere);
void initPPM(PPM &ppm);
void firstIntersect(float& distance, int& currentSphereIndex, std::vector<Sphere> sphereTab, Ray ray);