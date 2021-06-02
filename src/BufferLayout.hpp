#pragma once

#include "./Typedefs.hpp"

enum BufferLayoutElementType : u32 {
	BufferLayoutElementType_Double,
	BufferLayoutElementType_Float,
	BufferLayoutElementType_Int,
	BufferLayoutElementType_UInt,
	BufferLayoutElementType_Short,
	BufferLayoutElementType_UShort,
	BufferLayoutElementType_Char,
	BufferLayoutElementType_UChar,
};

struct BufferLayoutElement {
	BufferLayoutElementType Type;
	u32 Count;
};
