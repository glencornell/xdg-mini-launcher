#pragma once

#include <vector>
#include <X11/Xlib.h>
#include "property.hpp"
#include "font.hpp"

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
    Property<Font *> font;

    bool mouse_over_cell(int mouse_x, int mouse_y) const;

    virtual void process_configure_notify_event(XConfigureEvent const *ev) { }
    virtual void process_key_pressed_event(XKeyPressedEvent const *ev) { }
    virtual void process_key_released_event(XKeyReleasedEvent const *ev) { }
    virtual void process_button_pressed_event(XButtonPressedEvent const *ev) { }
    virtual void process_button_released_event(XButtonReleasedEvent const *ev) { }

    virtual void repaint() { dirty = true; }
    
  protected:
    Widget *m_parent;
    std::vector<Widget *> m_children;
    Property<bool> dirty; // if false, widget needs to be repainted
  };
}
