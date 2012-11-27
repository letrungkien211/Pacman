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
<<<<<<< HEAD
    ../Model/utility.cpp \
    ../Model/state.cpp \
    ../Model/minimaxAgent.cpp \
    ../Model/common.cpp \
    ../Model/alphabetaAgent.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    ../Model/utility.hpp \
    ../Model/state.hpp \
    ../Model/minimaxAgent.hpp \
    ../Model/grid.hpp \
    ../Model/common.hpp \
    ../Model/alphabetaAgent.hpp \
    ../../8puzzle/mystl.hpp \
    ../../8puzzle/gsearch.hpp

FORMS    += mainwindow.ui

INCLUDEPATH += \
    ../Model/ \
    ../../8puzzle/
=======
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
>>>>>>> 190a61bafe01f63f98800fa3edc5e000d93c0bda

LIBS += -lglut -lGL -lGLU
