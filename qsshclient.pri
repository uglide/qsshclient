QT += core network

CONFIG += c++11

HEADERS += \
    $$PWD/src/*.h \

SOURCES += \
    $$PWD/src/*.cpp \

INCLUDEPATH += $$PWD/src/

include($$PWD/3rdparty/3rdparty.pri)
