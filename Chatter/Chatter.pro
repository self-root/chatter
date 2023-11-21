QT += quick sql core concurrent

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp 

HEADERS += \
        screencontroller.h

RESOURCES += qml.qrc \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# set_source_files_properties($$PWD/style/Style.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)
# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


android {
    message(ChatUI Android)

    LIBS += -L$$OUT_PWD/../ChatterCore/ -lChatterCore_arm64-v8a
    include($$PWD/../ChatterCore/lib/android/android_openssl/openssl.pri)

}

linux{
    linux-g++{
        message(chatUI linux)
        LIBS += -L$$OUT_PWD/../ChatterCore/ -lChatterCore
        INCLUDEPATH += /usr/include/glib-2.0 \
                       /usr/include/libsecret-1
    }
}


INCLUDEPATH += $$PWD/../ChatterCore
DEPENDPATH += $$PWD/../ChatterCore
INCLUDEPATH += $$PWD/../ChatterCore/include
DEPENDPATH += $$PWD/../ChatterCore/include


