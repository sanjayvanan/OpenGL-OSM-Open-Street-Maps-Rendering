import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item{
    id:pointspace
    objectName: "pointspace"

    signal sendTestSignal()

    property var pointMarkId: ({})
    property var tempMarkId: ({})
    property var loadPointNames: []

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
    // MouseArea {
    //     id: mouseArea
    //     anchors.fill: parent
    //     hoverEnabled: true
    //     onEntered: {
    //       var pointItem = parent;
    //       pointItem.hovered(pointItem.pointId);
    //     }

    // }
    // property variant pointId
    // signal hovered(variant pointId)

    // Creating / removing new Points =========================================================

    function mapPointMark(mouse){
        console.log("pointspace mapPointMark called")
        var coord = mapview.toCoordinate(Qt.point(mouse.x, mouse.y))
        if (mouse.button === Qt.LeftButton){
            //console.log("left clicked")
            var marker = circleMarkerComponent.createObject(mapview, {
                "coordinate": QtPositioning.coordinate(coord.latitude,coord.longitude)
            });
            var pointId = new Date().getTime()
            tempMarkId[pointId] = marker
            loadPointNames = []
            console.log("marker-object = ",marker)
            //marker.pointId = pointId // for hoverhandle
            mapview.addMapItem(marker)
            // for (var id in tempMarkId) {  // for hoverhandle
            //     tempMarkId[id].hovered.connect(handlePointHover);
            // }
            mainrectangle.sendPointList(tempMarkId,0)
        }
    }

    function deletePointList(delList){
        for(var delId in delList){
            var pointId = delList[delId]
            mapview.removeMapItem(tempMarkId[pointId])
            delete tempMarkId[pointId]
        }
        loadPointNames = []
        mainrectangle.sendPointList(tempMarkId,1)
        removePointName()
    }

    function deleteAllPoints(){
        for(var pointId in tempMarkId){
            mapview.removeMapItem(tempMarkId[pointId])
            delete tempMarkId[pointId]
        }
        loadPointNames = []
        mainrectangle.sendPointList(tempMarkId,1)
        removePointName()
    }

    // Load / Deload ==========================================================================

    function loadPointList(loadList) {
        for (var i = 0; i < loadList.length; i++) {
            var pointDataValues = loadList[i].split("|");
            var gpointid = pointDataValues[0];
            var latitude = pointDataValues[1];
            var longitude = pointDataValues[2];

            if (!pointMarkId.hasOwnProperty(gpointid)) {
                var marker = circleMarkerComponent.createObject(mapview, {
                    "coordinate": QtPositioning.coordinate(latitude, longitude)
                });

                pointMarkId[gpointid] = marker;
                mapview.addMapItem(marker);
            }
        }
    }

    function deLoadPointList(deloadList){
        for(var delId in deloadList){
            var pointId = deloadList[delId]
            mapview.removeMapItem(pointMarkId[pointId])
            delete pointMarkId[pointId]
        }
        loadPointNames = []
        removePointName()
    }

    function deLoadAllPoints(){
        for(var pointId in pointMarkId){
            mapview.removeMapItem(pointMarkId[pointId])
            delete pointMarkId[pointId]
        }
        loadPointNames = []
        removePointName()
    }

    // Point Details Info ======================================================================

    function handlePointHover(PointId) {
        console.log("Hovered over polygon:", PointId);
    }    

    function sendLoadedPoints(){
        console.log("sending loaded value")
        mainrectangle.sendLoadList(pointMarkId)
    }

    property var tempTextHolder : []
    function showPointName(pointId,pointName){
        removePointName(pointId)
        var mapPoint = tempMarkId[pointId];

        mapPoint.sourceItem.color = "red"

        var coords = mapPoint.coordinate
        var marker = mapTextComponent.createObject(mapview, {
            "coordinate": QtPositioning.coordinate(coords.latitude, coords.longitude)
        });

        tempTextHolder.push(marker)
        marker.sourceItem.text = pointName
        //marker.sourceItem.children[0].text = pointName;
        mapview.addMapItem(marker)
    }

    function removePointName(){
        for (var key in tempMarkId) {
            console.log("Key:", key, "Value:", tempMarkId[key])
            var mapPoint = tempMarkId[key];
            mapPoint.sourceItem.color = "black"
        }
        for (var i = 0; i < tempTextHolder.length; i++) {
            mapview.removeMapItem(tempTextHolder[i]);
        }
        tempTextHolder = [];
    }
}
