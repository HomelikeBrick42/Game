#pragma once

#include "./Typedefs.hpp"
#include "./String.hpp"

class Shader {
public:
	Shader(String vertexSource, String fragmentSource);
	Shader(const Shader&) = delete;
	~Shader();

	void Bind();
	void Unbind();
private:
	u32 CreateShader(String source, u32 type);
private:
	u32 ID;
};
