
#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

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

	class JBaseWidget
	{
	public:
		JBaseWidget() : m_parent(nullptr) {};
		JBaseWidget(JBaseWidget& parent)
		{
			parent.add_child(*this);
		}

		bool add_child(JBaseWidget& child)
		{
			if (child.get_parent()) {
				return false;
			}
			else {
				const JBaseWidget* current = this;
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



		const JBaseWidget* get_parent() const
		{
			return m_parent;
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

		JBaseWidget* m_parent;
		std::vector<JBaseWidget*> children;

		JRect region;

		void on_draw()
		{
			render();
			for (const auto& child : children) {
				child->on_draw();
			}
		}

		virtual void render() = 0;

	};
}
