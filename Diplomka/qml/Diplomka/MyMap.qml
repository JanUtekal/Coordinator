import QtQuick 1.1

import QtMobility.location 1.2

Rectangle {
   id: pinchmap

   property double defaultLatitude:  49.1969
   property double defaultLongitude: 16.6017
   property int  defaultZoomLevel: 14

   property alias mapType: map.mapType




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

      center: Coordinate {
         latitude: pinchmap.defaultLatitude
         longitude: pinchmap.defaultLongitude
      }

      MapCircle {
          property double myLat: 0.0
          property double myLon: 0.0
          id: myPos
          center: Coordinate{
              latitude: myPos.myLat
              longitude: myPos.myLon
          }

          radius: 300
          color: "yellow"
          visible:true

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
                  border {color: "red"; width: 4}
                  visible:true





                  Component.onCompleted: {


                      type= parseInt(landmark.phoneNumber);


                      if(type==10){
                          var num=cont.getLineCoordinatesNum();
                          for(var i=0; i<num;i++){
                              var coord = Qt.createQmlObject('import Qt 4.7; import QtMobility.location 1.2; Coordinate{}', map, "coord"+i);

                              coord.latitude=cont.getLineCoordinateLatAt(i);
                              coord.longitude=cont.getLineCoordinateLonAt(i);
                              line.addCoordinate(coord);
                              line.visible=true;

                              console.log("Line length", line.path.length)
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

                  Component.onCompleted: {


                      var type= parseInt(landmark.phoneNumber);


                      if(type==20){
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

                      }
                  }



                  MapPolygon {
                      // property double lat:landmark.coordinate.latitude
                      // property double lon:landmark.coordinate.longitude
                      property string name: landmark.name
                      property int type: -1

                      id: polygon
                      border {color: "blue"; width: 4}
                      visible:false
                      color: "lightblue"


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


   Component.onCompleted: {

     //  var a=Qt.createComponent("MapCircle {center: Coordinate{latitude: defaultLatitude;longitude: defaultLongitude;};radius: 10000;color: \"yellow\"}");


      // map.addMapObject(a)



   }
}
