#-------------------------------------------------
#
# Project created by QtCreator 2017-07-12T15:37:41
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AMC4030
TEMPLATE = app


SOURCES += main.cpp\
    newmanualoperation.cpp \
    newsavefile.cpp \
    CmdFile.cpp \
    MC_CmdInterface.cpp \
    newbuildfile.cpp \
    newmodifyname.cpp \
    amc4030.cpp \
    ComInterface.cpp \
    Transfer.cpp \
    TransferProtocol.cpp \
    newabout.cpp \
    newprogrameditor.cpp \
    c_amc4030dll.cpp \
    Communication.cpp \
    newparametersetting.cpp \
    newcombobox.cpp \
    iostatus.cpp

HEADERS  += amc4030.h \
    SystemParam.h \
    newmanualoperation.h \
    newprogrameditor.h \
    newsavefile.h \
    Commdefine.h \
    CmdFile.h \
    MC_CmdInterface.h \
    newbuildfile.h \
    newmodifyname.h \
    ComInterface.h \
    Transfer.h \
    TransferProtocol.h \
    newabout.h \
    c_amc4030dll.h \
    Communication.h \
    newparametersetting.h \
    newcombobox.h \
    iostatus.h

FORMS    += amc4030.ui \
    newmanualoperation.ui \
    newprogrameditor.ui \
    newsavefile.ui \
    newbuildfile.ui \
    newmodifyname.ui \
    newabout.ui \
    newparametersetting.ui \
    iostatus.ui

RC_FILE     += appico.rc

RESOURCES +=

TRANSLATIONS = AMC4030_CHINESE_CN.ts \
               AMC4030_ENGLISH_CN.ts
