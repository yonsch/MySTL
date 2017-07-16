#pragma once

#include <string>

class Shader
{
	unsigned int id = 0;
public:
	inline Shader() {}
	Shader(const std::string& vertex, const std::string& fragment);
	void bind();
	void unbind();
};
