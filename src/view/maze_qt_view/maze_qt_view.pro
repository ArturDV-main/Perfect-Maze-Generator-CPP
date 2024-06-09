QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
qmake

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../main.cc \
    ../../model/s21_model_maze.cc \
    maze_main_win.cc \
    s21_tablet.cc

HEADERS += \
    ../../controller/s21_controller_maze.h \
    ../../model/s21_model_maze.h \
    maze_main_win.h \
    s21_tablet.h

FORMS += \
    maze_main_win.ui \
    s21_tablet.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
