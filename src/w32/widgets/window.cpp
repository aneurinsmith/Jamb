
#include "jamb/widgets/window.h"
#include "jamb/event_loop.h"

#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605

#include <windows.h>
#include <unordered_map>

namespace Jamb 
{
	struct JWindow::NativeWindowHandle
	{
		HWND hwnd;
	};

	LRESULT CALLBACK HandleMessage(HWND, UINT, WPARAM, LPARAM);

	void JWindow::init()
	{
		WNDCLASSEXA wcea = {};

		if (!GetClassInfoExA(GetModuleHandleA(NULL), "Jamb", &wcea)) {
			wcea.cbSize = sizeof(WNDCLASSEXA);
			wcea.lpfnWndProc = HandleMessage;
			wcea.cbClsExtra = 0;
			wcea.cbWndExtra = 0;
			wcea.hInstance = GetModuleHandleA(NULL);
			wcea.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcea.lpszClassName = "Jamb";
			wcea.style = CS_BYTEALIGNWINDOW | CS_DBLCLKS;

			if (!RegisterClassExA(&wcea))
				throw std::runtime_error("Window class failed to register");
		}

		if (!handle->hwnd)
		{
			handle->hwnd = CreateWindowExA(0,
				"Jamb", "JambWindow",
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				region.w, region.h,
				0, (HMENU)0, GetModuleHandleA(NULL), (void*)this);

			eventLoop->procEvents();

			if (!handle->hwnd)
				throw std::runtime_error("Window creation failed");
		}
	}

	void JWindow::hide()
	{
		ShowWindow(handle->hwnd, false);
	}
	void JWindow::show()
	{
		ShowWindow(handle->hwnd, true);
	}
}
