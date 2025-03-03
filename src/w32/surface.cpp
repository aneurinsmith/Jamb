
#include "../gen/surface.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define WINVER 0x0605
#include <windows.h>
#include <windowsx.h>
#undef ERROR

#include <cstdint>
#include <stdexcept>

namespace Jamb 
{
	class JW32Surface : public JSurface
	{
	public:
		JW32Surface();
	protected:
		HWND m_handle;

		static LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm);
	};

	JSurface* JSurface::create()
	{
		return new JW32Surface();
	}

	LRESULT CALLBACK JW32Surface::HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm)
	{
		return DefWindowProcA(wnd, msg, wpm, lpm);
	}

	JW32Surface::JW32Surface()
	{
		WNDCLASSEXA wcea = {};

		if (!GetClassInfoExA(GetModuleHandleA(0), "Jamb", &wcea)) {
			wcea.cbSize = sizeof(wcea);
			wcea.lpfnWndProc = HandleMessage;
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
			0, (HMENU)0, GetModuleHandleA(0), (JSurface*)this);

		if (!m_handle) {
			throw std::runtime_error("Window creation failed");
		}
	}

}
