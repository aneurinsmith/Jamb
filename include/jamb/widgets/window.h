
#pragma once
#include "base_widget.h"

namespace Jamb
{
	class JSurface;
	class JWindow : public JBaseWidget
	{
	public:
		JWindow();
		~JWindow();

	protected:
		void render() {}

	private:
		JSurface* m_surface;

	};
}
