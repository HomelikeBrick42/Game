#pragma once

#include "./Typedefs.hpp"
#include "./BufferLayout.hpp"

class VertexBuffer {
public:
	VertexBuffer(const void* data, u64 size, const BufferLayoutElement* layout,u64 layoutCount);
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	u32 VertexArrayID;
	u32 ID;
};
