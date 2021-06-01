#include "./Typedefs.hpp"
#include "./Window.hpp"

#include <glad/glad.h>

#include <cstdio>

int main(int argc, char** argv) {
	Window window = WindowCreate(1280, 720, "Game Window");
	WindowShow(window, true);

	while (!window->ShouldClose) {
		WindowUpdate(window);
	}

	WindowDestroy(window);
	return 0;
}
