import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item{
    id:circlespace
    objectName: "circlespace"

    property var circleMarkerId : ({})
    property var tempMarkerId : ({})
    property var coordcenter
    property var tempCirclePoint : []

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
        id: mapCircleComponent
        MapCircle {
            border.color: "black"
            border.width: 2
            color: "#20FFFFFF"
            center: QtPositioning.coordinate()
            radius: 10
        }
    }

    // Creating / removing new Circle =========================================================

    function circleMark(mouse) {
        if(mouse.button === Qt.LeftButton){
            coordcenter =  mapview.toCoordinate(Qt.point(mouse.x,mouse.y))
            var marker = circleMarkerComponent.createObject(mapview, {
                "coordinate": QtPositioning.coordinate(coordcenter.latitude,coordcenter.longitude)
            });
            mapview.addMapItem(marker)
            tempCirclePoint.push(marker)
        }
        else if(mouse.button === Qt.RightButton){
            if (typeof coordcenter !== "undefined" && coordcenter !== null) {
                var circle = mapCircleComponent.createObject(mapview)
                var coordr = mapview.toCoordinate(Qt.point(mouse.x, mouse.y))
                var distance = coordcenter.distanceTo(coordr)
                if(distance !== 0){
                    circle.center = coordcenter
                    circle.radius = distance
                    var circleId = new Date().getTime()
                    tempMarkerId[circleId] = circle
                    mapview.addMapItem(circle)
                    mainrectangle.sendCircleList(tempMarkerId,0)
                }
            }
            for (var i = 0; i < tempCirclePoint.length; i++) {
                tempCirclePoint[i].destroy()
            }
            tempCirclePoint = []
            coordcenter = null
        }
    }

    function deleteCircleList(delList){
        for(var delId in delList){
            var circleId = delList[delId]
            mapview.removeMapItem(tempMarkerId[circleId])
            delete tempMarkerId[circleId]
        }
        mainrectangle.sendCircleList(tempMarkerId,1)
    }

    function deleteAllCircle(){
        for(var circleId in tempMarkerId){
            mapview.removeMapItem(tempMarkerId[circleId])
            delete tempMarkerId[circleId]
        }
        mainrectangle.sendCircleList(tempMarkerId,1)
    }

    // Load / Deload ==========================================================================

    function loadCircleList(loadList) {
        for(var i=0; i<loadList.length; i++){
            var pointDataValues = loadList[i].split("|");
            var gpointid = pointDataValues[0];
            var latitude = pointDataValues[1];
            var longitude = pointDataValues[2];
            var radius = pointDataValues[3];

            console.log("gpointid",gpointid,"latitude",latitude,"longitude",longitude,"radius",radius);

            if (!circleMarkerId.hasOwnProperty(gpointid)){
                var circle = mapCircleComponent.createObject(mapview)
                if(radius !== 0){
                    circle.center = QtPositioning.coordinate(latitude, longitude);
                    circle.radius = radius
                    circleMarkerId[gpointid] = circle
                    mapview.addMapItem(circle)
                }
            }
        }
    }

    function deLoadCircleList(deloadList){
        for(var circleId in deloadList){
            var pointId = deloadList[circleId];
            mapview.removeMapItem(circleMarkerId[pointId])
            delete circleMarkerId[pointId]
        }
    }

    function deLoadAllCircles(){
        for(var pointId in circleMarkerId){
            mapview.removeMapItem(circleMarkerId[pointId])
            delete circleMarkerId[pointId]
        }
    }

    function sendLoadedCircles(){
        mainrectangle.sendCircleLoadList(circleMarkerId)
    }

}
