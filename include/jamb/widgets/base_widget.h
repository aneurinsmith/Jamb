
#ifdef win32
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#define WINVER 0x0605
	#include <Windows.h>
	#undef ERROR
#elif libx11
	#include <X11/Xlib.h>
	#include <X11/extensions/Xrandr.h>
	#include <X11/Xutil.h>
	#include <X11/Xatom.h>
	#include <X11/Xft/Xft.h>
#endif

namespace Jamb 
{
	struct JRect
	{
		int left = 0, 
			top = 0, 
			right = 0, 
			bottom = 0;

		int width()
		{
			return right - left;
		}
		int height()
		{
			return bottom - top;
		}
	};

	class BaseWidget
	{
	protected:

		void* handle;
		void* parent;
		bool is_fullscreen;

		JRect region;
	};
}
