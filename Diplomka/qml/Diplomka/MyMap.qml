import QtQuick 1.1

import QtMobility.location 1.2

//provides map, displays mapobjects and contains all gui elements
Rectangle {
    id: pinchmap

    property double defaultLatitude:  49.2166
    property double defaultLongitude: 17.7611
    property int  defaultZoomLevel: 14

    property alias mapType: map.mapType


    property color pointColor: Qt.rgba(1, 1, 1, 0.8)
    property color lineColor: "red"
    property color polygonBorderColor:  "blue"
    property color polygonColor:  Qt.rgba(0, 1, 1, 0.1)
    property bool watchLocation: true


    property int textSize:18

    // property variant array:[]

    //  property list<MapObject> array2

    //   property list<Item> ar

    Map {

        //    property variant array:Array()

        id: map
        connectivityMode: Map.OfflineMode
        anchors.fill: parent
        zoomLevel: pinchmap.defaultZoomLevel
        plugin: Plugin { name: "nokia" }
        mapType: Map.StreetMap

        function setType(type){
            mapType=type;

        }

        center: Coordinate {
            latitude: pinchmap.defaultLatitude
            longitude: pinchmap.defaultLongitude
        }



        MapGroup{
            id: myPosition
            MapImage{

                property double myLat: 0.0
                property double myLon: 0.0

                 id: myPos
                coordinate: Coordinate{
                    latitude: myPos.myLat
                    longitude: myPos.myLon
                }

                source: "images/pointerblue.png"
                offset.x: -15
                offset.y: -80
                z:1





            }




            MapText{
                id: background
                coordinate: Coordinate{
                    latitude: myPos.myLat
                    longitude: myPos.myLon
                }

                //   text:"toto je komentar"
                offset.y: 20
                text:""
                color: pointColor
                font.pointSize: textSize
                font.family: "Courier"
                font.bold: true
                z: 0

                Component.onCompleted: {
                    background.makeBackGround(2);//myname.text.length);
                }
                function makeBackGround(length) {


                        text="";
                        for(var i=0;i<length;i++){//

                            text+="█";
                        }




                }



            }


            MapText{
                id: myname
                coordinate: Coordinate{
                    latitude: myPos.myLat
                    longitude: myPos.myLon
                }
                offset.y: 20
                text:"Já"

                font.pointSize: textSize
                z:3
                  font.family: "Courier"
                  font.bold: true


            }


        }
        /*   MapObjectView {

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

                      }

                  }

              }

          }*/
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
                        offset.y: -80
                        z:1

                        Component.onCompleted: {
                            type=landmark.radius
                            console.log("TYPE", type,landmark.radius)
                            //  circle.color=pointColor;
                            if(type<10){

                                if(type==1){

                                  note=name;
                                }

                               if(type==2){

                                 note=name;
                               }
                                cont.createMapObjectReference(point,point.name,0,"");

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
                                var name=point.note.split("////")[0];

                                background.makeBackGround(name.length);
                                mapT.text=name;

                                var text=point.note.split("////")[1];
                                if(text && text!==""){

                                        mapT.font.underline=true;
                                        mapT.color="blue";

                                }

                            }


                        }


                    }


                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        offset.y: 20
                        z: 3
                        font.family: "Courier"
                        font.bold: true
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
                        offset.y: 20
                        font.family: "Courier"
                        font.bold: true
                        function makeBackGround(length) {

                            if(point.type<10){
                                text="";
                                for(var i=0;i<length;i++){//

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
                                cont.createMapObjectReference(line,line.name,1,landmark.description);//to be able to select the object we need to make a reference on it

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

                                var text=line.note.split("////")[1];
                                if(text!==""){
                                   mapT.font.underline=true;
                                   mapT.color="blue";
                                }
                            }
                        }


                    }

                    MapText{
                        id: mapT
                        coordinate: landmark.coordinate
                        text:""
                        font.pointSize: textSize
                        z: 3
                        offset.y: 20
                        font.family: "Courier"
                        font.bold: true

                    }

                    MapText{
                        id: background
                        coordinate: landmark.coordinate
                        //   text:"toto je komentar"
                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 2
                        offset.y: 20
                        font.family: "Courier"
                        font.bold: true
                        function makeBackGround(length) {

                            if(line.type>=10 && line.type<20){
                                text="";
                                for(var i=0;i<length;i++){//

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
                            cont.createMapObjectReference(polygon,polygon.name,2,landmark.description);//to be able to select the object we need to make a reference on it

                            polygon.type=type;

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

                            var text=polygon.note.split("////")[1];
                            if(text!==""){
                               mapT.font.underline=true;
                               mapT.color="blue";
                            }
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
                        offset.y: 20
                        font.family: "Courier"
                        font.bold: true
                    }

                    MapText{
                        id: background
                        coordinate: landmark.coordinate
                        //   text:"toto je komentar"
                        text:""
                        color: pointColor
                        font.pointSize: textSize
                        z: 2
                        font.family: "Courier"
                        font.bold: true
                        offset.y: 20
                        function makeBackGround(length) {

                            if(polygon.type>=20){
                                text="";
                                for(var i=0;i<length;i++){//

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

    }

    PinchArea {
        id: pincharea

        property double __oldZoom

        anchors.fill: parent

        function calcZoomDelta(zoom, percent) {
            //console.log(percent,Math.log(percent)/Math.log(2));
            return zoom + Math.log(percent)/Math.log(2)
        }

        onPinchStarted: {
            __oldZoom = map.zoomLevel
        }

        onPinchUpdated: {
            map.zoomLevel = calcZoomDelta(__oldZoom, pinch.scale)
        }

        onPinchFinished: {
            map.zoomLevel = calcZoomDelta(__oldZoom, pinch.scale)
        }
    }

    MouseArea {
        id: mousearea

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

        onCanceled: {
            __isPanning = false;
        }

        onClicked: {
            cont.getObjectUnderCursor(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude, map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude, map.zoomLevel)
        }
    }
    /*
    Connections {
        target: cont

        onRefresh:{

            for(var i=0;i<cont.getMapPointNum();i++){
                map.removeMapObject(cont.getFromVlistAt(i));
            }
            cont.clearVlist();

            var num= cont.getPointNum();
            console.log("ooooooooooo",num)
            for(var i=0;i<num;i++){



                var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                coord.latitude=cont.getLatFor(i);
                coord.longitude=cont.getLonFor(i);

//                console.log(coord.id)

                var marker = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; MapCircle{}', map, "marker"+i);
               // marker.id=i;
                marker.center = coord;
                marker.color = "red";
                marker.radius = 300;

              //  console.log("i je",i,cont.getLatFor(i),cont.getLonFor(i),cont.getJidFor(i))

              //  array.push(marker);
                cont.setToVlist(marker);

              //  array[0]=1;

           //     map.array.push(1);
              //  console.log(array.length);
              //  console.log(cont.getFromVlist());
              //  var o=cont.getFromVlist();
              //  map.removeMapObject(o);

                map.addMapObject(cont.getFromVlistAt(0));


         //       bla.push(marker);
         //       console.log(bla.length);
              //  console.log(array.length);
           //     map.removeMapObject(bla[0]);
            }

        }

        onRefreshMyPosition:{
            myPos.myLat=cont.getLatForMe();
            myPos.myLon=cont.getLonForMe();
          //  myPos.visible=false;
          //  myPos.visible=true;
            map.removeMapObject(myPos);
            map.addMapObject(myPos);


        }

    }

*/
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

    Item {
        id: keyItem
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

        }

    }

    Connections{
        target: cont
        onChangeNoteOf: {
            cont.getMapObjectReference(name).note=note;

        }
    }

    NoteTextDisplay{

        id: nodeTextDisplay
        width: parent.width -10
        height: parent.height/6 -10
        x: 5
        y: parent.height-height-5


    }

    Settings{
        id:settings
        width: 11*parent.width/12
        height: 11*parent.height/12
        anchors.centerIn: parent
        visible:false
    }

    MessageScreen{
        id:messageScreen
        width: 11*parent.width/12
        height: 11*parent.height/12
        anchors.centerIn: parent
        visible:false
    }

    ButtonPicture{
        id:settingsButton
        width: parent.width/8
        height: parent.height/8
        x: 20
        y: 20
      //  label: "Nastavení"
        imageSource: "images/settings.png"
        onButtonClick: {
            settings.visible=true;
            settingsButton.visible=false;
            messageButton.visible=false;
        }
    }

    ButtonPicture{
        id:messageButton
        width: parent.width/8
        height: parent.height/8
        x: parent.width-width-20
        y: 20
       // label: "Zprávy"
        imageSource: "images/message.png"
        onButtonClick: {
            messageScreen.visible=true;
            settingsButton.visible=false;
            messageButton.visible=false;
            messageButton.highlighted=false;
        }
    }


    Component.onCompleted: {

        //  var a=Qt.createComponent("MapCircle {center: Coordinate{latitude: defaultLatitude;longitude: defaultLongitude;};radius: 10000;color: \"yellow\"}");


        // map.addMapObject(a)



    }

    Connections{
        target: cont
        onUpdatePositionForMapUser:{

            if(userPoint){
                userPoint.lat=lat;
                userPoint.lon=lon;
            }


        }

        onSetMapUserOffline:{
            if(userPoint){

                userPoint.type=2;
            }
        }

        onRefreshMyPosition:{
            myPos.myLat=cont.getLatForMe();
            myPos.myLon=cont.getLonForMe();
          //  myPos.visible=false;
          //  myPos.visible=true;
      //      map.removeMapObject(myPos);
       //     map.addMapObject(myPos);


            myPosition.visible=false
            myPosition.visible=true
            if(watchLocation){
                map.center.latitude=myPos.myLat;
                map.center.longitude=myPos.myLon
            }

        }
    }


}
