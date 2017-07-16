#pragma once

#include <iostream>
#include "math3d.h"

struct vec3
{
	float x, y, z;

	inline vec3() {}

	inline vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	inline vec3(float all) : vec3(all, all, all) {}
	inline vec3(const vec3& copy) : vec3(copy.x, copy.y, copy.z) {}

	// might wanna implement vector operator* (not a mathematical opertion, but can be useful)
	inline vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }
	inline vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }

	// same with float operator+
	inline vec3 operator*(float f) const { return vec3(x * f, y * f, z * f); }
	inline vec3 operator/(float f) const { return vec3(x / f, y / f, z / f); }

	// implemented in source file
	vec3& operator+=(const vec3& v);
	vec3& operator-=(const vec3& v);
	vec3& operator*=(float f);
	vec3& operator/=(float f);

	vec3 rotate(const quaternion& rotation) const;
	vec3 rotate(const vec3& axis, float angle) const;

	// basic axes vectors, defined in source file
	static const vec3 RIGHT;
	static const vec3 LEFT;
	static const vec3 UP;
	static const vec3 DOWN;
	static const vec3 FORWARD;
	static const vec3 BACK;

	explicit inline operator float* () { return &x; }
	explicit inline operator const float* () const { return &x; }
};

// vector negation
inline vec3 operator-(const vec3& v) { return v * -1; }

inline std::ostream& operator<<(std::ostream& strm, const vec3 &v) {
	return strm << "(" << v.x << "," << v.y << "," << v.z << ")";
}

inline float length(const vec3& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

inline vec3 normalize(const vec3& v) { return v / length(v); }

inline float dot(const vec3& l, const vec3& r) { return l.x * r.x + l.y * r.y + l.z * r.z; }

//implemented in source file
vec3 cross(const vec3& l, const vec3& r);