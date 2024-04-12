QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Panes/about_pane.cpp \
    Panes/controllers_pane.cpp \
    Panes/driver_pane.cpp \
    Panes/hmd_pane.cpp \
    Panes/screens_pane.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Panes/Pane_class.h \
    Panes/about_pane.h \
    Panes/controllers_pane.h \
    Panes/driver_pane.h \
    Panes/hmd_pane.h \
    Panes/screens_pane.h \
    mainwindow.h

FORMS += \
    Panes/about_pane.ui \
    Panes/controllers_pane.ui \
    Panes/driver_pane.ui \
    Panes/hmd_pane.ui \
    Panes/screens_pane.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    resources.qrc
