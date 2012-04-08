# Add more folders to ship with the application, here
folder_01.source = qml/DiplomkaCentral
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE6B650DF

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices Location ReadUserData WriteUserData

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    controller.cpp \
    dbconnection.cpp \
    xmppclient.cpp \
    contact.cpp \
    extension.cpp \
    acl.cpp \
    terrainuser.cpp \
    datapreparator.cpp \
    mapobject.cpp \
    jabberregistrationtool.cpp \
    note.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

CONFIG += mobility
MOBILITY += location

HEADERS += \
    controller.h \
    dbconnection.h \
    xmppclient.h \
    contact.h \
    extension.h \
    acl.h \
    terrainuser.h \
    datapreparator.h \
    mapobject.h \
    jabberregistrationtool.h \
    note.h

QT+=sql core network xml svg


#INCLUDEPATH += $$quote(C:/projects/qxmpp/src)
#LIBS +=-lqxmpp_d -L $$quote(C:/projects/qxmpp/lib/libqxmpp_d.a)
INCLUDEPATH += $$quote(C:/projects/qxmpp/src)
LIBS +=-LC:/projects/qxmpp/lib -lqxmpp_d


#CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
