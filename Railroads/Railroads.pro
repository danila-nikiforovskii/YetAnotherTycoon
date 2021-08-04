QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DMagnetsD.cpp \
    DMagnetsDL.cpp \
    DMagnetsDR.cpp \
    DMagnetsL.cpp \
    DMagnetsR.cpp \
    DMagnetsU.cpp \
    DMagnetsUL.cpp \
    DMagnetsUR.cpp \
    DRandom.cpp \
    DRoadMagnets.cpp \
    DRoadMagnetsD.cpp \
    DRoadMagnetsDL.cpp \
    DRoadMagnetsDR.cpp \
    DRoadMagnetsL.cpp \
    DRoadMagnetsR.cpp \
    DRoadMagnetsU.cpp \
    DRoadMagnetsUL.cpp \
    DRoadMagnetsUR.cpp \
    MousePressEvents.cpp \
    MouseReleaseEvents.cpp \
    dloco.cpp \
    dmagnets.cpp \
    dmainscreen.cpp \
    dnetworklist.cpp \
    dnetworknode.cpp \
    dplayer.cpp \
    drailfragment.cpp \
    droadlist.cpp \
    dterraincell.cpp \
    main.cpp \
    mainwindow.cpp \
    dpath.cpp

HEADERS += \
    defines.h \
    dloco.h \
    dmainscreen.h \
    dnetworklist.h \
    dnetworknode.h \
    dplayer.h \
    drailfragment.h \
    droadlist.h \
    dterraincell.h \
    mainwindow.h \
    dpath.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
