import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    RenderViewer {
        id: viewer
        anchors.fill: parent
    }
}
