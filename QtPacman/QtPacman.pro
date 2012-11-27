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

LIBS += -lglut -lGL -lGLU
