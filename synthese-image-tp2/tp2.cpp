#define _USE_MATH_DEFINES
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/box.h"
#include "../synthese-image-common/tree.h"
#include "../synthese-image-common/node.h"
#include "../synthese-image-common/leaf.h"
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
#include <math.h>

float randomFloat() {
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

std::vector<Light> generateLightSphere(Vec3<float> c, float r, float intensity, int nbPoint) {
	std::vector<Light> lightSphere;

	for (int i = 0; i < nbPoint; i++) {
		float r1 = randomFloat();
		float r2 = randomFloat();
		float x = c.x + 2 * r * cos(2 * (float)M_PI * r1) * sqrt(r2 * (2 - r2));
		float y = c.y + 2 * r * sin(2 * (float)M_PI * r1) * sqrt(r2 * (2 - r2));
		float z = c.z + r * (2 - 2 * r2);
		lightSphere.push_back({ Vec3<float>{x, y, z}, Vec3<float>{100,100,100}, intensity });
	}

	return lightSphere;
}

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

/*Node generateTree(std::vector<Sphere> spheres) {
	Node root;
	std::vector<Leaf> leaves;

	for (Sphere s : spheres)
	{
		Leaf l(&s);
		leaves.push_back(l);
	}

	return root;
}*/

int main()
{
	srand(static_cast <unsigned> (time(0)));
	PPM ppm(600, 600, 100);
	Vec3<float> camOrigin = { 300, 300, -1000 };

	std::vector<Sphere> sphereTab = {
		Sphere{Vec3<float>{300, 300, 300}, 200, Vec3<float>{30, 50, 15}},
		Sphere{Vec3<float>{75, 75, 50}, 25, Vec3<float>{70, 70, 1}},
		Sphere{Vec3<float>{525, 300, 50}, 30, Vec3<float>{1, 100, 1}},
		Sphere{Vec3<float>{100, 500, 400}, 30, Vec3<float>{100, 100, 100}},
		Sphere{Vec3<float>{550, 525, 400}, 100, Vec3<float>{1, 1, 1}},
	};

	//std::vector<Light> lightTab = generateLightSphere(Vec3<float>{ 100, 550, 25 }, 10, 1, 20);
	std::vector<Light> lightTab = {
		Light{ Vec3<float>{100, 550, 25}, Vec3<float>{100,100,100}, 0.1f },
		Light{ Vec3<float>{600, 300, 25}, Vec3<float>{100,100,100}, 0.1f }
	};

	//Node root = generateTree(sphereTab);

	initPPM(ppm);
	
	for (int row = 0; row < 600; row++) {
		for (int col = 0; col < 600; col++) {
			Vec3<float> pixel = { float(col), float(600 - row), 0 };
			float red = 0, green = 0, blue = 0;
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
					float distToLight = norm(lightDir);
					Ray lightRay{ pointToLight + 0.01f * normal, lightDir};

					bool inShadow = shadow(sphereTab, lightRay);

					if (!inShadow) {
						red += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.x * currentSphere.albedo.x);
						green += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.y * currentSphere.albedo.y);
						blue += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.z * currentSphere.albedo.z);
						/*red += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.x);
						green += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.y);
						blue += ((currentLight.intensity * (1 / (distToLight * distToLight))) * dot(lightRay.direction, normal) * currentLight.color.z);*/
					}
				}
			}
			ppm.pixelMatrix[row][col].x = clamp((int)red, 0, ppm.maxValue);
			ppm.pixelMatrix[row][col].y = clamp((int)green, 0, ppm.maxValue);
			ppm.pixelMatrix[row][col].z = clamp((int)blue, 0, ppm.maxValue);
		}
	}

	ppm.save("image.ppm");
}