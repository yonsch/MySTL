#pragma once

#include <iostream>
#include "vec3.h"

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

	explicit inline operator vec3() { return vec3(x, y, 0); }
};

// vector negation
inline vec2 operator-(const vec2& v) { return v * -1; }

inline std::ostream& operator<<(std::ostream& strm, const vec2 &v) {
	return strm << "(" << v.x << "," << v.y << ")";
}

inline float length(const vec2& v) { return std::sqrt(v.x * v.x + v.y * v.y); }

inline vec2 normalize(const vec2& v) { return v / length(v); }

inline float dot(const vec2& l, const vec2& r) { return l.x * r.x + l.y * r.y; }

inline vec3 cross(const vec2& l, const vec2& r) { return vec3(0, 0, l.x * r.y - l.y * r.x); }

vec2 rotate(const vec2& v, float angle);