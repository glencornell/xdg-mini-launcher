#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include "entry_factory.hpp"
#include "menu_entry.hpp"
#include "ezxml.h"
#include "xdginfo.hpp"

using namespace xdg;

MenuEntry *MenuEntry::create(ezxml_t top)
{
  MenuEntry *rval = 0;
  ezxml_t name_elem = ezxml_child(top, "Name");
  DesktopEntryFactory factory;
  xdginfo xdg;
  
  if(name_elem == 0)
    {
      std::cerr << "ERROR: menu doesn't have a \"Name\" element." << std::endl;
    }
  else
    {
      const char *name = name_elem->txt;
      ezxml_t directory_elem = ezxml_child(top, "Directory");
      if(directory_elem == 0)
	{
	  std::cerr << "ERROR: menu \"" << name << "\" doesn't have a \"Directory\" element." << std::endl;
	}
      else
	{
	  const char *directory = directory_elem->txt;
	  std::string full_path;
	  xdg.find(full_path, "directories", directory);
	  DirectoryEntry *new_directory_object = dynamic_cast<DirectoryEntry *>(factory.create(full_path));
	  if(new_directory_object == 0)
	    {
	      std::cerr << "ERROR: unable to parse directory entry \"" << directory_elem->txt << "\"." << std::endl;
	    }
	  else
	    {
	      rval = new MenuEntry(new_directory_object);
	      if (!rval)
		{
		  std::cerr << "ERROR: unable to create new menu object" << std::endl;
		}
	      else
		{
		  ezxml_t include = ezxml_child(top, "Include");
		  if(include==0)
		    {
		      std::cerr << "ERROR: menu \"" << name << "\" doesn't have an \"Include\" element." << std::endl;
		    }
		  else
		    {
		      ezxml_t and_elem = ezxml_child(include, "And");
		      if(and_elem==0)
		    {
		      std::cerr << "ERROR: menu \"" << name << "\" doesn't have an \"Include/And\" element." << std::endl;
		    }
		      else
			{
			  ezxml_t child = 0;
			  for (child = and_elem->child; child; child = child->ordered)
			    {
			      if (strcmp(child->name, "Filename")==0)
				{
				  // Child element is an application entry:
				  std::string file(child->txt);
				  std::string full_path;
				  xdg.find(full_path, "applications", file);
				  AbstractEntry *item = factory.create(full_path.c_str());
				  if (item==0)
				    {
				      std::cerr << "ERROR: unable to create desktop entry \"" << full_path << "\"." << std::endl;
				    }
				  else
				    {
				      rval->m_children.push_back(item);
				    }
				}
			      else if(strcmp(child->name, "Menuname")==0)
				{
				  // Child element is a menu entry:
				  // search the xml structure for the Menu element with the given name:
				  std::string child_menu_name(child->txt);
				  if(child_menu_name == "")
				    {
				      std::cerr << "ERROR: \"Menuname\" element has no text." << std::endl;
				    }
				  else
				    {
				      ezxml_t menu_elem = 0;
				      bool found = false;
				      for(menu_elem = ezxml_child(top, "Menu"); menu_elem; menu_elem = menu_elem->next)
					{
					  ezxml_t name_elem = 0;
					  for(name_elem = ezxml_child(menu_elem,"Name");name_elem;name_elem->next)
					    {
					      if (strcmp(name_elem->txt, child_menu_name.c_str()) == 0)
						{
						  found = true;
						  break;
						}
					    }
					  if(found)
					    break;
					}
				      if (!found)
					{
					  std::cerr << "ERROR: \"" << name
						    << "\" element has no menu child with name = \""
						    << child_menu_name << "\"." << std::endl;
					}
				      else
					{
					  AbstractEntry *child_menu = create(menu_elem);
					  if(!child_menu)
					    {
					      std::cerr << "ERROR: can't create child menu" << std::endl;
					    }
					  else
					    {
					      rval->m_children.push_back(child_menu);
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
  return rval;
}

MenuEntry *MenuEntry::create(std::string const &filename)
{
  MenuEntry *rval = 0;
  xdg::xdginfo xdg;
  
  // extract the path from the filename:
  std::string full_path;

  // does the file exist as specified?
  struct stat file_info = { 0 };
  bool found = false;
  
  if (::stat(filename.c_str(), &file_info))
    {
      // does not exist as specified, now find it according to the XDG rules:
      xdg.find(full_path, "", filename);
    }
  else
    {
      if (!S_ISREG(file_info.st_mode) && !S_ISLNK(file_info.st_mode))
	{
	  std::cerr << "ERROR: \"" << filename << "\" is neither a file nor a symbolic link." << std::endl;
	}
      else
	{
	  // file exists
	  full_path = filename;
	}
    }
  if(full_path.size())
    {
      ezxml_t top = ezxml_parse_file(full_path.c_str());
      rval = create(top);
      ezxml_free(top);
    }
  else
    {
      std::cerr << "ERROR: unable to load \"" << filename << "\"" <<std::endl;
    }
  return rval;
}

MenuEntry::MenuEntry(DirectoryEntry *dir) :
  DirectoryEntry(*dir)
{
}
