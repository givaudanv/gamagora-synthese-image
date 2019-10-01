#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/light.h"
#include "../synthese-image-common/vec.h"
#include "../synthese-image-common/PGM.cpp"
#include "../synthese-image-common/PPM.cpp"
#include "tp2.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <optional>
#include <algorithm>

std::optional<float> intersect(Ray ray, Sphere sphere) {
	float a = 1;
	float b = 2 * (dot(ray.origin, ray.direction) - dot(sphere.center, ray.direction));
	float c = squaredNorm(ray.origin) + squaredNorm(sphere.center) - 2 * dot(sphere.center, ray.origin) - (sphere.radius * sphere.radius);

	float delta = b * b - 4 * c;
	float t = 0;

	if (delta < 0) {
		return {};
	} else {
		t = (-b - sqrt(delta)) / (2 * a);
		if (t < 0) {
			t = (-b + sqrt(delta)) / (2 * a);
			if (t < 0)
				return {};
		}
	}
	return t;
}

void initPPM(PPM &ppm) {
	for (int row = 0; row < 600; row++) {
		for (int col = 0; col < 600; col++) {
			ppm.pixelMatrix[row][col] = Vec3<int>{ 0, 0, 0 };
		}
	}
}

void firstIntersect(float &distance, int &currentSphereIndex, std::vector<Sphere> sphereTab, Ray ray) {
	for (unsigned i = 0; i < sphereTab.size(); i++) {
		std::optional<float> optT = intersect(ray, sphereTab.at(i));

		if (optT && (distance == 0 || optT.value() < distance)) {
			distance = optT.value();
			currentSphereIndex = i;
		}
	}
}

bool shadow(std::vector<Sphere> sphereTab, Ray lightRay) {
	bool inShadow = false;
	for (unsigned j = 0; j < sphereTab.size(); j++) {
		std::optional<float> optTLight = intersect(lightRay, sphereTab.at(j));
		if (optTLight) {
			inShadow = true;
			break;
		}
	}
	return inShadow;
}

int main()
{
	PPM ppm(600, 600, 1000);
	std::vector<Sphere> sphereTab = {
		Sphere{Vec3<float>{300, 300, 300}, 200},
		Sphere{Vec3<float>{75, 75, 50}, 25},
		Sphere{Vec3<float>{525, 525, 50}, 25},
		//Sphere{Vec3<float>{300, 300, 10000}, 300},
	};

	std::vector<Light> lightTab = {
		Light{ Vec3<float>{700,300,100}, Vec3<float>{100, 0, 0}, 1},
		Light{ Vec3<float>{0,0,-50}, Vec3<float>{100, 0, 100}, 1},
	};

	Vec3<float> camOrigin = { 300, 300, -1000 };

	initPPM(ppm);
	
	for (int row = 0; row < 600; row++) {
		for (int col = 0; col < 600; col++) {
			Vec3<float> pixel = { float(col), float(600 - row), 0 };
			Vec3<float> camDir = normalize(pixel - camOrigin);
			Ray ray{ pixel, camDir};
			float distance = 0;
			int currentSphereIndex = -1;

			firstIntersect(distance, currentSphereIndex, sphereTab, ray);
			
			if (distance > 0) {
				Sphere currentSphere = sphereTab.at(currentSphereIndex);
				Vec3<float> pointToLight = { ray.origin + distance * ray.direction };

				for (unsigned l = 0; l < lightTab.size(); l++) {
					Light currentLight = lightTab.at(l);
					Vec3<float> lightDir = normalize(currentLight.origin - pointToLight);
					Vec3<float> normal = normalize(pointToLight - currentSphere.center);
					float distToLight = norm(currentLight.origin - pointToLight);
					Ray lightRay{ pointToLight + 0.01f * normal, lightDir};

					bool inShadow = shadow(sphereTab, lightRay);

					if (!inShadow) {
						Vec3<float> clampedLightColor = clampVec3(currentLight.color, 0.0f, 1.0f);
						float clampedX = clamp(ppm.pixelMatrix[row][col].x + (currentLight.intensity * dot(lightRay.direction, normal) * clampedLightColor.x), 0.0f, 1.0f);
						float clampedY = clamp(ppm.pixelMatrix[row][col].y + (currentLight.intensity * dot(lightRay.direction, normal) * clampedLightColor.y), 0.0f, 1.0f);
						float clampedZ = clamp(ppm.pixelMatrix[row][col].z + (currentLight.intensity * dot(lightRay.direction, normal) * clampedLightColor.z), 0.0f, 1.0f);
						ppm.pixelMatrix[row][col].x = clampedX * ppm.maxValue;
						ppm.pixelMatrix[row][col].y = clampedY * ppm.maxValue;
						ppm.pixelMatrix[row][col].z = clampedZ * ppm.maxValue;

						/*Vec3<float> clampedLightColor = clampVec3(currentLight.color, 0.0f, 1.0f);
						float clampedX = clamp(ppm.pixelMatrix[row][col].x + ((currentLight.intensity) * dot(lightRay.direction, normal) * clampedLightColor.x), 0.0f, 1.0f);
						ppm.pixelMatrix[row][col].x = clampedX * ppm.maxValue;*/
					}
				}
			}
		}
	}

	ppm.save("image.ppm");
}