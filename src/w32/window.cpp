
#include "jamb/widgets/window.h"
#include "jamb/event_loop.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605
#include <windows.h>
#include <unordered_map>

namespace Jamb 
{
	LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm);

	JWindow::JWindow()
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

			if (!RegisterClassExA(&wcea)) {
				throw std::runtime_error("Window class failed to register");
			}
		}

		JEventLoop::instance().register_window(this);
		HWND handle = CreateWindowExA(0,
			"Jamb", "JambWindow",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_VSCROLL,
			CW_USEDEFAULT, CW_USEDEFAULT,
			800, 400,
			0, (HMENU)0, GetModuleHandleA(NULL), (void*)this);
		if (!handle) {
			throw std::runtime_error("Window creation failed");
		}
	}
}
