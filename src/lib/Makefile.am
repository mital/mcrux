## Process this file with automake to produce Makefile.in

INCLUDES = -I@top_srcdir@/lib -I@top_srcdir@/include

SUBDIRS = window

noinst_HEADERS=MCruxSpecParser.h

lib_LTLIBRARIES = libmcrux_common.la

libmcrux_common_la_SOURCES = \
	MCrux.cpp \
	MCruxSpecParser.cpp
