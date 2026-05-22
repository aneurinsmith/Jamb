
#pragma once
#include <memory>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace Jamb 
{
	class JDrawEvent;

	struct JRect
	{
		int x = 0;
		int y = 0;
		int w = 200;
		int h = 200;

		int left()   const { return x; }
		int top()    const { return y; }
		int right()  const { return x + w; }
		int bottom() const { return y + h; }

		int width()  const { return w; }
		int height() const { return h; }

		void setWidth(int width) { w = width; }
		void setHeight(int height) { h = height; }
	};

	class JBaseWidget
	{
	public:

		JBaseWidget() : m_parent(nullptr) {};
		JBaseWidget(JBaseWidget& parent)
		{
			parent.add_child(*this);
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

	protected:

		JBaseWidget* m_parent;
		std::vector<JBaseWidget*> children;

		JRect region;

		void on_draw(JDrawEvent& jde)
		{
			render(jde);
			for (const auto& child : children) {
				child->on_draw(jde);
			}
		}

		virtual void render(JDrawEvent&) = 0;

	};
}
