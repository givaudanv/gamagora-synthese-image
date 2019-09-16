#include <cmath>
#include <iostream>

using namespace std;

struct Vec3
{
    float x, y, z;
};

bool operator==(const Vec3 &a, const Vec3 &b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

Vec3 operator+(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x + b.x, a.y + b.y, a.z + b.z};
}

Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x - b.x, a.y - b.y, a.z - b.z};
}

Vec3 operator*(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x * b.x, a.y * b.y, a.z * b.z};
}

Vec3 operator/(const Vec3 &a, const Vec3 &b)
{
    return Vec3{a.x / b.x, a.y / b.y, a.z / b.z};
}

Vec3 operator+(const Vec3 &a, const float &b)
{
    return Vec3{a.x + b, a.y + b, a.z + b};
}

Vec3 operator*(const float &a, const Vec3 &b)
{
	return Vec3{ b.x * a, b.y * a, b.z * a };
}

Vec3 operator/(const Vec3 &a, const float &b)
{
    return Vec3{a.x / b, a.y / b, a.z / b};
}

ostream &operator<<(ostream &os, const Vec3 &a)
{
    os << a.x << ";" << a.y << ";" << a.z;
    return os;
}

float dot(const Vec3 &a, const Vec3 &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float norm(const Vec3 &v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}