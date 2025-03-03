
#pragma once
#include "base_widget.h"
#include "jamb/surface.h"

namespace Jamb
{
	class JWindow : public JBaseWidget
	{
	public:
		JWindow();
		~JWindow();

	protected:
		virtual void on_size() {}
		virtual void render() {}

		JSurface* m_surface;

	};
}
