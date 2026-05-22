
#include "jamb/events/event_loop.h"
#include "jamb/widgets/window.h"

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

				JCreateEvent* jce = new JCreateEvent(window, 1, 1);
				window->eventLoop->pushEvent(jce);
				return true;
			}
			case WM_NCDESTROY:
			{
				JDestroyEvent* jde = new JDestroyEvent(window);
				window->eventLoop->pushEvent(jde);
				break;
			}
			case WM_SIZE:
			{
				JSizeEvent* jse = new JSizeEvent(window, LOWORD(lpm), HIWORD(lpm));
				window->eventLoop->pushEvent(jse);
				window->eventLoop->procEvents();
				break;
			}
			case WM_PAINT:
			{
				JDrawEvent* jde = new JDrawEvent(window, 1, 1);
				window->eventLoop->pushEvent(jde);
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
