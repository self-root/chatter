import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: app
    width: 640
    height: 480
    visible: true
    title: "Chatter"

    Text {
        text: qsTr("Hello, world!")
        anchors.centerIn: parent
    }
}
