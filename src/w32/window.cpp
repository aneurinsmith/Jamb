
#include "jamb/surface.h"
#include "jamb/widgets/window.h"

namespace Jamb 
{
	JWindow::JWindow()
	{
		m_surface = JSurface::create();
		m_surface->m_window = this;
		m_surface->init();
	}

	JWindow::~JWindow()
	{
		delete m_surface;
	}
}
