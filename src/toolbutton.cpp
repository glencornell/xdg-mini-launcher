#include "toolbutton.hpp"

using namespace gui;

ToolButton::ToolButton(Widget *parent) :
  Widget(parent),
  m_font_height(0)
{
}

void ToolButton::icon(std::string const &file_name)
{
  // TODO: load image file
}

void ToolButton::font_name(std::string const &font_name)
{
  // TODO : load font
}
