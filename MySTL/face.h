#pragma once

#include <vector>
#include "vec3.h"

class Face 
{
public:
	vec3 v1, v2, v3, n;

	inline Face() {}
	inline Face(vec3 v1, vec3 v2, vec3 v3,vec3 n) : v1(v1), v2(v2), v3(v3), n(n) {}
	Face(vec3 v1, vec3 v2, vec3 v3);
	
	//std::vector<float> getFloats(); |
	//reimplemented this using a cast V
	explicit operator std::vector<float>() const;
	inline Face operator*(const float& scale) const { return Face(v1 * scale, v2 * scale, v3 * scale, n); }
};

extern std::ostream& operator<<(std::ostream& strm, const Face &a);
