#pragma once

#include "./Typedefs.hpp"
#include "./BufferLayout.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec4 Color;
};

const static BufferLayoutElement VertexLayout[2] = {
	{ BufferLayoutElementType_Float, 3 },
	{ BufferLayoutElementType_Float, 4 },
};

constexpr u64 VertexLayoutCount = ArrayLength(VertexLayout);
