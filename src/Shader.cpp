#include "./Shader.hpp"

#include <glad/glad.h>

#include <cstdio>
#include <cstdlib>

Shader::Shader(String vertexSource, String fragmentSource) {
	u32 vertexShader = this->CreateShader(vertexSource, GL_VERTEX_SHADER);
	u32 fragmentShader = this->CreateShader(fragmentSource, GL_FRAGMENT_SHADER);

	if (vertexShader != 0 && fragmentShader != 0) {
		this->ID = glCreateProgram();

		glAttachShader(this->ID, vertexShader);
		glAttachShader(this->ID, fragmentShader);

		glLinkProgram(this->ID);

		s32 isLinked = 0;
		glGetProgramiv(this->ID, GL_LINK_STATUS, &isLinked);
		if (!isLinked) {
			s32 maxLength = 0;
			glGetProgramiv(this->ID, GL_INFO_LOG_LENGTH, &maxLength);
			GLchar* error = cast(GLchar*) malloc(maxLength * sizeof(GLchar));

			glGetProgramInfoLog(this->ID, maxLength, &maxLength, error);
			printf("%s\n", error);

			glDeleteProgram(this->ID);
			free(error);
			return;
		}

		glDetachShader(this->ID, vertexShader);
		glDeleteShader(vertexShader);
		glDetachShader(this->ID, fragmentShader);
		glDeleteShader(fragmentShader);
	}
}

Shader::~Shader() {
	glDeleteProgram(this->ID);
}

void Shader::Bind() {
	glUseProgram(this->ID);
}

void Shader::Unbind() {
	glUseProgram(0);
}

u32 Shader::CreateShader(String source, u32 type) {
	u32 shader = glCreateShader(type);
	glShaderSource(shader, 1, cast(GLchar**) &source.Data, cast(s32*) &source.Length);

	glCompileShader(shader);

	s32 isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (!isCompiled) {
		s32 maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		GLchar* error = cast(GLchar*) malloc(maxLength * sizeof(GLchar));

		glGetShaderInfoLog(shader, maxLength, &maxLength, error);
		printf("%s\n", error);

		glDeleteShader(shader);
		free(error);
		return 0;
	}

	return shader;
}
