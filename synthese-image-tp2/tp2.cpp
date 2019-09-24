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

int main()
{
	PGM pgm(600, 600, 255);
	std::vector<Sphere> sphereTab = {
		Sphere{Vec3<float>{300, 300, 300}, 250},
		Sphere{Vec3<float>{100, 100, 100}, 50},
		Sphere{Vec3<float>{500, 100, 500}, 50},
		Sphere{Vec3<float>{500, 500, 75}, 50},
	};

	std::vector<Light> lightTab = {
		Light{ Vec3<float>{800,800,50}, 100 },
		Light{ Vec3<float>{50,-150,50}, 90 },
	};

	

	for (int row = 0; row < 600; row++) {
		for (int col = 0; col < 600; col++) {
			pgm.pixelMatrix[row][col] = 0;
		}
	}
	
	for (int row = 0; row < 600; row++) {
		for (int col = 0; col < 600; col++) {
			float t = 0;
			float coef = 1;
			Vec3<float> pixel = { float(col), float(600 - row), 0 };
			Ray ray{ pixel, Vec3<float>{ 0, 0, 1 } };
			int currentSphereIndex = -1;

			for (unsigned i = 0; i < sphereTab.size(); i++) {
				std::optional<float> optT = intersect(ray, sphereTab.at(i));

				if (optT && (t == 0 || optT.value() < t)) {
					t = optT.value();
					currentSphereIndex = i;
				}
			}
			
			if (t > 0) {
				Sphere currentSphere = sphereTab.at(currentSphereIndex);
				Vec3<float> pointToLight = { ray.origin + t * ray.direction };

				for (unsigned l = 0; l < lightTab.size(); l++) {
					Light currentLight = lightTab.at(l);
					Vec3<float> lightDir = currentLight.origin - pointToLight;
					Vec3<float> normal = normalize(pointToLight - currentSphere.center);
					float distToLight = norm(lightDir);
					lightDir = normalize(lightDir);
					Ray lightRay{ pointToLight + 0.01f * normal, lightDir };

					bool inShadow = false;
					for (unsigned j = 0; j < sphereTab.size(); j++) {
						std::optional<float> optTLight = intersect(lightRay, sphereTab.at(j));
						if (optTLight) {
							inShadow = true;
							break;
						}
					}

					if (!inShadow) {
						float clamped = clamp(coef * dot(lightRay.direction, normal), 0.0f, 1.0f);
						pgm.pixelMatrix[row][col] = (pgm.pixelMatrix[row][col] / pgm.maxValue) + (clamped * pgm.maxValue);
					}
				}
			}
		}
	}

	pgm.save("image.pgm");
}