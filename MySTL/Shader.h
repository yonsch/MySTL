#pragma once
#include <string>

class Shader
{
	int id;
public:
	Shader();
	Shader(const string& vertex, const string& fragment);
	void bind();
	void unbind();
};

