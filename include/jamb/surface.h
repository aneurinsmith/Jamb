
#pragma once
#include <stdexcept>

namespace Jamb
{
	class JWindow;
	class JSurface
	{
		friend class JWindow;
	protected:
		static JSurface* create();

		virtual void init() = 0;

		JWindow* m_window;

	};
}
