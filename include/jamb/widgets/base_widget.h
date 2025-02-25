
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

namespace Jamb 
{
	struct JRect
	{
		int left = 0, 
			top = 0, 
			right = 0, 
			bottom = 0;

		int width()
		{
			return right - left;
		}
		int height()
		{
			return bottom - top;
		}
	};

	class BaseWidget
	{
	public:
		BaseWidget() : m_parent(nullptr) {};
		BaseWidget(BaseWidget& parent)
		{
			parent.add_child(*this);
		}

		BaseWidget& get_parent()
		{
			return *m_parent;
		}

		bool add_child(BaseWidget& child)
		{
			if (&child.get_parent()) {
				return false;
			}
			else {
				const BaseWidget* current = this;
				while (current != nullptr) {
					if (current == &child) {
						return false;
					}
					current = current->m_parent;
				}
			}

			child.m_parent = this;
			children.push_back(&child);
			return true;
		}

		void render()
		{
			on_draw();
			for (const auto& child : children) {
				child->render();
			}
		}

		int get_width()
		{
			return region.width();
		}

		int get_height()
		{
			return region.height();
		}

	protected:

		void* m_handle;

		BaseWidget* m_parent;
		std::vector<BaseWidget*> children;

		JRect region;


		virtual void on_draw() = 0;

	};
}
