QT       += core gui sql widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += static

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addnewrecorddialog.cpp \
    adialogbase.cpp \
    alternatives.cpp \
    animalsdialog.cpp \
    clientdialog.cpp \
    employeedialog.cpp \
    fieldvariant.cpp \
    main.cpp \
    mainwindow.cpp \
    ordersdialog.cpp \
    positiondialog.cpp \
    settingsrepository.cpp \
    sqlitemanager.cpp \
    sqlitereader.cpp \
    sqlitewriter.cpp

HEADERS += \
    addnewrecorddialog.h \
    adialogbase.h \
    alternatives.h \
    animalsdialog.h \
    clientdialog.h \
    employeedialog.h \
    fieldvariant.h \
    mainwindow.h \
    ordersdialog.h \
    positiondialog.h \
    settingsrepository.h \
    sqlitemanager.h \
    sqlitereader.h \
    sqlitewriter.h \
    stdafx.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    craete_pitomnik_db.sql


