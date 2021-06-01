#pragma once

#include "./Typedefs.hpp"
#include "./Window.hpp"

#include "./VertexBuffer.hpp"
#include "./IndexBuffer.hpp"
#include "./Shader.hpp"

class Application {
public:
	Application();
	Application(const Application&) = delete;
	~Application();

	void Run();
private:
	void Init();
	void Draw();
private:
	Window MainWindow = nullptr;
	u32 VertexArrayID = 0;
	VertexBuffer* Vertices = nullptr;
	IndexBuffer* Indices = nullptr;
	Shader* FlatColorShader = nullptr;
};
