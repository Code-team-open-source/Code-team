QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClientConnection.cpp \
    buttons.cpp \
    creator_of_tasks.cpp \
    game_field.cpp \
    git_tool.cpp \
    main.cpp \
    main_indicators.cpp \
    mainwindow.cpp \
    my_dial.cpp \
    settings.cpp \
    sliders.cpp \
    task.cpp \
    task_button.cpp \
    task_buttons_6.cpp \
    task_dial.cpp \
    task_git_tool.cpp \
    task_sliders.cpp \
    tool.cpp

HEADERS += \
    ClientConnection.h \
    buttons.h \
    creator_of_tasks.h \
    game_field.h \
    git_tool.h \
    main_indicators.h \
    mainwindow.h \
    my_dial.h \
    settings.h \
    sliders.h \
    task.h \
    task_button.h \
    task_buttons_6.h \
    task_dial.h \
    task_git_tool.h \
    task_sliders.h \
    tool.h

FORMS += \
    creator_of_tasks.ui \
    game_field.ui \
    mainwindow.ui \
    settings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
LIBS += -lWs2_32

RESOURCES += \
    resourses.qrc
