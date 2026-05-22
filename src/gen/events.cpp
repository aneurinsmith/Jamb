
#include "jamb/event_loop.h"
#include "jamb/widgets/window.h"

namespace Jamb 
{
	void JCreateEvent::dispatch()
	{
		window->on_create(*this);
	}

	void JDestroyEvent::dispatch()
	{
		window->eventLoop->stop();
		window->on_destroy(*this);
	}

	void JDisplayEvent::dispatch()
	{
		window->show();
		window->on_display(*this);
	}

	void JDrawEvent::dispatch()
	{
		window->on_draw(*this);
	}

	void JSizeEvent::dispatch()
	{
		window->region.w = width;
		window->region.h = height;

		window->on_size(*this);
	}
}
