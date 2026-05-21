
#pragma once

#include <jamb/events.h>

#include <unordered_map>
#include <memory>
#include <algorithm>
#include <thread>
#include <mutex>
#include <queue>
#include <functional>

namespace Jamb 
{
	class JEventLoop
	{
	public:

		static JEventLoop& thread_instance()
		{
			thread_local JEventLoop instance;
			return instance;
		}

		void pushEvent(JEvent* je)
		{
			std::lock_guard<std::mutex> lock(queueMutex);
			queue.push(je);
		}

		int run()
		{
			is_running = true;

			while (is_running)
			{
				pumpEvents();
				procEvents();
			}

			return is_running + queue.size();
		}

		void stop()
		{
			is_running = false;
		}

		void procEvents()
		{
			while (true)
			{
				JEvent* je = nullptr;
				{
					std::lock_guard<std::mutex> lock(queueMutex);
					if (queue.empty()) {
						break;
					}
					je = queue.front();
					queue.pop();
				}

				if (je) {
					je->dispatch();
				}
			}
		}

	private:

		void pumpEvents();

		bool is_running;

		std::queue<JEvent*> queue;
		std::mutex queueMutex;
	};

	inline int run_loop()
	{
		return Jamb::JEventLoop::thread_instance().run();
	}

	inline void stop_loop()
	{
		Jamb::JEventLoop::thread_instance().stop();
	}
}
