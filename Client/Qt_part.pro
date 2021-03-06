QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buttons.cpp \
    main.cpp \
    main_indicators.cpp \
    mainwindow.cpp \
    sliders.cpp \
    task.cpp \
    task_button.cpp \
    task_buttons_6.cpp \
    task_sliders.cpp \
    tool.cpp

HEADERS += \
    buttons.h \
    main_indicators.h \
    mainwindow.h \
    sliders.h \
    task.h \
    task_button.h \
    task_buttons_6.h \
    task_sliders.h \
    tool.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
