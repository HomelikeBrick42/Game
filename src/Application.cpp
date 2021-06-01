#include "./Application.hpp"
#include "./Window.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

Application::Application() {
	this->MainWindow = WindowCreate(1280, 720, "Game Window");
	if (!this->MainWindow) {
		throw "Could not create window!"; // TODO: Find some other way to do this
	}

	WindowShow(this->MainWindow, true);

	if (!WindowMakeGLContextCurrent(this->MainWindow)) {
		throw "Could not create OpenGL context!"; // TODO: Find some other way to do this
	}

	{
		GLint majorVersion;
		GLint minorVersion;
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
		printf("OpenGL Version: %d.%d\n", majorVersion, minorVersion);
	}
}

Application::~Application() {
	WindowDestroy(this->MainWindow);
}

void Application::Run() {
	while (!this->MainWindow->ShouldClose) {
		WindowUpdate(this->MainWindow);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->Draw();

		WindowSwapBuffers(this->MainWindow);
	}
}

void Application::Draw() {
}
