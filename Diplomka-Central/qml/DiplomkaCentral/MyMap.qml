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


    property color lineColor: "red"
    property color polygonBorderColor:  "blue"
    property color polygonColor:  Qt.rgba(0, 1, 1, 0.1)

    // property bool deleteButtonClicked: false

    // property variant array:[]

    //  property list<MapObject> array2



    //   property list<Item> ar
    function deselect(){
        if(objectEverSelected){
            console.log("type",cont.getSelectedMapObject().type)
            if(cont.getSelectedMapObject().type<10){
                cont.getSelectedMapObject().color="green";
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





                MapCircle {

                    property double lat:landmark.coordinate.latitude
                    property double lon:landmark.coordinate.longitude
                    property string name:landmark.name
                    property int type: -1

                    id: point
                    //   color: type== 0 ? "green" : type== 2 ? "grey" : "blue"
                    radius: 300
                    center: landmark.coordinate

                    //    visible: type<10 ? true : false

                    MapMouseArea{
                        //anchors.fill: parent
                        //acceptedButtons: Qt.LeftButton
                        onClicked: {

                            if(type==0){

                                //console.log("bla");

                                deselect();

                                point.color="yellow";
                                cont.setSelectedMapObject(parent);
                                cont.selectObject(name);
                                objectEverSelected=true;

                            }


                        }

                    }

                    Component.onCompleted: {
                        type= parseInt(landmark.phoneNumber);
                        console.log("TYPE", type,landmark.phoneNumber)
                        if(type<10){

                            if(type==0){

                                color="green";
                            }

                            if(type==1){

                                color="blue";
                            }

                            if(type==2){

                                color="grey";
                            }
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

                }


            }
        }


        MapObjectView {

            id: allLandmarks2
            model: landmarkModel
            delegate: Component {








                MapPolyline {
                    // property double lat:landmark.coordinate.latitude
                    // property double lon:landmark.coordinate.longitude
                    property string name: landmark.name
                    property int type: -1

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


                        type= parseInt(landmark.phoneNumber);


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


                }



            }
        }

        MapObjectView {

            id: allLandmarks3
            model: landmarkModel
            delegate: Component {




                MapGroup{
                    opacity: 0.3
                    //bacause of an error in MapPolygon we cannot add anything else than Coordinates into the polygon definition, so we define the polygon geometry here
                        Component.onCompleted: {


                            var type= parseInt(landmark.phoneNumber);


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



                    MapPolygon {
                        // property double lat:landmark.coordinate.latitude
                        // property double lon:landmark.coordinate.longitude
                        property string name: landmark.name
                        property int type: -1

                        id: polygon
                        border {color: polygonBorderColor; width: 4}
                        visible:false
                        color: polygonColor


                   /*
                        MapMouseArea{
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            onClicked: {
                                if(!polygonButtonClicked){
                                    if(type==20){

                                        //console.log("bla");

                                        deselect();

                                        polygon.border.color="yellow";
                                        cont.setSelectedMapObject(parent);
                                        cont.selectObject(name);
                                        objectEverSelected=true;

                                    }
                                }


                            }

                        }



                        Component.onCompleted: {


                            type= parseInt(landmark.phoneNumber);


                            if(type==20){
                                var num=cont.getPolygonCoordinatesNum();
                                for(var i=0; i<num;i++){
                                    var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                                    coord.latitude=cont.getPolygonCoordinateLatAt(i);
                                    coord.longitude=cont.getPolygonCoordinateLonAt(i);
                                    polygon.addCoordinate(coord);
                                    visible=true;
                                }

                            }
                        }

                        */
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

                    var paintedObject=cont.findObjectUnderCursor(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);
                    if(paintedObject){
                        deselect();

                        paintedObject.border.color="yellow";
                        cont.setSelectedMapObject(paintedObject);
                        cont.selectObject(paintedObject.name);
                        objectEverSelected=true;


                    } else {
                        deselect();
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



    Button{
        id: userManagementButton
        width: 120
        height: 50
        x: parent.width-140
        y: 20
        z: 2
        label: "Spravovat uživatele"

        onButtonClick: {
            userManagement.visible=true;
            cont.prepareAclList();
            cont.prepareTerrainUserList();


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
                map.zoomLevel += 0.5

            }
            if (event.key == Qt.Key_Minus) {

                console.log('oooQML: Key - was pressed');

                map.zoomLevel -= 1.5
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


    Component.onCompleted: {

        //  var a=Qt.createComponent("MapCircle {center: Coordinate{latitude: defaultLatitude;longitude: defaultLongitude;};radius: 10000;color: \"yellow\"}");


        // map.addMapObject(a)



    }

}
