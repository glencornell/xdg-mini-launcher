#include "grid.hpp"

using namespace gui;

void Grid::recalculate(void)
{
  border=width()/10;
  cell_width=icon_size()+padding()*2+border_width()*2;
  cell_height=icon_size()+padding()*2+border_width()*2+font_height();
  columns=(width()-border()*2)/cell_width();
  cell_width=(width()-border()*2)/columns(); // rounded
}

void Grid::add_widget(ToolButton *child)
{
  child->icon_size=icon_size();
  child->font_name=font_name;
  m_children.push_back(child);
}
