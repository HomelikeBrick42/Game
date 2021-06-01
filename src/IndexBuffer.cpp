#include "./IndexBuffer.hpp"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const u32* indices, u64 count) {
	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &this->ID);
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ID);
}

void IndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
