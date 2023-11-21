QT -= gui
QT += network sql core concurrent

TEMPLATE = lib
DEFINES += CHATCORE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    socketconnection.cpp

HEADERS += \
    chattercore_global.h
    socketconnection.h

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


android{
    message(PLATFORM_ANDROID)
    LIBS += -L$$PWD/lib/android/ -lprotobuf
    include($$PWD/lib/android/android_openssl/openssl.pri)
}

linux{
    linux-g++{
        message(PLATFORM_LINUX)
        LIBS += -lprotobuf
        LIBS += -lpthread -lglib-2.0 -lsecret-1
        INCLUDEPATH += /usr/include/glib-2.0 \
                       /usr/include/libsecret-1 \

        DEPENDPATH  += /usr/include/glib-2.0 \
                        /usr/include/libsecret-1
    }
}
