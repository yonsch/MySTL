#pragma once

#include <string>
#include <vector>
#include "face.h"
#include "vec3.h"

typedef unsigned char byte;

class STLMesh
{
public:
	std::string header;
	int triCount;
	std::vector<Face> faces;

	inline STLMesh() {}
	inline STLMesh(std::vector<Face> f, std::string h) : header(h), faces(f), triCount(f.size()) {}

	STLMesh(std::string fileName);

	void toFile(std::string fileName) const;

	STLMesh operator* (const float& scale);

	static std::vector<Face> pyramid(std::vector<vec3>);
	static std::vector<Face> prism(std::vector<vec3>, vec3);
	static std::vector<Face> revolve(std::vector<vec3>, float);
	static std::vector<vec3> curve(float, float, int, bool, bool, float(*)(float));
};
