#include "pch.h"
#include "CppUnitTest.h"
#include "../synthese-image-common/ray.h"
#include "../synthese-image-common/sphere.h"
#include "../synthese-image-common/vec.h"
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
			Assert::AreEqual(expected, t.value());
		}

		TEST_METHOD(TestNoIntersection)
		{
			Sphere sphere{ Vec3<float>{10, 0, 0}, 2 };
			Ray ray{ Vec3<float>{0, 0, 0}, Vec3<float>{0,1,0} };
			float expected = -1;

			std::optional<float> t = intersect(ray, sphere);
			Assert::AreEqual(expected, t.value_or(-1));
		}
	};
}
