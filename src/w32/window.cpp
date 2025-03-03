
#include "../gen/surface.h"
#include "jamb/widgets/window.h"

namespace Jamb 
{
	class JW32Window : public JWindow
	{
		int i;
	};

	JWindow::JWindow()
	{
		m_surface = JSurface::create();
	}

	JWindow::~JWindow()
	{

	}
}
