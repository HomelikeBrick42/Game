#pragma once

#include "./Typedefs.hpp"
#include "./Window.hpp"

class Application {
public:
	Application();
	~Application();

	void Run();
private:
	void Draw();
private:
	Window MainWindow;
};
