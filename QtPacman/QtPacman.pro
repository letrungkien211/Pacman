#-------------------------------------------------
#
# Project created by QtCreator 2012-11-28T03:14:51
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = QtPacman
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    ../Pacman/Model/utility.cpp \
    ../Pacman/Model/state.cpp \
    ../Pacman/Model/minimaxAgent.cpp \
    ../Pacman/Model/common.cpp \
    ../Pacman/Model/alphabetaAgent.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    ../Pacman/Model/utility.hpp \
    ../Pacman/Model/state.hpp \
    ../Pacman/Model/minimaxAgent.hpp \
    ../Pacman/Model/grid.hpp \
    ../Pacman/Model/common.hpp \
    ../Pacman/Model/alphabetaAgent.hpp \
    ../8puzzle/mystl.hpp \
    ../8puzzle/gsearch.hpp

FORMS    += mainwindow.ui

OTHER_FILES += \
    ../Pacman/Model/README.md \
    ../Pacman/Model/Makefile

INCLUDEPATH += \
    ../Pacman/Model/ \
    ../8puzzle/

LIBS += -lglut -lGL -lGLU
