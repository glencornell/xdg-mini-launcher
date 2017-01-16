bin_PROGRAMS = xdg-mini-launcher

xdg_mini_launcher_SOURCES = \
	abstract_entry.cpp \
	application_entry.cpp \
	entry_factory.cpp \
	main.cpp \
	process.cpp \
	wmdesktop.cpp \
	x11info.cpp

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
