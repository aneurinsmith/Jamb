
#pragma once
#include "base_widget.h"
#include "jamb/event_loop.h"

namespace Jamb
{
	typedef uintptr_t JHandle;

	class JWindow : public JBaseWidget
	{
		friend class JEventLoop;
		friend class JRenderer;

		friend class JCreateEvent;
		friend class JSizeEvent;
		friend class JDrawEvent;
		friend class JDestroyEvent;
		friend class JDisplayEvent;

	public:

		void init();
		void hide();
		void show();

		//void resize(uint32_t width, uint32_t height);
		
		void maximize();
		void minimize();
		void restore();

		JEventLoop* const eventLoop = &JEventLoop::thread_instance();

	protected:

		struct NativeWindowHandle;
		NativeWindowHandle* handle;

		virtual void on_display(JDisplayEvent&) {}
		virtual void on_create(JCreateEvent&) {}
		virtual void on_size(JSizeEvent&) {}
		virtual void on_destroy(JDestroyEvent&) {}

		virtual void render(JDrawEvent&) {}
	};

	template<typename T>
	inline T* create_window()
	{
		static_assert(
			std::is_base_of<JWindow, T>::value,
			"T must derive from JWindow");

		T* jwin = new T();
		jwin->init();
		return jwin;
	}
}
