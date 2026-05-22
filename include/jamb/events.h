
namespace Jamb
{
	class JWindow;


	class JEvent
	{
		friend class JEventLoop;
	public:
		JEvent() {}
		JEvent(JWindow* w)
			: window(w) {}

		JWindow* window;

	protected:
		virtual void dispatch() = 0;
	};


	class JDestroyEvent : public JEvent
	{
	public:
		JDestroyEvent() {}
		JDestroyEvent(JWindow* w)
			: JEvent(w) {}

	protected:
		void dispatch();
	};


	class JDisplayEvent : public JEvent
	{
	public:
		JDisplayEvent() {}
		JDisplayEvent(JWindow* w)
			: JEvent(w) {}

	protected:
		void dispatch();
	};


	class JDrawEvent : public JEvent
	{
	public:
		JDrawEvent() {}
		JDrawEvent(JWindow* w)
			: JEvent(w) {}

	protected:
		void dispatch();
	};


	class JSizeEvent : public JEvent
	{
	public:
		JSizeEvent() {}
		JSizeEvent(JWindow* w, int width, int height)
			: JEvent(w), width(width), height(height) {}

		int width;
		int height;

	protected:
		void dispatch();
	};


	class JCreateEvent : public JSizeEvent
	{
	public:
		JCreateEvent() {}
		JCreateEvent(JWindow* w, int width, int height)
			: JSizeEvent(w, width, height) {}

	protected:
		void dispatch();
	};
}