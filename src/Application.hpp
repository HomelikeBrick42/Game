#pragma once

#include "./Typedefs.hpp"
#include "./Window.hpp"

class Application {
public:
	Application();
	~Application();

	void Run();
private:
	void Init();
	void Draw();
private:
	Window MainWindow;
	u32 VertexArrayID;
	u32 VertexBufferID;
	u32 IndexBufferID;
};
