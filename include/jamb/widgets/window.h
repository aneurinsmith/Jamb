
#pragma once
#include "base_widget.h"

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

	};
}
