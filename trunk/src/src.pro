######################################################################
# Automatically generated by qmake (2.01a) Wed Nov 4 17:31:02 2009
######################################################################

TEMPLATE = app
TARGET = mcrux.bin
LIBS += -lxml2
DEPENDPATH += . \
              /usr/include/libxml2 \
              bin \
              lib \
              include
INCLUDEPATH += . \
              /usr/include/libxml2 \
               lib \
               include

# Input
HEADERS += lib/MCruxSpecParser.h \
           lib/MCruxWebView.h \
           include/mcrux/MCrux.h \
           lib/abstract/MCruxWindow.h \
           lib/window/MCruxQTWindow.h \
           lib/window/MCruxWindowConfiguration.h \
           lib/window/MCruxWindowManager.h \
           include/mcrux/abstract/callback.h
SOURCES += bin/mcrux_linux.cpp \
           lib/MCrux.cpp \
           lib/MCruxSpecParser.cpp \
           lib/abstract/MCruxWindow.cpp \
           lib/window/MCruxQTWindow.cpp \
           lib/window/MCruxWindowConfiguration.cpp \
           lib/window/MCruxWindowManager.cpp