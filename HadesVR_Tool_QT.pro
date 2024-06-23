QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets serialport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Panes/about_pane.cpp \
    Panes/controllers_pane.cpp \
    Panes/driver_pane.cpp \
    Panes/generic_pane.cpp \
    Panes/hmd_pane.cpp \
    Panes/others_pane.cpp \
    Panes/screens_pane.cpp \
    connection_handler.cpp \
    generic_setting.cpp \
    main.cpp \
    mainwindow.cpp \
    vrsettings.cpp

HEADERS += \
    Panes/Pane_class.h \
    Panes/about_pane.h \
    Panes/controllers_pane.h \
    Panes/driver_pane.h \
    Panes/generic_pane.h \
    Panes/hmd_pane.h \
    Panes/others_pane.h \
    Panes/screens_pane.h \
    connection_handler.h \
    generic_setting.h \
    include_ext/hidapi.h \
    mainwindow.h \
    vrsettings.h

FORMS += \
    Panes/about_pane.ui \
    Panes/controllers_pane.ui \
    Panes/driver_pane.ui \
    Panes/hmd_pane.ui \
    Panes/others_pane.ui \
    Panes/screens_pane.ui \
    mainwindow.ui

LIBS += \
    # no idea why $$PWD is needed, but it doesn't compile without it for me. https://stackoverflow.com/questions/55513042/how-to-link-external-dlls-properly-in-qt-creator
    $$PWD/dlls/hidapi.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    resources.qrc

DISTFILES += \
    include_ext/hidapi.dll
