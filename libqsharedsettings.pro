QT -= gui

TARGET = qsharedsettings
TEMPLATE = lib

DEFINES += LIBQSHAREDSETTINGS_LIBRARY

SOURCES += qsharedsettings.cpp

HEADERS += qsharedsettings.h

unix {
    target.path = /usr/lib
    INSTALLS += target

    header_files.files = $$HEADERS
    header_files.path = /usr/include
    INSTALLS += header_files
}
