import QtQuick 2.15
import QtQuick.Window 2.15
import io.ossia 1.0
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Mockup {
        anchors.fill: parent
        ticks: m.ticks
    }

    ExecutionModel {
        id: m
        path: "/tmp/score_execution_log.json"
    }
}
