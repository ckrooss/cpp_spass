import QtQuick 2.0
import QtQuick.Controls 2.2

Item {
    // private
    id: root
    property double _vis_frac: _active_notification ? 1.0 : 0.0
    property var _notifications: []
    property var _active_notification: null
    property int _idx: 0
    property int _default_timeout: 5000

    z: 1
    height: height_extended * _vis_frac
    visible: _vis_frac > 0

    Rectangle {
        id: background
        clip: true
        anchors.fill: parent
        color: "grey"
        opacity: 0.8 * _vis_frac
    }

    ProgressBar {
        id: timeout_bar
        visible: _active_notification
        width: parent.width
        height: 2
        value: _active_notification ? (_active_notification.timeout / _active_notification.initial_timeout) : 0
    }

    Button {
        id: notification_count
        text: _notifications.length
        clip: true
        anchors.margins: 10
        anchors.left: root.left
        anchors.verticalCenter: title.verticalCenter
        width: 0.05 * parent.width
        height: width
        opacity: 0.8 * _vis_frac
    }

    Text {
        id: title
        clip: true
        anchors.margins: 5
        width: parent.width
        height: parent.height * 0.2
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        text: _active_notification ? _active_notification.title : ""

        font.bold: true
        font.pointSize: 20
    }

    Text {
        id: message
        clip: true
        width: parent.width
        height: parent.height * 0.8
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: parent.bottom
        text: _active_notification ? _active_notification.message : ""

        font.pointSize: 12
        wrapMode: Text.Wrap
    }

    MouseArea {
        anchors.fill: parent
        onClicked: _shiftActiveNotification()
    }

    Behavior on _vis_frac {
        // Make _vis_frac move smoothly: use for y-position and opacity
        NumberAnimation {
            duration: 500
            easing.type: Easing.InOutQuad
        }
    }

    Timer {
        id: update_timer
        interval: 10
        repeat: true
        running: false

        onTriggered: {
            /*
              Stop timer if nothing is scheduled (to save energy)
              Count down timeout of active notification
              If currently active notification is still valid, stop here
            */
            if (!_active_notification && _notifications.length === 0) return stop()
            if (_active_notification) _active_notification.timeout -= interval
            if (_active_notification && _active_notification.timeout >= 0) {
                _active_notificationChanged()
                return
            }
            _shiftActiveNotification()
        }
    }

    function _shiftActiveNotification() {
        // If currently no active notification AND upcoming notifications:
        // advance the queue by one notification
        if (_notifications.length && (_vis_frac === 0.0)) _active_notification = _notifications.shift()
        else _active_notification = null
        _notificationsChanged()
    }

    // public
    function addNotification(title, message, timeout) {
        timeout = timeout || _default_timeout

        var new_notification = {
            id: _idx++,
            title: title || "",
            message: message || "",
            timeout: timeout,
            initial_timeout: timeout,
            timeout_percent: 1.0
        }
        _notifications.push(new_notification)
        _notificationsChanged()
        update_timer.start()
    }

    property int height_extended: 0
}
