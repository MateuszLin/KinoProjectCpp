#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T18:02:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RezerwacjaKino
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += Headers/mainwindow.h \
           Headers/newreservation.h \
           Headers/newreservation.h \
           Headers/database.h \
           Headers/chooiceseats.h \
           Headers/modifyrezervation.h \
           Headers/adminspanel.h



FORMS += Forms/mainwindow.ui \
         Forms/newreservation.ui \
         Forms/chooiceseats.ui \
         Forms/modifyrezervation.ui \
         Forms/adminspanel.ui


SOURCES += main.cpp \
           Sources/mainwindow.cpp \
           Sources/newreservation.cpp \
           Sources/database.cpp \
           Sources/chooiceseats.cpp \
           Sources/modifyrezervation.cpp \
           Sources/adminspanel.cpp


