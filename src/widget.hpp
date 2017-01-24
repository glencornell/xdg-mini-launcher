#pragma once

#include <vector>
#include "property.hpp"

namespace gui
{
  class Widget
  {
  public:
    Widget(Widget *parent = 0);
    virtual ~Widget();

    Property<int> x;
    Property<int> y;
    Property<int> width;
    Property<int> height;
    Property<int> border_width;

    bool mouse_over_cell(int mouse_x, int mouse_y) const;
    virtual void repaint() { dirty = false; }
    
  protected:
    Widget *m_parent;
    std::vector<Widget *> m_children;
    Property<bool> dirty; // if false, widget needs to be repainted
  };
}
