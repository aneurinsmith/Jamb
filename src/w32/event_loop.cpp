
#include "jamb/event_loop.h"
#include "jamb/widgets/window.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605
#include <Windows.h>
#undef ERROR

namespace Jamb
{
	LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm)
	{
		JWindow* window = reinterpret_cast<JWindow*>(GetWindowLongPtr(wnd, GWLP_USERDATA));

		switch (msg)
		{
			case WM_NCCREATE:
			{
				JWindow* window = static_cast<JWindow*>(reinterpret_cast<LPCREATESTRUCT>(lpm)->lpCreateParams);
				SetWindowLongPtr(wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

				window->eventLoop->pushEvent(new JCreateEvent{ window, 1, 1 });
				window->eventLoop->procEvents();
				return true;
			}
			case WM_NCDESTROY:
			{
				window->eventLoop->pushEvent(new JDestroyEvent{ window });
				break;
			}
			case WM_SIZE:
			{
				window->eventLoop->pushEvent(new JSizeEvent{ window, LOWORD(lpm), HIWORD(lpm) });
				window->eventLoop->procEvents();
				break;
			}
		}

		return DefWindowProcA(wnd, msg, wpm, lpm);
	}

	void JEventLoop::pumpEvents()
	{
		MSG msg;

		while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}
