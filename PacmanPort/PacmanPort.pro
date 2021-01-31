QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/game/GameStatus.cpp \
    ../src/game/Ghost.cpp \
    ../src/game/Maze.cpp \
    ../src/game/Node.cpp \
    ../src/game/Pacman.cpp \
    ../src/gui/Game.cpp \
    ../src/gui/GhostGraphic.cpp \
    ../src/gui/HighScore.cpp \
    ../src/gui/MainMenu.cpp \
    ../src/gui/PPMPixmap.cpp \
    ../src/gui/PacmanGraphic.cpp \
    ../src/gui/ScorePoint.cpp \
    ../src/hardware/QTPaintDevice.cpp \
    ../src/misc/DataInfo.cpp \
    ../src/misc/FpsStabilizer.cpp \
    ../src/misc/Rect.cpp \
    GameWidget.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../src/game/GameStatus.h \
    ../src/game/Ghost.h \
    ../src/game/Maze.h \
    ../src/game/Node.h \
    ../src/game/Pacman.h \
    ../src/gui/Game.h \
    ../src/gui/GhostGraphic.h \
    ../src/gui/GraphicObject.h \
    ../src/gui/HighScore.h \
    ../src/gui/MainMenu.h \
    ../src/gui/PPMPixmap.h \
    ../src/gui/PacmanGraphic.h \
    ../src/gui/ScorePoint.h \
    ../src/hardware/KeyMapping.h \
    ../src/hardware/PaintDevice.h \
    ../src/hardware/QTPaintDevice.h \
    ../src/hardware/Resources.h \
    ../src/hardware/peripherals.h \
    ../src/misc/DataInfo.h \
    ../src/misc/FpsStabilizer.h \
    ../src/misc/Rect.h \
    GameWidget.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
