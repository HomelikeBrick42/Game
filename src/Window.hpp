#pragma once

#include "./Typedefs.hpp"

typedef struct Window_t {
	const volatile b8 ShouldClose;
	const volatile u32 Width;
	const volatile u32 Height;
} *Window;

Window WindowCreate(u32 width, u32 height, const char* title);
void WindowDestroy(Window window);

void WindowShow(Window window, b8 show);
void WindowUpdate(Window window);

b8 WindowMakeGLContextCurrent(Window window);
void WindowSwapBuffers(Window window);
