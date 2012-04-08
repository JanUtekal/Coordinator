import QtQuick 1.1

import QtMobility.location 1.2
import Qt 4.7
Rectangle {
    id: pinchmap

    property double defaultLatitude:  49.1969
    property double defaultLongitude: 16.6017
    property int  defaultZoomLevel: 14

    property alias mapType: map.mapType

    property bool pointButtonClicked: false
    property bool lineButtonClicked: false
    property bool polygonButtonClicked: false

    property bool objectEverSelected:false //slouzi ke kontrole jestli byl nekdy nejaky mapovy objekt vybran

    property bool lostLineCoordinate: false//fix of a qml bug

    property color pointColor: Qt.rgba(1, 1, 1, 0.8)
    property color lineColor: "red"
    property color polygonBorderColor:  "blue"
    property color polygonColor:  Qt.rgba(0, 1, 1, 0.1)

    property int textSize:15

    property bool selectingPermited:false
    // property bool deleteButtonClicked: false

    // property variant array:[]

    //  property list<MapObject> array2



    //   property list<Item> ar
    function deselect(){
        if(objectEverSelected){
            console.log("type",cont.getSelectedMapObject().type)
            if(cont.getSelectedMapObject().type<10){
                cont.getSelectedMapObject().source="images/pointergreen.png";
            } else if(cont.getSelectedMapObject().type<20){
                cont.getSelectedMapObject().border.color=lineColor;
            } else {
                cont.getSelectedMapObject().border.color=polygonBorderColor;
            }

            cont.deselectObject();
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
                        coordinate: landmark.coordinate
                        source: point.type==0 ? "images/pointergreen.png" : point.type==1 ? "images/pointerblue.png" : "images/pointergrey.png"
                        offset.x: -15
                        offset.y: -96
                        z:1

                        Component.onCompleted: {
                            type=landmark.radius
                            console.log("TYPE", type,landmark.radius)
                            //  circle.color=pointColor;
                            if(type<10){

                                //  if(type==0){


                                //  }

                                //   if(type==1){

                                //     color="blue";
                                //   }

                                /*  if(type==2){

                                    color="grey";
                                }*/
                                cont.createMapObjectReference(point,point.name,0);

                            } else {
                                if(type==10){

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
                                mapT.text=point.note.split("////")[0];
                                background.makeBackGround();
                            }
                        }


                    }


                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        z: 3
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
                        //   text:"toto je komentar"
                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 2

                        function makeBackGround() {

                            if(point.type<10){
                                text="";
                                for(var i=0;i<2*mapT.text.length/3;i++){
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
                        border {color: lineColor; width: 4}
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


                            if(type==10){
                                var num=cont.getLineCoordinatesNum();
                                for(var i=0; i<num;i++){
                                    var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                                    coord.latitude=cont.getLineCoordinateLatAt(i);
                                    coord.longitude=cont.getLineCoordinateLonAt(i);
                                    line.addCoordinate(coord);
                                    visible=true;
                                }
                                cont.createMapObjectReference(line,line.name,1);//to be able to select the object we need to make a reference on it

                            }


                        }

                        onNoteChanged: {
                            // console.log("changed")
                            type=landmark.radius;

                            if(line.type>=10 && line.type<20){
                                mapT.text=line.note.split("////")[0];
                                background.makeBackGround();
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

                        function makeBackGround() {

                            if(line.type>=10 && line.type<20){
                                text="";
                                for(var i=0;i<2*mapT.text.length/3;i++){
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

                            var num=cont.getPolygonCoordinatesNum();
                            for(var i=0; i<num;i++){
                                var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                                coord.latitude=cont.getPolygonCoordinateLatAt(i);
                                coord.longitude=cont.getPolygonCoordinateLonAt(i);
                                polygon.addCoordinate(coord);
                                //helpLine.addCoordinate(coord)
                                polygon.visible=true;
                                // visible=true;
                            }
                            cont.createMapObjectReference(polygon,polygon.name,2);//to be able to select the object we need to make a reference on it

                        }


                    }
                    onNoteChanged: {
                        // console.log("changed")
                        polygon.type=landmark.radius;

                        if(polygon.type>=20){
                            mapT.text=note.split("////")[0];
                            background.makeBackGround();
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

                        function makeBackGround() {

                            if(polygon.type>=20){
                                text="";
                                for(var i=0;i<2*mapT.text.length/3;i++){
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
                __isPanning = true
                __lastX = mouse.x
                __lastY = mouse.y
            }

            onReleased: {
                __isPanning = false

                //            console.log(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);

            }

            onPositionChanged: {
                if (__isPanning) {
                    var dx = mouse.x - __lastX
                    var dy = mouse.y - __lastY
                    map.pan(-dx, -dy)
                    __lastX = mouse.x
                    __lastY = mouse.y
                }
            }

            onClicked: {
                console.log(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)

                if(pointButtonClicked){

                    cont.addPoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude, userManagement.selectedMapAcl);
                    pointButtonClicked=false;
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


                    }
                } else {
                    if(!selectingPermited){
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
        Button{
            id: pointButton
            width: 120
            height: 50

            z: 2
            label: "Přidat bod"

            onButtonClick: {
                pointButtonClicked=true;
                lineButtonClicked=false;
                polygonButtonClicked=false;
            }

        }

        Button{
            id: lineButton
            width: 120
            height: 50

            z: 2
            label: "Přidat trasu"

            onButtonClick: {
                lineButtonClicked=true;
                pointButtonClicked=false;
                polygonButtonClicked=false;
                //cont.testButtonOperation();

            }

        }

        Button{
            id: polygonButton
            width: 120
            height: 50

            z: 2
            label: "Přidat oblast"

            onButtonClick: {
                polygonButtonClicked=true;
                pointButtonClicked=false;
                lineButtonClicked=false;
                //cont.testButtonOperation();

            }

        }

        Button{
            id: noteButton
            width: 120
            height: 50

            z: 2
            label: "Přidat poznámku"

            onButtonClick: {
                if(cont.getSelectedMapObject()){
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

            label: "Spravovat uživatele"

            onButtonClick: {
                userManagement.visible=true;
                cont.prepareAclList();
                cont.prepareTerrainUserList();


            }

        }

        Button{
            id: testButton
            width: 120
            height: 50

            z: 2
            label: "test"

            onButtonClick: {
                cont.testButtonOperation();

            }

        }
        Button{
            id: testButton2
            width: 120
            height: 50

            z: 2
            label: "test"

            onButtonClick: {
                cont.testButtonOperation2();

            }

        }

    }

    AclListMap{
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




    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {

            if (event.key == Qt.Key_Plus) {

                console.log('oooQML: Key + was pressed');

                if(map.zoomLevel<map.maximumZoomLevel){
                    map.zoomLevel += 0.5
                    textSize+=1
                }

            }
            if (event.key == Qt.Key_Minus) {

                console.log('oooQML: Key - was pressed');
                if(map.zoomLevel>map.minimumZoomLevel){
                    map.zoomLevel -= 1.5
                    textSize-=1
                }
            }

            if (event.key == Qt.Key_Delete) {

                console.log('oooQML: Key del was pressed');
                cont.deleteCurrentObject();
                objectEverSelected=false;
            }
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

    NoteEditor{
        id: noteEditor
        anchors.centerIn: parent
        width:250
        height: 260
        z:2
        visible:false
    }


    Component.onCompleted: {

        //  var a=Qt.createComponent("MapCircle {center: Coordinate{latitude: defaultLatitude;longitude: defaultLongitude;};radius: 10000;color: \"yellow\"}");


        // map.addMapObject(a)



    }

}
