import QtQuick 2.0
import QtLocation 5.6

MapQuickItem {
    id: mapItem
    anchorPoint.x: image.width/2
    anchorPoint.y: image.height

    sourceItem: Rectangle {
        width: 14
        height: 14
        color: "red"
        border.color: "black"
        border.width: 2
        radius: 7
    }
}
