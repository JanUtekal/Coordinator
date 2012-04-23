import QtQuick 1.1

import QtMobility.location 1.2
import Qt 4.7
Rectangle {
    id: pinchmap


    property double defaultLatitude:  49.2166
    property double defaultLongitude: 17.7611
    property int  defaultZoomLevel: 14

    property alias mapType: map.mapType

    property bool pointButtonClicked: false
    property bool lineButtonClicked: false
    property bool polygonButtonClicked: false

    property bool objectEverSelected:false //slouzi ke kontrole jestli byl nekdy nejaky mapovy objekt vybran

    property bool lostLineCoordinate: false//fix of a qml bug

    property color pointColor: Qt.rgba(1, 1, 1, 0.8)
    property color lineColor: "red"
    property color trajectoryColor: "orange"
    property color polygonBorderColor:  "blue"
    property color polygonColor:  Qt.rgba(0, 1, 1, 0.1)
    property color highlightedButtonColor:  Qt.rgba(1, 1, 0, 0.8)

    property int textSize:15

    property bool selectingPermited:false
    property bool movingPermitted:false


    // property bool deleteButtonClicked: false

    // property variant array:[]

    //  property list<MapObject> array2



    //   property list<Item> ar
    function deselect(){
        if(objectEverSelected && cont.getSelectedMapObject()){
            console.log("deselecting",cont.getSelectedMapObject().type)
            if(cont.getSelectedMapObject().type<10){
                cont.getSelectedMapObject().source="images/pointergreen.png";
            } else if(cont.getSelectedMapObject().type<20){
                cont.getSelectedMapObject().border.color=lineColor;
            } else {
                cont.getSelectedMapObject().border.color=polygonBorderColor;
            }

            cont.deselectObject();
            cont.setSelectedMapObject(null);
            console.log("desel")
        }
    }


    Map {

        //    property variant array:Array()

        id: map
        connectivityMode: Map.OfflineMode
        anchors.fill: parent
        zoomLevel: pinchmap.defaultZoomLevel
        plugin: Plugin { name: "nokia" }
        mapType: Map.StreetMap

        center: Coordinate {
            latitude: pinchmap.defaultLatitude
            longitude: pinchmap.defaultLongitude
        }


        // console.log('oooQML: map wheel event, rotation in degrees: ' + delta/8);


        // if (delta > 0) map.zoomLevel += 0.25
        //

        //  else
        MapObjectView {

            id: allLandmarks
            model: landmarkModel
            delegate: Component {




                MapGroup{

                    MapImage{
                        property double lat:landmark.coordinate.latitude
                        property double lon:landmark.coordinate.longitude
                        property string name:landmark.name
                         property int type: -1//landmark.radius
                        property string note:landmark.phoneNumber

                        id: point
                        coordinate: Coordinate{
                            latitude: point.lat
                            longitude: point.lon
                        }

                        source: point.type==0 ? "images/pointergreen.png" : point.type==1 ? "images/pointerblue.png" : "images/pointergrey.png"
                        offset.x: -15
                        offset.y: -96
                        z:1

                        Component.onCompleted: {
                            type=landmark.radius
                           // console.log("TYPE", type,landmark.radius)
                            //  circle.color=pointColor;
                            if(type<10){

                                //  if(type==0){


                                //  }

                                  if(type==1 ){

                                    note=name;
                                  }

                                  if(type==2 ){

                                    note=name;
                                  }

                                  cont.createMapObjectReference(point,point.name, 0, "");

                            } else {
                                if(type==10 || type==15){

                                    visible=false;
                                    border.width=0
                                    //  color="red"
                                }

                                if(type==20){

                                    visible=false;
                                    border.width=0
                                    //  color="red"
                                }
                            }


                        }

                        onNoteChanged: {
                            type=landmark.radius;


                            if(point.type<10){
                                var name=point.note.split("////")[0];

                                background.makeBackGround(name.length);
                                mapT.text=name;


                            }
                        }


                    }


                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        offset.y: 10
                        z: 1
        /*                Component.onCompleted: {
                            if(point.type<10){
                                text=point.note.split("////")[0];
                                background.makeBackGround();
                            } else {
                                visible=false;
                            }


                        }

*/

                    }

                    MapText{
                        id: background
                        coordinate: landmark.coordinate

                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 0
                        offset.y: 10
                        function makeBackGround(length) {

                            if(point.type<10){
                                text="";
                                for(var i=0;i<2*length/3;i++){//

                                    text+="█";
                                }


                            } else {
                                visible=false;
                            }
                        }



                    }



                }

            }
        }


        MapObjectView {

            id: allLandmarks2
            model: landmarkModel
            delegate: Component {




                MapGroup{



                    MapPolyline {
                        // property double lat:landmark.coordinate.latitude
                        // property double lon:landmark.coordinate.longitude
                        property string name: landmark.name
                        property int type: -1//landmark.radius
                        property string note:landmark.phoneNumber
                        id: line
                        border {color: landmark.radius==10 ? lineColor : trajectoryColor; width: 4}
                        visible:false



                        /*    MapMouseArea{
                        //anchors.fill: parent
                        //acceptedButtons: Qt.LeftButton
                        onClicked: {
                            if(!lineButtonClicked){
                                if(type==10){

                                    //console.log("bla");

                                    deselect();

                                    line.border.color="yellow";
                                    cont.setSelectedMapObject(parent);
                                    cont.selectObject(name);
                                    objectEverSelected=true;

                                }
                            }


                        }

                    }*/



                        Component.onCompleted: {


                            type= landmark.radius;


                            if(type>=10 && type<20){

                                cont.createMapObjectReference(line,line.name,1, landmark.description);//to be able to select the object we need to make a reference on it
                                var num=cont.getLineCoordinatesNum(line.name);




                                for(var i=0; i<num;i++){
                                    var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                                    coord.latitude=cont.getLineCoordinateLatAt(line.name,i);

                                    coord.longitude=cont.getLineCoordinateLonAt(line.name,i);
                                    console.log("ulozil jsem",coord.latitude, coord.longitude)
                                    line.addCoordinate(coord);
                                    visible=true;
                                }
                            }


                        }

                        onNoteChanged: {
                            // console.log("changed")
                            type=landmark.radius;

                            if(line.type>=10 && line.type<20){
                                var name=line.note.split("////")[0];

                                background.makeBackGround(name.length);
                                mapT.text=name;
                            }
                        }


                    }

                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        z: 3


                    }

                    MapText{
                        id: background
                        coordinate: landmark.coordinate
                        //   text:"toto je komentar"
                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 2

                        function makeBackGround(length) {

                            if(line.type>=10 && line.type<20){
                                text="";
                                for(var i=0;i<2*length/3;i++){//

                                    text+="█";
                                }

                            } else {
                                visible=false;
                            }
                        }



                    }
                }



            }
        }

        MapObjectView {

            id: allLandmarks3
            model: landmarkModel
            delegate: Component {




                MapGroup{
                    property string note:polygon.note//this property is here because when onNoteChange is declared in polygon, we get an error (qt bug)

                    //bacause of an error in MapPolygon we cannot add anything else than Coordinates into the polygon definition, so we define the polygon geometry here
                    Component.onCompleted: {

                        var type= landmark.radius;


                        if(type==20){
                            polygon.type=type;

                            cont.createMapObjectReference(polygon,polygon.name,2, landmark.description);//to be able to select the object we need to make a reference on it

                            var num=cont.getPolygonCoordinatesNum(polygon.name);
                            for(var i=0; i<num;i++){
                                var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                                coord.latitude=cont.getPolygonCoordinateLatAt(polygon.name,i);
                                coord.longitude=cont.getPolygonCoordinateLonAt(polygon.name,i);
                                polygon.addCoordinate(coord);
                                //helpLine.addCoordinate(coord)
                                polygon.visible=true;
                                // visible=true;
                            }
                        }


                    }
                    onNoteChanged: {
                        // console.log("changed")
                        polygon.type=landmark.radius;

                        if(polygon.type>=20){
                            var name=polygon.note.split("////")[0];

                            background.makeBackGround(name.length);
                            mapT.text=name;
                        }
                    }


                    MapPolygon {
                        // property double lat:landmark.coordinate.latitude
                        // property double lon:landmark.coordinate.longitude
                        property string name: landmark.name
                        property int type: -1
                        property string note:landmark.phoneNumber
                        id: polygon
                        border {color: polygonBorderColor; width: 4}
                        visible:false
                        color: polygonColor


                    }

                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        z: 3


                    }

                    MapText{
                        id: background
                        coordinate: landmark.coordinate
                        //   text:"toto je komentar"
                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 2

                        function makeBackGround(length) {

                            if(polygon.type>=20){
                                text="";
                                for(var i=0;i<2*length/3;i++){//

                                    text+="█";
                                }

                            } else {
                                visible=false;
                            }
                        }



                    }



                }
            }
        }

        MapPolyline {


            id: tmpLine
            border {color: "orange"; width: 3}
            visible:false


        }

        /*   MapPolygon {
            // property double lat:landmark.coordinate.latitude
            // property double lon:landmark.coordinate.longitude


            id: polygon
            border {color: "blue"; width: 4}





            Coordinate{
                latitude: 49.1886
                longitude: 16.5671
            }
            Coordinate{
                latitude: 49.2886
                longitude: 16.5671
            }

            Coordinate{
                latitude: 49.1886
                longitude: 16.6671
            }
        }*/

        MapMouseArea {
            id: mousearea
            //   acceptedButtons: Qt.LeftButton | Qt.RightButton
            property bool __isPanning: false
            property int __lastX: -1
            property int __lastY: -1

            anchors.fill : parent

            onPressed: {
                if(!movingPermitted){

                    __isPanning = true
                    __lastX = mouse.x
                    __lastY = mouse.y
                }
            }

            onReleased: {

                if(!movingPermitted){

                    __isPanning = false
                }
                //            console.log(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);

            }

            onPositionChanged: {

                if(!movingPermitted){

                    if (__isPanning) {
                        var dx = mouse.x - __lastX
                        var dy = mouse.y - __lastY
                        map.pan(-dx, -dy)
                        __lastX = mouse.x
                        __lastY = mouse.y
                    }
                }


            }

            onClicked: {

                console.log(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)
                console.log(pointButtonClicked,lineButtonClicked,polygonButtonClicked,selectingPermited)
                if(pointButtonClicked){

                    cont.addPoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude, userManagement.selectedMapAcl);
                    pointButtonClicked=false;
                    pointButton.alwaysPressed(false);
                } else if(lineButtonClicked) {


                    if (mouse.button == Qt.LeftButton){


                        cont.addLinePoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);

                        //      var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord");

                        //  coord.latitude=cont.getLineCoordinateLatAt(i);
                        //  coord.longitude=cont.getLineCoordinateLonAt(i);


                        tmpLine.addCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)));
                        if(lostLineCoordinate){
                            tmpLine.removeCoordinate(tmpLine.path[0]);
                            lostLineCoordinate=false;
                        } else {
                            tmpLine.visible=true;
                        }


                    }
                    else{
                        cont.lineReady(userManagement.selectedMapAcl);
                        console.log("hh",tmpLine.path.length)
                        tmpLine.visible=false;

                        while(tmpLine.path.length!==1){

                            tmpLine.removeCoordinate(tmpLine.path[0]);


                        }





                        console.log("hh",tmpLine.path.length)
                        lineButtonClicked=false;
                        lostLineCoordinate =true;

                        lineButton.alwaysPressed(false);


                    }
                } else if(polygonButtonClicked) {


                    if (mouse.button == Qt.LeftButton){


                        cont.addPolygonPoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);

                        //      var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord");

                        //  coord.latitude=cont.getLineCoordinateLatAt(i);
                        //  coord.longitude=cont.getLineCoordinateLonAt(i);

                        console.log("adding coordinate")
                        tmpLine.addCoordinate(map.toCoordinate(Qt.point(mouse.x,mouse.y)));
                        if(lostLineCoordinate){
                            tmpLine.removeCoordinate(tmpLine.path[0]);
                            lostLineCoordinate=false;
                        } else {
                            tmpLine.visible=true;

                        }


                    }
                    else{
                        cont.polygonReady(userManagement.selectedMapAcl);

                        console.log("hh",tmpLine.path.length)
                        tmpLine.visible=false;

                        while(tmpLine.path.length!==1){

                            tmpLine.removeCoordinate(tmpLine.path[0]);


                        }



                        //  console.log("hh",tmpLine.path.length)
                        polygonButtonClicked=false;
                        lostLineCoordinate =true;

                        polygonButton.alwaysPressed(false);
                    }
                } else {
                    if(!selectingPermited){
                        console.log("tryyyy")
                        var paintedObject=cont.findObjectUnderCursor(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);
                        if(paintedObject){
                            deselect();

                            if(paintedObject.type<10){
                                paintedObject.source="images/pointeryellow.png";
                            } else {
                                paintedObject.border.color="yellow";
                            }
                            cont.setSelectedMapObject(paintedObject);
                            cont.selectObject(paintedObject.name);
                            objectEverSelected=true;


                        } else {
                            deselect();
                        }


                    }
                }



            }

            /*     onCanceled: {
                __isPanning = false;
            }*/



        }

    }
    Column{
        x: 20
        y: 20
        spacing: 20
        id:leftButtons
        Button{
            id: pointButton
            width: 120
            height: 50

            z: 2
            label: "Add Point"

            onButtonClick: {
                pointButtonClicked=true;
                lineButtonClicked=false;
                polygonButtonClicked=false;
                pointButton.alwaysPressed(true);
                polygonButton.alwaysPressed(false);
                lineButton.alwaysPressed(false);
            }

        }

        Button{
            id: lineButton
            width: 120
            height: 50

            z: 2
            label: "Add Route"

            onButtonClick: {
                lineButtonClicked=true;
                pointButtonClicked=false;
                polygonButtonClicked=false;
                //cont.testButtonOperation();
                lineButton.alwaysPressed(true);
                polygonButton.alwaysPressed(false);
                pointButton.alwaysPressed(false);

            }

        }

        Button{
            id: polygonButton
            width: 120
            height: 50

            z: 2
            label: "Add Area"

            onButtonClick: {
                polygonButtonClicked=true;
                pointButtonClicked=false;
                lineButtonClicked=false;
                //cont.testButtonOperation();
                polygonButton.alwaysPressed(true);
                lineButton.alwaysPressed(false);
                pointButton.alwaysPressed(false);
            }

        }

        Button{
            id: noteButton
            width: 120
            height: 50

            z: 2
            label: "Add Note"

            onButtonClick: {

                if(objectEverSelected && cont.getSelectedMapObject() ){

                   // console.log(cont.getSelectedMapObject().name);

                    noteEditor.visible=true;

                    selectingPermited=true;
                }


            }

        }



    }

    Column{
        x: parent.width-140
        y: 20
        z: 2
        spacing: 20

        Button{
            id: userManagementButton
            width: 120
            height: 50

            label: "User Management"

            onButtonClick: {
                userManagement.visible=true;
                cont.prepareAclList();
                cont.prepareTerrainUserList();


            }

        }

        Button{
            id: messageButton
            width: 120
            height: 50

            z: 2
            label: "Messages"

            onButtonClick: {
                messageScreen.visible=true;
                messageButton.highlighted=false;

            }

        }
        Button{
            id: historyButton
            width: 120
            height: 50

            z: 2
            label: "History"

            onButtonClick: {
                history.visible=true;
                cont.prepareAclHistoryList();
            //    cont.prepareTerrainUserList();

            }

        }

    }

    AclListMap{
        id: aclListMap
        width: 150
        height: 350
        //   color: userManagement.color

        x: parent.width-170
        y: parent.height-450
        z: 1


        Component.onCompleted: {
            cont.prepareAclList();
        }
    }

    AclListHistory{
        id: aclListHistoryMap
        width: 150
        height: 350
        //   color: userManagement.color

        x: parent.width-170
        y: parent.height-450
        z: 1

        visible:false



    }



    Button{
        id: closeHistoryButton
        width: 140
        height: 50

        x: 20
        y: 20
        z: 2
        label: "Close history view"
        visible:false

        onButtonClick: {
            //history.visible=false;
            cont.getAllMapObjects();
            terrainUserFromAclHistoryListMap.visible=false;
            aclListHistoryMap.visible=false;
            aclListMap.visible=true;
            leftButtons.visible=true;
            closeHistoryButton.visible=false;
            pinchmap.selectingPermited=false;
        }

    }



    TerrainUserFromAclHistoryList {
        id: terrainUserFromAclHistoryListMap
        width: 150
        height: 350
        //   color: userManagement.color

        x: 20
        y: parent.height-450
        z: 1

        visible:false



    }



    Item {
        id: keyitem
        anchors.fill: parent
        focus: true
        Keys.onPressed: {

            if (event.key == Qt.Key_Plus) {

                console.log('oooQML: Key + was pressed');

                if(map.zoomLevel<map.maximumZoomLevel){
                    map.zoomLevel += 0.5
                    textSize+=1
                    cont.setZoomRatio(map.zoomLevel);
                }

            }
            if (event.key == Qt.Key_Minus) {

                console.log('oooQML: Key - was pressed');
                if(map.zoomLevel>map.minimumZoomLevel){
                    map.zoomLevel -= 1.5
                    textSize-=1
                    cont.setZoomRatio(map.zoomLevel);
                }

            }

            if (event.key == Qt.Key_Delete) {

                console.log('oooQML: Key del was pressed');
                cont.deleteCurrentObject();
                objectEverSelected=false;
                deselect();


            }
        }

        onFocusChanged: {

        }

    }

    LandmarkModel {
        id: landmarkModel
        autoUpdate: true
        // filter: boxFilter
        // limit: 20
        onModelChanged: {
            console.log("All landmark model changed, landmark count: " + count)
            //    allLandmarks.repaint=true;
            //    allLandmarks.repaint=false;
        }
        // importFile: "landmarks.lmx"
    }


    UserManagement{
        id: userManagement
        anchors.centerIn: parent
        z:2
        visible: false


    }

    History{
        id: history
        anchors.centerIn: parent
        z:2
        visible: false


    }

    NoteEditor{
        id: noteEditor
        anchors.centerIn: parent
        width:250
        height: 260
        z:2
        visible:false
    }

    MessageScreen{
        id: messageScreen
        anchors.centerIn: parent
        z:2
        visible: false
    }


    Component.onCompleted: {

        //  var a=Qt.createComponent("MapCircle {center: Coordinate{latitude: defaultLatitude;longitude: defaultLongitude;};radius: 10000;color: \"yellow\"}");


        // map.addMapObject(a)



    }

    Rectangle{
        id:nodb
        width:parent.width/2
        height: nodbText.paintedHeight
        y: 50
        anchors.horizontalCenter: parent.horizontalCenter
        color:"white"
        radius: 5
        visible:false

        Text{
            id:nodbText
            width:parent.width
            text: "The program is running without database. The funcionality is strongly limited. Testing purposes only."
            font.pointSize: 15
            wrapMode: Text.WordWrap
            color:"red"
        }
    }

    Connections{
        target: cont
        onUpdatePositionForMapUser:{

            if(userPoint){
                userPoint.lat=lat;
                userPoint.lon=lon;
                userPoint.type=1;

            }
        }

        onSetMapUserOffline:{
            if(userPoint){

                userPoint.type=2;
            }
        }

        onNoDbModeSig:{

            userManagement.selectedMapAcl=1;
            nodb.visible=true;
        }

        onNewMessageFromUserAt:{
            if(!messageScreen.visible){
                messageButton.highlighted=true;
            }
        }

        onAllowMoving:{
            pinchmap.movingPermitted=false;
        }
    }


}
