#include "vec2.h"

using namespace std;

vec2& vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;

	return *this;
}
vec2& vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;

	return *this;
}

vec2& vec2::operator*=(float f) {
	x *= f;
	y *= f;

	return *this;
}
vec2& vec2::operator/=(float f) {
	x /= f;
	y /= f;

	return *this;
}

vec2 rotate(const vec2& v, float angle) {
	float sin = std::sin(angle), cos = std::cos(angle);
	return vec2(cos * v.x - sin * v.y, sin * v.x + cos * v.y);
}

vec3 cross(const vec2& l, const vec2& r) { return vec3(0, 0, l.x * r.y - l.y * r.x); }

vec2::operator vec3() { return vec3(x, y, 0); }