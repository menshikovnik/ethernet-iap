# UdpTool.pro
QT       += widgets network
CONFIG   += c++17

SOURCES  += \
    main.cpp \
    UdpWidget.cpp \
    udpwidget.cpp

HEADERS  += \
    UdpWidget.h \
    udpwidget.h

TARGET = UdpTool
TEMPLATE = app

DISTFILES += \
    .gitignore

