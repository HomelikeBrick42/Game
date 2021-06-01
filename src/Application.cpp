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

	this->Init();
}

Application::~Application() {
	if (this->Vertices) {
		delete this->Vertices;
	}

	WindowDestroy(this->MainWindow);
}

void Application::Run() {
	while (!this->MainWindow->ShouldClose) {
		WindowUpdate(this->MainWindow);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		this->Draw();

		WindowSwapBuffers(this->MainWindow);
	}
}

void Application::Init() {
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glm::vec3 vertices[3] = {
		{  0.0f,  0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f }
	};

	this->Vertices = new VertexBuffer(vertices, sizeof(vertices));

	glGenBuffers(1, &IndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBufferID);

	u32 indices[3] = {
		0, 1, 2
	};

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), cast(const void*) 0);
}

void Application::Draw() {
	glBindVertexArray(VertexArrayID);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
