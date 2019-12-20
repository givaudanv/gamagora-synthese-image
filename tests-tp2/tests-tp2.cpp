#include "pch.h"
#include "CppUnitTest.h"
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/box.h"
#include "../synthese-image-common/light.h"
#include "../synthese-image-common/vec.h"
#include "../synthese-image-common/tree.h"
#include "../synthese-image-common/leaf.h"
#include "../synthese-image-common/node.h"
#include "../synthese-image-tp2/tp2.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <optional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace teststp2
{
	TEST_CLASS(teststp2)
	{
	public:
		
		TEST_METHOD(TestIntersection)
		{
			Sphere sphere{ Vec3<float>{20, 0, 0}, 5 };
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{1,0,0} };
			float expected = 15;

			std::optional<float> t = intersect(ray, sphere);
			Assert::AreEqual(expected, t.value_or(-1));
		}

		TEST_METHOD(TestNoIntersection)
		{
			Sphere sphere{ Vec3<float>{10, 0, 0}, 2 };
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{0,1,0} };
			float expected = -1;

			std::optional<float> t = intersect(ray, sphere);
			Assert::AreEqual(expected, t.value_or(-1));
		}

		TEST_METHOD(TestFirstIntersection)
		{
			std::vector<Sphere> sphereTab = {
				Sphere{Vec3<float>{0, 0, 100}, 5},
				Sphere{Vec3<float>{0, 0, 20}, 5},
			};
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{0,0,1} };
			float expectedDistance = 15;
			float distance = 0;
			int expectedIndex = 1;
			int currentSphereIndex = -1;

			firstIntersect(distance, currentSphereIndex, sphereTab, ray);
			Assert::AreEqual(expectedDistance, distance);
			Assert::AreEqual(expectedIndex, currentSphereIndex);
		}

		TEST_METHOD(TestSecondIntersection)
		{
			std::vector<Sphere> sphereTab = {
				Sphere{Vec3<float>{0, 0, 20}, 10},
				Sphere{Vec3<float>{0, 0, 100}, 5},
			};
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{0,0,1} };
			float expectedDistance = 10;
			float distance = 0;
			int expectedIndex = 0;
			int currentSphereIndex = -1;

			firstIntersect(distance, currentSphereIndex, sphereTab, ray);
			Assert::AreEqual(expectedDistance, distance);
			Assert::AreEqual(expectedIndex, currentSphereIndex);
		}

		TEST_METHOD(TestIntersectionFeuille)
		{
			Sphere sphere{ Vec3<float>{0, 0, 20}, 5 };
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{0,0,1} };
			Leaf l(&sphere);
			float expected = 15;

			std::optional<float> t = l.intersect(ray);
			Assert::AreEqual(expected, t.value_or(-1));
		}

		TEST_METHOD(TestIntersectionNode)
		{
			Box box{ Vec3<float>{0, 0, 10}, Vec3<float>{10, 10, 20}};
			Ray ray{ Vec3<float>{5, 5, 0}, Vec3<float>{0,0,1} };
			Node n(&box);
			float expected = 10;

			std::optional<float> t = n.intersect(ray);
			Assert::AreEqual(expected, t.value());
		}
	};
}
