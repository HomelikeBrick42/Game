#include "./Typedefs.hpp"
#include "./Window.hpp"

#include <glad/glad.h>

#include <cstdio>

int main(int argc, char** argv) {
	Window window = WindowCreate(1280, 720, "Game Window");
	if (!window) {
		printf("Could not create window!\n");
		return -1;
	}

	WindowShow(window, true);

	if (!WindowMakeGLContextCurrent(window)) {
		printf("Could not create OpenGL context!\n");
		return -1;
	}

	{
		GLint majorVersion;
		GLint minorVersion;
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
		printf("OpenGL Version: %d.%d\n", majorVersion, minorVersion);
	}

	while (!window->ShouldClose) {
		WindowUpdate(window);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		WindowSwapBuffers(window);
	}

	WindowDestroy(window);
	return 0;
}
