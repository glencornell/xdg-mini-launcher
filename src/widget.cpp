#include "widget.hpp"

using namespace gui;

Widget::Widget(Widget *parent):
  m_parent(parent)
{
  // Changing any of the widget's parameters will force a repaint
  x.on_change().connect([this](int const &value){ dirty=true; });
  y.on_change().connect([this](int const &value){ dirty=true; });
  width.on_change().connect([this](int const &value){ dirty=true; });
  height.on_change().connect([this](int const &value){ dirty=true; });
  border_width.on_change().connect([this](int const &value){ dirty=true; });
}

Widget::~Widget()
{
}

bool Widget::mouse_over_cell(int mouse_x, int mouse_y) const
{
  if (mouse_x>=x()+border_width() &&
      mouse_x<=x()+width()-border_width() &&
      mouse_y>=y()+border_width() &&
      mouse_y<=y()+height()-border_width())
    return true;
  else
    return false;
}

