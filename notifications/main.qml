import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.4
import QtQuick.Window 2.11

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Notification Tester")

    Material.theme: Material.Light

    NotificationArea {
        id: notificationArea
        height_extended: 0.3 * parent.height
        width: parent.width
        anchors.top: parent.top
    }

    Rectangle {
        id: content
        height: parent.height
        width: parent.width
        anchors.bottom: parent.bottom

        Image {
            source: "background.jpg"
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
        }

        Button {
            id: btn
            width: parent.width * 0.3
            height: parent.height * 0.1
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter

            onClicked: {
                notificationArea.addNotification("Warnung", "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum.")
            }
        }
    }
}
