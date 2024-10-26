TEMPLATE = app
TARGET = greenhouse

QT += core gui widgets opengl

CONFIG += c++11

SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    # ... (celelalte surse)

HEADERS += mainwindow.h \
    glwidget.h \
    # ... (celelalte headere)

FORMS += mainwindow.ui

LIBS += -lGL

# Pentru sisteme care necesită explicit linking la OpenGL
unix: LIBS += -lGLU
