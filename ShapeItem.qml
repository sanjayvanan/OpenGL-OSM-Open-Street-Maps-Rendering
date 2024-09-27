import QtQuick
import QtLocation
import QtPositioning
import QtQuick.Shapes 1.15

MapQuickItem {
    id: root
    anchorPoint.x: width / 2
    anchorPoint.y: height / 2

    property string shapeType
    property var points: []
    property string fileName

    sourceItem: Item {
        width: 1000  // Adjust based on your needs
        height: 1000 // Adjust based on your needs

        Shape {
            anchors.fill: parent
            ShapePath {
                strokeColor: shapeType === "LINESTRING" ? "blue" : "red"
                strokeWidth: shapeType === "LINESTRING" ? 3 : 1
                fillColor: shapeType === "POLYGON" ? Qt.rgba(1, 0, 0, 0.5) : "transparent"

                PathPolyline {
                    path: {
                        var path = [];
                        for (var i = 0; i < points.length; i++) {
                            var point = mapview.fromCoordinate(points[i], false);
                            path.push(Qt.point(point.x, point.y));
                        }
                        return path;
                    }
                }
            }
        }

        Rectangle {
            visible: shapeType === "POINT"
            width: 14
            height: 14
            color: "red"
            border.color: "black"
            border.width: 2
            radius: 7
        }

        Text {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: fileName
            font.pixelSize: 12
            color: "black"
            style: Text.Outline
            styleColor: "white"
        }
    }
}
