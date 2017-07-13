#include "Shader.h"
#include "SDL.h"
#include "glew.h"
#include <string>

using namespace std;

int createShader(const string& shader, int type) {
	int id = glCreateShader(type);

	const char *c_str = shader.c_str();
	glShaderSource(id, 1, &c_str, NULL);
	glCompileShader(id);

	return id;
}

Shader::Shader(const string& vertex, const string& fragment) {
	int vertexID = createShader(vertex, GL_VERTEX_SHADER);
	int fragmentID = createShader(fragment, GL_FRAGMENT_SHADER);

	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);

	glLinkProgram(id);
	glValidateProgram(id);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

void Shader::bind() { glUseProgram(id); }
void Shader::unbind() { glUseProgram(0); }

Shader::Shader() {}
