#pragma once

#include <X11/Xlib.h>

class x11info
{
public:
  static void init(void);
  static Display *display(void);
private:
  static Display *m_display;
};
