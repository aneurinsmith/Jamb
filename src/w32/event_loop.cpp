
#include "jamb/event_loop.h"
#include "jamb/widgets/window.h"

#include <iostream>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605
#include <Windows.h>
#undef ERROR

namespace Jamb 
{
	std::unordered_map<JWindow*, JEventLoop*> JEventLoop::window_loops;
	LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm)
	{
		JWindow* window = reinterpret_cast<JWindow*>(GetWindowLongPtr(wnd, GWLP_USERDATA));
		JEventLoop* event_loop = JEventLoop::instance().get_loop(window);

		switch (msg) {
			case WM_NCCREATE: {

				JWindow* window = static_cast<JWindow*>(reinterpret_cast<LPCREATESTRUCT>(lpm)->lpCreateParams);
				SetWindowLongPtr(wnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

				break;
			}
		}

		if (event_loop && window) {
			JEvent je;
			je.window = window;
			event_loop->send_message(je);
		}

		return DefWindowProcA(wnd, msg, wpm, lpm);
	}

	void JEventLoop::send_message(JEvent je)
	{
		je.window->on_size(1,1);
	}

	JEventLoop::JEventLoop() : is_running(true) {}

	bool JEventLoop::run()
	{
		MSG msg;
		while (is_running) {
			GetMessageA(&msg, NULL, 0, 0);
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		return is_running;
	}
	void JEventLoop::stop()
	{
		is_running = false;
	}
}
