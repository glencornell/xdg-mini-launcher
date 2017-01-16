#include "x11info.hpp"

Display *x11info::m_display = 0;

void x11info::init(void)
{
  m_display = XOpenDisplay(NULL);
}

Display *x11info::display(void)
{
  return m_display;
}

