
#pragma once
#include <unordered_map>
#include <memory>

namespace Jamb 
{
	class JWindow;

	class JEvent
	{
	public:
		JWindow* window;
	};

	class JEventLoop
	{
	public:

		static JEventLoop& instance()
		{
			static JEventLoop instance;
			return instance;
		}

		bool run();
		void stop();

		JEvent get_message();
		void send_message(JEvent);

		void register_window(JWindow* window)
		{
			window_loops[window] = this;
		}

		JEventLoop* get_loop(JWindow* window)
		{
			return window_loops[window];
		}

	protected:
		JEventLoop();

	private:
		bool is_running;
		static std::unordered_map<JWindow*, JEventLoop*> window_loops;
	};

	inline bool run_loop()
	{
		return Jamb::JEventLoop::instance().run();
	}

	inline void stop_loop()
	{
		Jamb::JEventLoop::instance().stop();
	}
}
