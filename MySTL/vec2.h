#pragma once

#include <iostream>
#include "math3d.h"

struct vec2
{
	float x, y;

	inline vec2() {}

	inline vec2(float x, float y) : x(x), y(y) {}
	inline vec2(float all) : vec2(all, all) {}
	inline vec2(const vec2& copy) : vec2(copy.x, copy.y) {}

	// might wanna implement vector operator* (not a mathematical opertion, but can be useful)
	inline vec2 operator+(const vec2& v) const { return vec2(x + v.x, y + v.y); }
	inline vec2 operator-(const vec2& v) const { return vec2(x - v.x, y - v.y); }

	// same with float operator+
	inline vec2 operator*(float f) const { return vec2(x * f, y * f); }
	inline vec2 operator/(float f) const { return vec2(x / f, y / f); }

	// implemented in source file
	vec2& operator+=(const vec2& v);
	vec2& operator-=(const vec2& v);
	vec2& operator*=(float f);
	vec2& operator/=(float f);

	explicit operator vec3();

	explicit inline operator float* () { return &x; }
	explicit inline operator const float* () const { return &x; }
};

// vector negation
inline vec2 operator-(const vec2& v) { return v * -1; }

inline std::ostream& operator<<(std::ostream& strm, const vec2 &v) {
	return strm << "(" << v.x << "," << v.y << ")";
}

inline float length(const vec2& v) { return std::sqrt(v.x * v.x + v.y * v.y); }

inline vec2 normalize(const vec2& v) { return v / length(v); }

inline float dot(const vec2& l, const vec2& r) { return l.x * r.x + l.y * r.y; }

vec3 cross(const vec2& l, const vec2& r);

vec2 rotate(const vec2& v, float angle);