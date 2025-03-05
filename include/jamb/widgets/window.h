
#pragma once
#include "base_widget.h"
#include "jamb/event_loop.h"

namespace Jamb
{
	class JWindow : public JBaseWidget
	{
		friend class JEventLoop;
	public:
		JWindow();

	protected:
		virtual void on_size(int width, int height) {}
		virtual void on_destroy() {}

		virtual void render() {}

	};
}
