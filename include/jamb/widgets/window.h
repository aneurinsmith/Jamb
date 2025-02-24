
#include "base_widget.h"
#include <thread>

namespace Jamb 
{
	class Window : public BaseWidget
	{
	public:
		Window();

		// Window methods
		void display();
		void maximize();
		void minimize();
		void restore();
		void resize();

	private:

		void init();

	#ifdef win32
		static LRESULT CALLBACK HandleMessage(HWND wnd, UINT msg, WPARAM wpm, LPARAM lpm);
	#elif libx11
		static void HandleMessage(XEvent* xe, void* _data);
	#endif

	};
}
