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

	glViewport(0, 0, this->MainWindow->Width, this->MainWindow->Height);

	this->Init();
}

Application::~Application() {
	delete this->FlatColorShader;
	glDeleteVertexArrays(1, &VertexArrayID);
	delete this->Vertices;
	delete this->Indices;

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
	glGenVertexArrays(1, &VertexArrayID); // TODO: Move to vertex buffer
	glBindVertexArray(VertexArrayID);

	struct Vertex {
		glm::vec3 Position;
		glm::vec4 Color;
	};

	Vertex vertices[3] = {
		{ {  0.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
		{ {  0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } },
		{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
	};
	this->Vertices = new VertexBuffer(vertices, sizeof(vertices));

	u32 indices[3] = {
		0, 1, 2,
	};
	this->Indices = new IndexBuffer(indices, 3);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), cast(const void*) (0 * sizeof(f32)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(f32), cast(const void*) (3 * sizeof(f32)));

	String vertexSource = StringFromLiteral(R"(
#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

layout(location = 0) out vec4 v_Color;

void main() {
	gl_Position = a_Position;
	v_Color = a_Color;
}
)");

	String fragmentSource = StringFromLiteral(R"(
#version 450 core

layout(location = 0) out vec4 o_Color;

layout(location = 0) in vec4 v_Color;

void main() {
	o_Color = v_Color;
}
)");

	this->FlatColorShader = new Shader(vertexSource, fragmentSource);
}

void Application::Draw() {
	glBindVertexArray(VertexArrayID);
	this->Vertices->Bind();
	this->Indices->Bind();
	this->FlatColorShader->Bind();
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}
