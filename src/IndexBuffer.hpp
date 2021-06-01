#pragma once

#include "./Typedefs.hpp"

class IndexBuffer {
public:
	IndexBuffer(const u32* indices, u64 count);
	IndexBuffer(const IndexBuffer&) = delete;
	~IndexBuffer();

	void Bind();
	void Unbind();
private:
	u32 ID;
};
