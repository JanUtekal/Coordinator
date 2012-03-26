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

    property bool objectEverSelected:false //slouzi ke kontrole jestli byl nekdy nejaky mapovy objekt vybran


    // property bool deleteButtonClicked: false

    // property variant array:[]

    //  property list<MapObject> array2



    //   property list<Item> ar
    function deselect(){
        if(objectEverSelected){
            if(cont.getSelectedMapObject().type<10){
                cont.getSelectedMapObject().color="green";
            } else {
                cont.getSelectedMapObject().border.color="red";
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
                    border {color: "red"; width: 4}
                    visible:false



                    MapMouseArea{
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

                    }



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

                        }
                    }


                }



            }
        }


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
                if(pointButtonClicked){

                    cont.addPoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude, userManagement.selectedMapAcl);
                    pointButtonClicked=false;
                }

                if(lineButtonClicked) {


                    if (mouse.button == Qt.LeftButton){
                        cont.addLinePoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);
                    }
                    else{
                        cont.lineReady(userManagement.selectedMapAcl);
                        lineButtonClicked=false;
                    }
                }
                deselect();

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
