import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item{
    id:polygonspace
    objectName: "polygonspace"

    property var polygonMarkerId : ({})
    property var tempMarkerId : ({})
    property var tempPolygonPoint : []
    property var tempPolygonPath : []

    Component {
        id: circleMarkerComponent
        MapQuickItem {
            anchorPoint.x: circle.width / 2
            anchorPoint.y: circle.height / 2
            sourceItem: Rectangle{
                id: circle
                color: "black"
                width: 6
                height: 6
                radius: width / 2
            }
        }
    }

    Component {
        id: polygonComponent
        MapPolygon {
            border.color:"black"
            border.width: 2
            color: "#20FFFFFF"
            path: []

            // MouseArea {
            //     id: mouseArea
            //     anchors.fill: parent
            //     hoverEnabled: true
            //     onEntered: {
            //       var polygonItem = parent;
            //       polygonItem.hovered(polygonItem.polygonId);
            //     }
            // }
            // property variant polygonId
            // signal hovered(variant polygonId)
        }
    }

    function polygonMark(mouse){
        var coord = mapview.toCoordinate(Qt.point(mouse.x,mouse.y))
        if(mouse.button === Qt.LeftButton){
            var marker = circleMarkerComponent.createObject(mapview, {
                "coordinate": QtPositioning.coordinate(coord.latitude,coord.longitude)
            });
            tempPolygonPath.push(coord)
            mapview.addMapItem(marker)
            tempPolygonPoint.push(marker)
        }
        else if(mouse.button === Qt.RightButton){
            if (tempPolygonPath.length >= 3) {
                var newPolygon = polygonComponent.createObject(mapview)
                newPolygon.path = tempPolygonPath
                var polyId = new Date().getTime()
                //newPolygon.polygonId = polyId // for hoverhandle
                tempMarkerId[polyId] = newPolygon
                mapview.addMapItem(newPolygon)
                console.log(polyId,tempMarkerId);
                mainrectangle.sendPolygonList(tempMarkerId,0)
            }
            tempPolygonPath = []
            for (var i = 0; i < tempPolygonPoint.length; i++) {
                tempPolygonPoint[i].destroy()
            }
            tempPolygonPoint = []
        }
    }

    function handlePolygonHover(polygonId) {
        console.log("Hovered over polygon:", polygonId);
        popupPolygon.open()

    }

    function deletePolygonList(delList){
        for(var delId in delList){
            var polygonId = delList[delId]
            mapview.removeMapItem(tempMarkerId[polygonId])
            delete tempMarkerId[polygonId]
        }
        mainrectangle.sendPolygonList(tempMarkerId,1)
    }

    function deleteAllPolygon(){
        for(var polygonId in tempMarkerId){
            mapview.removeMapItem(tempMarkerId[polygonId])
            delete tempMarkerId[polygonId]
        }
        mainrectangle.sendPointList(tempMarkerId,1)
    }

    // Load / Deload ==========================================================================polygonMarkerId
    function loadpolygonList(polygonList){
        for(var polygonId in polygonList){
            if(!polygonMarkerId.hasOwnProperty(polygonId)){
                var polygonDataValues = polygonList[polygonId].split("|");
                var pathCoordinates = [];
                for(var j=0; j<polygonDataValues.length; j++){
                    var polygoncoord = polygonDataValues[j].split(",");
                    var lati = parseFloat(polygoncoord[0]);
                    var longi = parseFloat(polygoncoord[1]);
                    pathCoordinates.push({ latitude: lati, longitude: longi });
                }
                var polygon = polygonComponent.createObject(mapview);
                polygon.path = pathCoordinates;
                mapview.addMapItem(polygon)
                polygonMarkerId[polygonId] = polygon
            }
        }
    }

    function deLoadPolygonList(dePolygonList){
        for(var polygonId in dePolygonList){
            var pointId = dePolygonList[polygonId];
            mapview.removeMapItem(polygonMarkerId[pointId])
            delete polygonMarkerId[pointId]
        }
    }

    function deLoadAllPolygon(){
        for(var pointId in polygonMarkerId){
            mapview.removeMapItem(polygonMarkerId[pointId])
            delete polygonMarkerId[pointId]
        }
    }

    function sendLoadedpolygon(){
        console.log("sending loaded value")
        mainrectangle.sendpolygonLoadList(polygonMarkerId)
    }

}
