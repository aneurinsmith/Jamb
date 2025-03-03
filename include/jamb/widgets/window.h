
#pragma once
#include "base_widget.h"

namespace Jamb
{
	class JWindow : public JBaseWidget
	{
		friend JEventLoop;
	protected:
		virtual void render(JContext* ctx) {}
	};
}
