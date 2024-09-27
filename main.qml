import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtLocation
import QtPositioning

Rectangle
{
    id:mainrectangle
    property int mwidth: 160
    signal dataToPoint()

    property double latitude: 15.6937
    property double longitute: 85.9629
    property int typeDraw: 0

    // Plugin{
    //     id:osmview
    //     name:"osm"
    // }


    Map{
        id:mapview
        anchors.fill:parent
        plugin: Plugin {
            name: "osm"
            PluginParameter {
                name: "osm.mapping.custom.host"
                value: "http://localhost:2080/tiles/"
            }
            PluginParameter { name: "osm.mapping.providersrepository.disabled"; value: true }

        }

        //plugin:osmview

        activeMapType: supportedMapTypes[supportedMapTypes.length - 1]
        center: QtPositioning.coordinate(latitude,longitute)
        minimumZoomLevel: 1
        maximumZoomLevel: 11
        zoomLevel: 5

        // Map Movement =============================================================================================================================

        property geoCoordinate startCentroid
        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                mapview.startCentroid = mapview.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                mapview.zoomLevel += Math.log2(delta)
                mapview.alignCoordinateToPoint(mapview.startCentroid, pinch.centroid.position)
            }
            onRotationChanged: (delta) => {
                mapview.bearing -= delta
                mapview.alignCoordinateToPoint(mapview.startCentroid, pinch.centroid.position)
            }
            grabPermissions: PointerHandler.TakeOverForbidden
        }
        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
        }
        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => mapview.pan(-delta.x, -delta.y)
        }
        Shortcut {
            enabled: mapview.zoomLevel < mapview.maximumZoomLevel
            sequence: StandardKey.ZoomIn
            onActivated: mapview.zoomLevel = Math.round(mapview.zoomLevel + 1)
        }
        Shortcut {
            enabled: mapview.zoomLevel > mapview.minimumZoomLevel
            sequence: StandardKey.ZoomOut
            onActivated: mapview.zoomLevel = Math.round(mapview.zoomLevel - 1)
        }

        MouseArea {
            anchors.fill: mapview
            hoverEnabled: true
            property var coordinate: mapview.toCoordinate(Qt.point(mouseX, mouseY))

            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked : function(mouse){
                if(typeDraw == 0){
                    //console.log("nothing")
                }
                else if(typeDraw == 1){
                    pointspace.mapPointMark(mouse)
                }
                else if(typeDraw == 2){
                    //console.log("line")
                    linespace.mapLineMark(mouse)
                }
                else if(typeDraw == 3){
                    //console.log("polyon")
                    polygonspace.polygonMark(mouse)
                }
                else if(typeDraw == 4){
                    //console.log("circle")
                    circlespace.circleMark(mouse)
                }
                else{
                    console.log("invalid type")
                }
            }

            // onPositionChanged: function(mouse){
            //     if(typeDraw == 4){
            //         //console.log("circle")
            //         radiusSelector(mouse)
            //     }
            // }


            Label {
                id: coordLabel
                x: mapview.width - width
                y: mapview.height - height
                text: "lat: %1; lon: %2".arg(parent.coordinate.latitude).arg(parent.coordinate.longitude)
                color: "black"
                font {
                    pixelSize: 12
                }
                background: Rectangle {
                    color: "white"
                    opacity: 0.5
                }
            }
        }
    }

    Pointmenu{
        id:pointspace
    }

    Linemenu{
        id:linespace
    }

    Polygonmenu{
        id:polygonspace
    }

    Circlemenu{
        id:circlespace
    }

    // Zoom Buttons ======================================================================================

    ColumnLayout{
        id:zoomButtons
        x: mainrectangle.width - width - 10
        y: mainrectangle.height - height - 20
        spacing:5
        width: 30

        Button{
            id:zoomPlus
            text:qsTr("+")
            Layout.fillWidth : true
            background: Rectangle {
                color: "gray"
                //implicitWidth: 100
                //implicitHeight: 40
            }
            contentItem: Text {
                text: zoomPlus.text
                font: zoomPlus.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            onClicked:{
                mapview.zoomLevel += 1
            }
        }

        Button{
            id:zoomLevelVal
            text: parseInt(mapview.zoomLevel)
            enabled: false
            Layout.fillWidth : true
            background: Rectangle {
                color: "gray"
            }
            contentItem: Text {
                text: zoomLevelVal.text
                font: zoomLevelVal.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button{
            id:zoonMinus
            text:qsTr("-")
            Layout.fillWidth : true
            background: Rectangle {
                color: "gray"
            }
            contentItem: Text {
                text: zoonMinus.text
                font: zoonMinus.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
            onClicked:{
                mapview.zoomLevel -= 1
            }
        }
    }

    // All Signals =======================================================================================

    signal sendPointList(variant pointMarkList,variant type)

    signal sendLoadList(variant pointloadList)

    //------------------------------------------------------------

    signal sendLineList(variant lineMarkList,variant type)

    signal sendLineLoadList(variant pointlineList)

    //------------------------------------------------------------

    signal sendPolygonList(variant polygonMarkList,variant type)

    signal sendpolygonLoadList(variant pointpolygonList)

    //--------------------------------------------------------------

    signal sendCircleList(variant circleMarkList,variant type)

    signal sendCircleLoadList(variant pointCircleList)

    //--------------------------------------------------------------

    Component{
        id:mapTextComponent
        MapQuickItem {
            anchorPoint.x: text.width-50
            anchorPoint.y: text.height+15
            sourceItem: Text {
                id: text
                width: 40
                height: 20
                text: ""
                font.pixelSize: 18
                color: "black"
            }
        }
    }

    // Component {
    //     id: mapTextComponent
    //     MapQuickItem {
    //         anchorPoint.x: text.width-50
    //         anchorPoint.y: text.height+15
    //         sourceItem: Rectangle {
    //             id: textRectangle
    //             width: 100  // Adjust width as needed
    //             height: 40  // Adjust height as needed
    //             color: "lightblue"  // Set background color
    //             border.color: "black"
    //             border.width: 2
    //             radius: 5  // Add rounded corners (optional)

    //             Text {
    //                 id: text
    //                 anchors.centerIn: parent
    //                 width: 40
    //                 height: 20
    //                 text: ""
    //                 font.pixelSize: 18
    //                 color: "black"
    //             }
    //         }
    //     }
    // }


    Item{
        id:functionspace
        objectName: "functionspace"

        function chooseDraw(choice){
            //console.log("Choice",choice)
            typeDraw = choice
        }

        function stopDraw(stopper){
            //console.log("stopper",stopper)
            typeDraw = 0
            pointspace.removePointName()
            // pointspace.deleteAllPoints()

            // linespace.deleteAllLines()
            // polygonspace.deleteAllPolygon()
            // circlespace.deleteAllCircle()
        }
    }

    function renderGeoData(features) {
        console.log("Received", features.length, "features");
        for (var i = 0; i < features.length; i++) {
            var feature = features[i];
            console.log("Processing feature of type:", feature.type);
            if (feature.type === "POINT") {
                console.log("Creating point at", feature.y, feature.x);
                var component = Qt.createComponent("PointItem.qml");
                if (component.status === Component.Ready) {
                    var pointItem = component.createObject(mapview, {
                        coordinate: QtPositioning.coordinate(feature.y, feature.x)
                    });
                    mapview.addMapItem(pointItem);
                    console.log("Added point to map");
                } else {
                    console.log("Error creating point item:", component.errorString());
                }
            } else if (feature.type === "LINESTRING") {
                console.log("Creating linestring with", feature.points.length, "points");
                var path = [];
                for (var j = 0; j < feature.points.length; j++) {
                    path.push(QtPositioning.coordinate(feature.points[j].y, feature.points[j].x));
                }
                var polyline = Qt.createQmlObject('import QtLocation 5.6; MapPolyline { line.width: 3; line.color: "blue" }', mapview);
                polyline.path = path;
                mapview.addMapItem(polyline);
                console.log("Added linestring to map");
            } else if (feature.type === "POLYGON") {
                console.log("Creating polygon with", feature.points.length, "points");
                var path = [];
                for (var j = 0; j < feature.points.length; j++) {
                    path.push(QtPositioning.coordinate(feature.points[j].y, feature.points[j].x));
                }
                var polygonItem = Qt.createQmlObject('import QtLocation 5.6; MapPolygon { color: "red"; opacity: 0.5 }', mapview);
                polygonItem.path = path;
                mapview.addMapItem(polygonItem);
                console.log("Added polygon to map");
            }
        }
        console.log("Finished rendering features");
        console.log("Map centered at:", mapview.center.latitude, mapview.center.longitude, "with zoom level:", mapview.zoomLevel);

        // Center the map on the first feature
        if (features.length > 0) {
            var firstFeature = features[0];
            if (firstFeature.type === "POINT") {
                mapview.center = QtPositioning.coordinate(firstFeature.y, firstFeature.x);
            } else if ((firstFeature.type === "LINESTRING" || firstFeature.type === "POLYGON") && firstFeature.points.length > 0) {
                mapview.center = QtPositioning.coordinate(firstFeature.points[0].y, firstFeature.points[0].x);
            }
            mapview.zoomLevel = 10; // Adjust this value as needed
        }
    }
}
