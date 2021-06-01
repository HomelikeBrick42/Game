#include "./Window.hpp"

#if defined(_WIN32) || defined(_WIN64)

#include <Windows.h>

typedef struct WindowData_t {
	HINSTANCE Instance;
	HWND WindowHandle;
	HDC DeviceContext;
	HGLRC GLContext;
} *WindowData;

constexpr const char* WindowClassName = "GameWindowClass"; // TODO: Make a better name
static b8 WindowClassCreated = false;

LRESULT CALLBACK WindowMessageCallback(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;

	Window window = cast(Window) GetWindowLongPtrA(windowHandle, GWLP_USERDATA);
	if (window) {
		WindowData data = cast(WindowData) (cast(u8*) window + sizeof(Window_t));

		switch (message) {
		case WM_CLOSE:
		case WM_QUIT: {
			*(cast(b8*) & window->ShouldClose) = true;
		} break;

		case WM_SIZE: {
			RECT clientRect;
			GetClientRect(data->WindowHandle, &clientRect);
			s32 windowWidth = clientRect.right - clientRect.left;
			s32 windowHeight = clientRect.bottom - clientRect.top;

			if (windowWidth > 0 && windowHeight > 0) {
				*(cast(u32*) & window->Width) = cast(u32) windowWidth;
				*(cast(u32*) & window->Height) = cast(u32) windowHeight;
			}
		} break;

		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		case WM_KEYDOWN:
		case WM_KEYUP: {
			// TODO: Key press event
			result = DefWindowProcA(data->WindowHandle, message, wParam, lParam); // Do default stuff e.g. alt+f4
		} break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP: {
			// TODO: Mouse button event
		} break;

		default: {
			result = DefWindowProcA(data->WindowHandle, message, wParam, lParam);
		} break;
		}
	}
	else {
		result = DefWindowProcA(windowHandle, message, wParam, lParam);
	}

	return result;
}

Window WindowCreate(u32 width, u32 height, const char* title) {
	constexpr DWORD Style = WS_OVERLAPPEDWINDOW;

	Window window = cast(Window) calloc(1, sizeof(Window_t) + sizeof(WindowData_t));
	*(cast(u32*) & window->Width) = width;
	*(cast(u32*) & window->Height) = height;

	WindowData data = cast(WindowData) (cast(u8*) window + sizeof(Window_t));

	data->Instance = GetModuleHandle(nullptr);

	RECT windowRect = {};
	windowRect.left = 100;
	windowRect.right = windowRect.left + width;
	windowRect.top = 100;
	windowRect.bottom = windowRect.top + height;
	AdjustWindowRect(&windowRect, Style, false);

	u32 windowWidth = windowRect.right - windowRect.left;
	u32 windowHeight = windowRect.bottom - windowRect.top;

	if (!WindowClassCreated) {
		WNDCLASSEXA windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEXA);
		windowClass.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		windowClass.hInstance = data->Instance;
		windowClass.lpszClassName = WindowClassName;
		windowClass.lpfnWndProc = &WindowMessageCallback;
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		if (!RegisterClassExA(&windowClass)) {
			WindowDestroy(window);
			return nullptr;
		}

		WindowClassCreated = true;
	}

	data->WindowHandle = CreateWindowExA(
		0,
		WindowClassName,
		title,
		Style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowWidth,
		windowHeight,
		nullptr,
		nullptr,
		data->Instance,
		nullptr
	);

	if (!data->WindowHandle) {
		free(window);
		return nullptr;
	}

	SetWindowLongPtrA(data->WindowHandle, GWLP_USERDATA, cast(LONG_PTR) window);

	data->DeviceContext = GetDC(data->WindowHandle);

	if (!data->DeviceContext) {
		WindowDestroy(window);
		return nullptr;
	}

	return window;
}

void WindowDestroy(Window window) {
	WindowData data = cast(WindowData) (cast(u8*) window + sizeof(Window_t));

	if (data->DeviceContext) {
		ReleaseDC(data->WindowHandle, data->DeviceContext);
	}

	if (data->WindowHandle) {
		DestroyWindow(data->WindowHandle);
	}

	free(window);
}

void WindowShow(Window window, b8 show) {
	WindowData data = cast(WindowData) (cast(u8*) window + sizeof(Window_t));
	ShowWindow(data->WindowHandle, show ? SW_SHOW : SW_HIDE);
}

void WindowUpdate(Window window) {
	WindowData data = cast(WindowData) (cast(u8*) window + sizeof(Window_t));

	MSG message;
	while (PeekMessageA(&message, data->WindowHandle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
}

#else
	#error Not implemented on this platform!
#endif
