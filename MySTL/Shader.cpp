#include "Shader.h"
#include "SDL.h"
#include "glew.h"


Shader::Shader()
{
}


Shader::~Shader()
{
}

int createShader(const char* shader, int type) {
	int id = glCreateShader(type);

	glShaderSource(id, shader);
	glCompileShader(id);

	return id;
}

Shader::Shader(const char* vertex, const char* fragment) {
	int vertexID = createShader(vertex, GL_VERTEX_SHADER);
	int fragmentID = createShader(fragment, GL_FRAGMENT_SHADER);

	glAttachShader(id, vertexID);
	glAttachShader(id, fragmentID);

	glLinkProgram(id);
	glValidateProgram(id);

	System.err.println(glGetProgramInfoLog(id));

	uniforms = vs.getUniforms(id);
	uniforms.putAll(fs.getUniforms(id));

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

Shader::bind() { glUseProgram(id); }
Shader::unbind() { glUseProgram(0); }