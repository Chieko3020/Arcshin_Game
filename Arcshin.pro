QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamewindow.cpp \
    gemstone.cpp \
    help.cpp \
    hikari.cpp \
    main.cpp \
    mainwindow.cpp \
    score.cpp \
    setting.cpp

HEADERS += \
    gamewindow.h \
    gemstone.h \
    help.h \
    hikari.h \
    mainwindow.h \
    score.h \
    setting.h

FORMS += \
    gamewindow.ui \
    help.ui \
    mainwindow.ui \
    score.ui \
    setting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc



VERSION = 1.0.0
QMAKE_TARGET_COMPANY = "Chieko3020"
QMAKE_TARGET_DESCRIPTION = "Arcshin"
QMAKE_TARGET_COPYRIGHT = "Copyright(C) 2024"
QMAKE_TARGET_PRODUCT = "Arcshin"
RC_LANG = 0x0800
RC_ICONS = ./res/title.ico

