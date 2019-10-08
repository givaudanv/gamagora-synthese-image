#pragma once
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/PPM.h"
#include <optional>
#include <vector>

std::optional<float> intersect(Ray ray, Sphere sphere);
void initPPM(PPM &ppm);
void firstIntersect(float& distance, int& currentSphereIndex, std::vector<Sphere> sphereTab, Ray ray);
bool shadow(std::vector<Sphere> sphereTab, Ray lightRay);
std::vector<Light> generateLightSphere(Vec3<float> c, float r, float intensity, int nbPoint);
float randomFloat();