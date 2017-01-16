AM_CPPFLAGS = -isystem $(top_srcdir)/lib/gtest/include -I$(top_srcdir)/src $(GTEST_CPPFLAGS)
AM_CXXFLAGS = $(GTEST_CXXFLAGS)
AM_LDFLAGS = $(GTEST_LDFLAGS) $(GTEST_LIBS) \
	     $(top_srcdir)/lib/gtest/lib/libgtest_main.la \
	     $(top_srcdir)/lib/gtest/lib/libgtest.la \
	     $(top_srcdir)/lib/ezxml/libezxml.la \
	     $(top_srcdir)/lib/inih/libinih.la \
	     $(top_srcdir)/lib/wmctrl/libwmctrl.la \
	     $(IMLIB2_LDADD)

# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS = 
check_PROGRAMS = 

TESTS += test_process
check_PROGRAMS += test_process

test_process_SOURCES = test_process.cpp
test_process_LDADD = $(top_srcdir)/src/xdg_mini_launcher-process.o
