#include "./VertexBuffer.hpp"

#include <glad/glad.h>

static u64 GetElementSize(BufferLayoutElement element) {
	switch (element.Type) {
		case BufferLayoutElementType_Double: {
			return sizeof(f64) * element.Count;
		} break;

		case BufferLayoutElementType_Float: {
			return sizeof(f32) * element.Count;
		} break;

		case BufferLayoutElementType_Int: {
			return sizeof(s32) * element.Count;
		} break;

		case BufferLayoutElementType_UInt: {
			return sizeof(u32) * element.Count;
		} break;

		case BufferLayoutElementType_Short: {
			return sizeof(s16) * element.Count;
		} break;

		case BufferLayoutElementType_UShort: {
			return sizeof(u16) * element.Count;
		} break;

		case BufferLayoutElementType_Char: {
			return sizeof(s8) * element.Count;
		} break;

		case BufferLayoutElementType_UChar: {
			return sizeof(u8) * element.Count;
		} break;

		default: {
			ASSERT(false);
		} break;
	}
}

static GLenum LayoutTypeToGLType(BufferLayoutElementType type) {
	switch (type) {
		case BufferLayoutElementType_Double: {
			return GL_DOUBLE;
		} break;

		case BufferLayoutElementType_Float: {
			return GL_FLOAT;
		} break;

		case BufferLayoutElementType_Int: {
			return GL_INT;
		} break;

		case BufferLayoutElementType_UInt: {
			return GL_UNSIGNED_INT;
		} break;

		case BufferLayoutElementType_Short: {
			return GL_SHORT;
		} break;

		case BufferLayoutElementType_UShort: {
			return GL_UNSIGNED_SHORT;
		} break;

		case BufferLayoutElementType_Char: {
			return GL_BYTE;
		} break;

		case BufferLayoutElementType_UChar: {
			return GL_UNSIGNED_BYTE;
		} break;

		default: {
			ASSERT(false);
		} break;
	}
}

VertexBuffer::VertexBuffer(const void* data, u64 size, const BufferLayoutElement* layout, u64 layoutCount) {
	glGenVertexArrays(1, &this->VertexArrayID);
	glBindVertexArray(this->VertexArrayID);

	glGenBuffers(1, &this->ID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	u64 stride = 0;
	for (u64 i = 0; i < layoutCount; i++) {
		stride += GetElementSize(layout[i]);
	}

	u64 offset = 0;
	for (u64 i = 0; i < layoutCount; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(
			i,
			layout[i].Count,
			LayoutTypeToGLType(layout[i].Type),
			GL_FALSE,
			stride,
			cast(const void*) offset
		);
		offset += GetElementSize(layout[i]);
	}
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->ID);
	glDeleteVertexArrays(1, &this->VertexArrayID);
}

void VertexBuffer::Bind() {
	glBindVertexArray(this->VertexArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VertexBuffer::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
