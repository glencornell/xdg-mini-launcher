#pragma once

#include "widget.hpp"
#include "toolbutton.hpp"

namespace gui
{
  class Grid : public Widget
  {
  public:
    Grid(Widget *parent = 0);

    void add_widget(ToolButton *);
    void recalculate();

    Property<int> padding; // the distance between two child widgets
    Property<int> border; // distance from edge to first child
    Property<int> columns; // number of columns.

    // Children will be forced to share the same geometry:
    Property<int> icon_size;
    Property<int> cell_width;
    Property<int> cell_height;
    Property<int> font_height;
  };
}
