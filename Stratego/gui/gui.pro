QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_CXXFLAGS += -std=c++17 -pedantic-errors -Wpedantic -Werror
SOURCES += \
    boardfx.cpp \
    controllerFx.cpp \
    main.cpp \
    piecefx.cpp \
    viewfx.cpp

HEADERS += \
    boardfx.h \
    controllerFx.h \
    piecefx.h \
    viewfx.h

FORMS += \
    viewfx.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../metier/release/ -lmetier
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../metier/debug/ -lmetier
else:unix: LIBS += -L$$OUT_PWD/../metier/ -lmetier

INCLUDEPATH += $$PWD/../metier
DEPENDPATH += $$PWD/../metier

RESOURCES += \
    resources.qrc \
