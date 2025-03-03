
#pragma once

namespace Jamb
{
	class JSurface
	{
		friend class JWindow;
	protected:
		static JSurface* create();
	};
}
