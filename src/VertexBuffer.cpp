#include "./VertexBuffer.hpp"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, u64 size) {
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->ID);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
