#pragma once

#include <string>
#include "widget.hpp"
#include "signal.hpp"
#include "property.hpp"

namespace gui
{
  class ToolButton : public Widget
  {
  public:
    ToolButton(Widget *parent = 0);
    
    Property<std::string> text;
    Property<int> icon_size;
    Property<bool> hovered;
    Property<bool> clicked;

    void icon(std::string const &file_name);
    void font_name(std::string const &font_name);
    int font_height(void) const { return m_font_height; }

    Signal<> on_hovered;
    Signal<> on_clicked;

  private:
    ToolButton();
    
    // Rendering parameters
    int m_font_height;

    // TODO: icon
    // TODO: font_name
  };
}
