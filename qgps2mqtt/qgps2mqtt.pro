QT -= gui
QT +=  core mqtt positioning

CONFIG += c++11 console
CONFIG -= app_bundle

QMAKE_LFLAGS += -lgps
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "$$PWD/../../sysroot/" \
               "$$PWD/../../sysroot/lib" \
               "$$PWD/../../sysroot/opt" \
               "$$PWD/../../sysroot/usr" \
               "$$PWD/../../sysroot/usr/include" \
               "$$PWD/../../sysroot/usr/include/arm-linux-gnueabihf"

LIBS +=    "-L$$PWD/../../sysroot/" \
           "-L$$PWD/../../sysroot/opt" \
           "-L$$PWD/../../sysroot/lib" \
           "-L$$PWD/../../sysroot/usr" \
           "-L$$PWD/../../sysroot/usr/include" \
           "-L$$PWD/../../sysroot/usr/include/arm-linux-gnueabihf"

SOURCES += \
        configsetting.cpp \
        gpsconfigure.cpp \
        locationdetect.cpp \
        main.cpp \
        mainmodel.cpp \
        mqttsender.cpp \
        mqttsenderprivate.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /usr/local/qt5pi/vpos
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    configsetting.h \
    gpsconfigure.h \
    locationdetect.h \
    mainmodel.h \
    mqttsender.h \
    mqttsenderprivate.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../qt-everywhere-src-5.12.3/qtbase/lib/release/ -lQt5Network
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../qt-everywhere-src-5.12.3/qtbase/lib/debug/ -lQt5Network
else:unix: LIBS += -L$$PWD/../../qt-everywhere-src-5.12.3/qtbase/lib/ -lQt5Network

INCLUDEPATH += $$PWD/../../qt-everywhere-src-5.12.3/qtbase/include
DEPENDPATH += $$PWD/../../qt-everywhere-src-5.12.3/qtbase/include
