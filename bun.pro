# Add more folders to ship with the application, here
folder_01.source = ../question
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

QT += core gui\
        declarative\
        quick\
        widgets\
        qml\

CONFIG += qt


# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    ImageProvider.cpp \
    FileIO.cpp \
    Timeprocess.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../question/Sentakudeleagte.qml \
    ../question/Sentakushimodel.qml \
    ../question/Choose.qml \
    ../question/Dropitem.qml \
    ../question/Dragitem.qml \
    ../question/Log.qml \
    ../question/Logmodel.qml \
    ../question/Puzzledelegate.qml

HEADERS += \
    ImageProvider.h \
    FileIO.h \
    Timefunction.h \
    Timeprocess.h \
    Ipget.h
