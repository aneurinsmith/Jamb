
#include "jamb/surface.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605
#include <windows.h>
#include <windowsx.h>
#include <uxtheme.h>
#undef ERROR

#include <unordered_map>

namespace Jamb
{
	class JW32Surface : public JSurface
	{
	protected:
		void init();

	private:
		static std::unordered_map<HWND, JWindow*> window_data;
		static LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm);
		HWND m_handle;
	};

	std::unordered_map<HWND, JWindow*> JW32Surface::window_data;

	JSurface* JSurface::create()
	{
		return new JW32Surface();
	}

	void JW32Surface::init()
	{
		WNDCLASSEXA wcea = {};

		if (!GetClassInfoExA(GetModuleHandleA(0), "Jamb", &wcea)) {
			wcea.cbSize = sizeof(wcea);
			wcea.lpfnWndProc = (WNDPROC)HandleMessage;
			wcea.cbClsExtra = 0;
			wcea.cbWndExtra = 0;
			wcea.hInstance = GetModuleHandleA(0);
			wcea.hCursor = LoadCursor(NULL, IDC_ARROW);
			wcea.lpszClassName = "Jamb";
			wcea.style = CS_BYTEALIGNWINDOW | CS_DBLCLKS;

			if (!RegisterClassExA(&wcea)) {
				throw std::runtime_error("Window class failed to register");
			}
		}

		m_handle = CreateWindowExA(0,
			"Jamb", "Jamb",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			0, 0, 600, 400,
			0, (HMENU)0, GetModuleHandleA(0), (void*)m_window);
		window_data[m_handle] = m_window;

		if (!m_handle) {
			throw std::runtime_error("Window creation failed");
		}
	}



	LRESULT CALLBACK JW32Surface::HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm)
	{
		JWindow* data = JW32Surface::window_data[wnd];

		switch(msg)
		{
			case WM_NCCREATE: {
				data = static_cast<JWindow*>(reinterpret_cast<LPCREATESTRUCT>(lpm)->lpCreateParams);
				window_data[wnd] = data;
				break;
			}
		}

		return DefWindowProcA(wnd, msg, wpm, lpm);
	}
}


