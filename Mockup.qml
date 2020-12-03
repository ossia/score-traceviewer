import QtQuick 2.0
import org.kde.kirigami 2.12
import QtQuick.Controls 2.15

import io.ossia 1.0

Item {
    property var ticks;

    GraphRenderer{
        id: renderer
        graph: ticks[Math.round(slider.value)].dataflow.graph;
    }

    Column {
        id: column
        x: 39
        y: 16
        width: 577
        height: 400

        Row {
            id: row
            width: 556
            height: 50

            Slider {
                id: slider
                width: 400
                height: 22
                value: 0.5
                from: 0
                to: ticks.length
            }

            Text {
                id: text1
                text: Math.round(slider.value)

                font.pixelSize: 12
            }
        }

        Image {
            id: image
            width: sourceSize.width
            height: sourceSize.height
            source: "file://" + renderer.imagePath
            onSourceChanged: console.log(source)
            fillMode: Image.PreserveAspectFit
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
