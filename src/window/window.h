
#include "widgets/base_widget.h"

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
	class Window : BaseWidget
	{

	};
}
