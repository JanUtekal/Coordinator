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
    property bool objectEverSelected:false //slouzi ke kontrole jestli byl nekdy nejaky mapovy objekt vybran


    // property bool deleteButtonClicked: false

    // property variant array:[]

    //  property list<MapObject> array2



    //   property list<Item> ar
    function deselect(){
        if(objectEverSelected){
            cont.getSelectedMapObject().color="green";
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
                    property int type: landmark.phoneNumber=="1" ? 1 : landmark.phoneNumber=="2" ? 2 : 0

                    id: color1
                    color: type== 0 ? "green" : type== 2 ? "grey" : "blue"
                    radius: 300
                    center: landmark.coordinate

                    MapMouseArea{
                        //anchors.fill: parent
                        //acceptedButtons: Qt.LeftButton
                        onClicked: {

                            if(type==0){

                                //console.log("bla");

                                deselect();

                                color1.color="yellow";
                                cont.setSelectedMapObject(parent);
                                cont.selectObject(lat,lon);
                                objectEverSelected=true;

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

                    cont.addPoint(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);
                    pointButtonClicked=false;
                } else {


                    //    if (mouse.button == Qt.RightButton){
                    //cont.selectObject(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude);
                }
                deselect();

            }

            /*     onCanceled: {
                __isPanning = false;
            }*/



        }

    }
    Button{
        id: pointButton
        width: 120
        height: 50
        x: 20
        y: 20
        z: 2
        label: "Přidat bod"

        onButtonClick: {
            pointButtonClicked=true;

        }

    }

    Button{
        id: testButton
        width: 120
        height: 50
        x: 20
        y: 90
        z: 2
        label: "test"

        onButtonClick: {
            cont.testButtonOperation();

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

    AclListElement{
        width: 150
        height: 400
        color: userManagement.color

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
