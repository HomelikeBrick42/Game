#pragma once

#include "./Typedefs.hpp"

class VertexBuffer {
public:
	VertexBuffer(const void* data, u64 size); // TODO: Layout
	VertexBuffer(const VertexBuffer&) = delete;
	~VertexBuffer();

	void Bind();
	void Unbind();
private:
	u32 ID;
};
