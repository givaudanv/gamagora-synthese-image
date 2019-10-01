#pragma once
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
struct Vec3
{
    T x, y, z;
};

template<typename T>
bool operator==(const T&a, const T&b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<typename T>
T operator+(const T&a, const T&b)
{
    return T{a.x + b.x, a.y + b.y, a.z + b.z};
}

template<typename T>
T operator-(const T&a, const T&b)
{
    return T{a.x - b.x, a.y - b.y, a.z - b.z};
}

template<typename T>
T operator*(const T&a, const T&b)
{
    return T{a.x * b.x, a.y * b.y, a.z * b.z};
}

template<typename T>
T operator/(const T&a, const T&b)
{
    return T{a.x / b.x, a.y / b.y, a.z / b.z};
}

template<typename T>
T operator+(const T&a, const float &b)
{
    return T{a.x + b, a.y + b, a.z + b};
}

template<typename T>
T operator*(const float &a, const T &b)
{
	return T{ b.x * a, b.y * a, b.z * a };
}

template<typename T>
T operator/(const T &a, const float &b)
{
    return T{a.x / b, a.y / b, a.z / b};
}

template<typename T>
float dot(const T &a, const T &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template<typename T>
float squaredNorm(const T& a) {
	return dot(a, a);
}

template<typename T>
float norm(const T &v)
{
    return std::sqrt(squaredNorm(v));
}

template<typename T>
T normalize(const T& v)
{
	return v / norm(v);
}

template<typename T>
T clampVec3(const T& v, const float &min, const float &max)
{
	return T{ clamp(v.x, min, max), clamp(v.y, min, max), clamp(v.z, min, max) };
}