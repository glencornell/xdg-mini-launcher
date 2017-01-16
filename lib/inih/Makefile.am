# Nonstandard package files for distribution
EXTRA_DIST = \
    examples/INIReaderExample.cpp \
    examples/ini_dump.c \
    examples/test.ini \
    examples/config.def \
    examples/ini_example.c \
    examples/ini_buffer.c \
    examples/ini_xmacros.c \
    extra/Makefile.static \
    cpp/INIReader.cpp \
    cpp/INIReader.h \
    Makefile.am \
    README.md \
    tests/baseline_disallow_inline_comments.txt \
    tests/multi_line.ini \
    tests/bad_comment.ini \
    tests/normal.ini \
    tests/user_error.ini \
    tests/baseline_handler_lineno.txt \
    tests/unittest.c \
    tests/baseline_stop_on_first_error.txt \
    tests/unittest.bat \
    tests/baseline_multi.txt \
    tests/baseline_single.txt \
    tests/bad_section.ini \
    tests/bom.ini \
    tests/unittest.sh \
    tests/bad_multi.ini \
    LICENSE.txt

# Build rules for libraries.
noinst_LTLIBRARIES = libinih.la

libinih_la_SOURCES = \
	ini.c \
	ini.h
