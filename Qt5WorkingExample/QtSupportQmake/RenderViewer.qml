import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: viewer

    property real fieldOfView: 3.5
    property real fieldHeight: 3.5

    RenderScene {
        id: scene
        anchors.fill: parent
    }
}
