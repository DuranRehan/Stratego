TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors -Wpedantic -Werror
SOURCES += \
        Board.cpp \
        Piece.cpp \
        Position.cpp \
        facade.cpp \
        observable.cpp

HEADERS += \
    ColorPiece.h \
    Role.h \
    board.h \
    direction.h \
    facade.h \
    observable.h \
    observers.h \
    position.h \
    piece.h

DISTFILES +=

RESOURCES +=
