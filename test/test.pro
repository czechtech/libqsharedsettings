CONFIG  += debug
CONFIG  -= app_bundle
QT      -= gui

TEMPLATE = app
CONFIG  += console

SOURCES += test.cpp
   LIBS += ../libqsharedsettings.so.1.0.0

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/..\',-z,origin'

TARGET   = test 
