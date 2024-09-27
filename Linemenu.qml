import QtQuick
import QtQuick.Controls.Universal
import QtQuick.Layouts
import QtLocation
import QtPositioning

Item{
    id:linespace
    objectName: "linespace"

    property var lineMarkerId : ({})
    property var tempMarkerId : ({})
    property var tempLinePoint : []
    property var tempLinePath: []

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
        id: polyLineComponent
        MapPolyline {
            line.width: 3
            line.color: "black"
            path: []

            // MouseArea {
            //     id: mouseArea
            //     anchors.fill: parent
            //     hoverEnabled: true
            //     onEntered: {
            //       var lineItem = parent;
            //       lineItem.hovered(lineItem.polyLineId);
            //     }

            // }
            // property variant polyLineId
            // signal hovered(variant polyLineId)
        }
    }

    // Creating / Removing new Lines ======================================================================

    function mapLineMark(mouse){
        var coord = mapview.toCoordinate(Qt.point(mouse.x, mouse.y))
        //console.log(coord.latitude,coord.longitude)
        if(mouse.button === Qt.LeftButton){
            var marker = circleMarkerComponent.createObject(mapview, {
                "coordinate": QtPositioning.coordinate(coord.latitude,coord.longitude)
            });
            tempLinePath.push(coord)
            mapview.addMapItem(marker)
            tempLinePoint.push(marker)
        }
        else if(mouse.button === Qt.RightButton){
            if(tempLinePath.length > 1){
                var polyLine = polyLineComponent.createObject(mapview)
                polyLine.path = tempLinePath
                var lineId = new Date().getTime()

                //polyLine.polyLineId = lineId// for hoverhandle

                tempMarkerId[lineId] = polyLine
                mapview.addMapItem(polyLine)
                console.log(lineId,tempMarkerId);
                mainrectangle.sendLineList(tempMarkerId,0)
            }

            // for (var id in lineMarkerId) {
            //     lineMarkerId[id].hovered.connect(handleLineHover);
            // }

            tempLinePath = []
            for (var i = 0; i < tempLinePoint.length; i++) {
                tempLinePoint[i].destroy()
            }
            tempLinePoint = []
        }
    }

    function deleteLineList(delList){
        for(var delId in delList){
            var lineId = delList[delId]
            mapview.removeMapItem(tempMarkerId[lineId])
            delete tempMarkerId[lineId]
        }
        mainrectangle.sendLineList(tempMarkerId,1)
    }

    function deleteAllLines(){
        for(var pointId in tempMarkerId){
            mapview.removeMapItem(tempMarkerId[pointId])
            delete tempMarkerId[pointId]
        }
        mainrectangle.sendPointList(tempMarkerId,1)
    }

    // Load / Deload ==========================================================================

    function loadLineList(lineList){
        for(var lineId in lineList){
            if(!lineMarkerId.hasOwnProperty(lineId)){
                var lineDataValues = lineList[lineId].split("|");
                var pathCoordinates = [];

                for(var j=0; j<lineDataValues.length; j++){
                    var linecoord = lineDataValues[j].split(",");
                    var lati = parseFloat(linecoord[0]);
                    var longi = parseFloat(linecoord[1]);
                    pathCoordinates.push({ latitude: lati, longitude: longi });
                }
                var polyLine = polyLineComponent.createObject(mapview);
                polyLine.path = pathCoordinates;
                mapview.addMapItem(polyLine)
                lineMarkerId[lineId] = polyLine
            }
        }
    }

    function deLoadLineList(deLineList){
        for(var lineId in deLineList){
            var pointId = deLineList[lineId];
            mapview.removeMapItem(lineMarkerId[pointId])
            delete lineMarkerId[pointId]
        }
    }

    function deLoadAllLines(){
        for(var pointId in lineMarkerId){
            mapview.removeMapItem(lineMarkerId[pointId])
            delete lineMarkerId[pointId]
        }
    }

    // Line Details Info ======================================================================

    function handleLineHover(polyLineId) {
        console.log("Hovered over polygon:", polyLineId)
        console.log(tempMarkerId[polyLineId])
    }

    function sendLoadedLine(){
        console.log("sending loaded value")
        mainrectangle.sendLineLoadList(lineMarkerId)
    }

    function showLineName(lineId,lineName){

    }


}
