TEMPLATE = app

QT += testlib #Include QtTest to use SignalSpy, QTest::mouseClick, etc

CONFIG += testcase #Creates 'check' target in Makefile.
CONFIG += c++11
CONFIG -= debug_and_release
CONFIG += console

TARGET = Tests

include(../GoogleTest/GoogleTest.pri)

HEADERS += \ 
    ../BalloonModelApp/balloonmovement.h

SOURCES += \ 
    main.cpp \
    ../BalloonModelApp/balloonmovement.cpp
