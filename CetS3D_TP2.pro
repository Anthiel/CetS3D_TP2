#R. Raffin
#M1 Informatique, Aix-Marseille Université
#.pro de l'application de départ du TP1

QT	+= core gui
QT      += opengl
CONFIG	+= c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CetS3D_TP2
TEMPLATE = app

unix:!win32 {
    LIBS += -lglut -lGLU
    LIBS += -L$$PWD/OpenMesh/liblinux/ -lOpenMeshCore

    INCLUDEPATH += $$PWD/OpenMesh/inc/
    DEPENDPATH += $$PWD/OpenMesh/inc/
    DEPENDPATH += $$PWD/OpenMesh/liblinux/
}
win32 {
    LIBS += -lGLU32\
    -lOpengl32
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myopenglwidget.cpp \
    segment.cpp \
    point.cpp \
    courbeparametrique.cpp \
    settings.cpp

HEADERS += \
        mainwindow.h \
    myopenglwidget.h \
    segment.h \
    point.h \
    courbeparametrique.h \
    settings.h

FORMS += \
        mainwindow.ui \
    settings.ui

RESOURCES += \
    ressources.qrc
