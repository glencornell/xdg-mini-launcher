bin_PROGRAMS = xdg-mini-launcher

xdg_mini_launcher_SOURCES = \
	abstract_entry.cpp \
	abstract_entry.hpp \
	application_entry.cpp \
	application_entry.hpp \
	directory_entry.cpp \
	directory_entry.hpp \
	entry_factory.cpp \
	entry_factory.hpp \
	grid.cpp \
	grid.hpp \
	main.cpp \
	menu_entry.cpp \
	menu_entry.hpp \
	process.cpp \
	process.hpp \
	toolbutton.cpp \
	toolbutton.hpp \
	widget.cpp \
	widget.hpp \
	wmdesktop.cpp \
	wmdesktop.hpp \
	x11info.cpp \
	x11info.hpp \
	xdginfo.cpp \
	xdginfo.hpp

xdg_mini_launcher_LDADD = \
	$(top_srcdir)/lib/ezxml/libezxml.la \
	$(top_srcdir)/lib/inih/libinih.la \
	$(top_srcdir)/lib/wmctrl/libwmctrl.la \
	$(IMLIB2_LDADD)
xdg_mini_launcher_CPPFLAGS = \
	-I$(top_srcdir)/lib/ezxml \
	-I$(top_srcdir)/lib/inih \
	-I$(top_srcdir)/lib/wmctrl
xdg_mini_launcher_CXXFLAGS = \
	-I$(top_srcdir)/lib/ezxml \
	-I$(top_srcdir)/lib/inih \
	-I$(top_srcdir)/lib/wmctrl
