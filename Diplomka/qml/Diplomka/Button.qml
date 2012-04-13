import QtQuick 1.0

Rectangle{
    id: button
    signal buttonClick()
    property string font1: "Arial"
    property string label: "button"
 /*   Image{
        width: parent.width
        height: parent.height
        source:  buttonMouseArea.pressed ? "images/toolbutton.png" : "images/toolbutton_pressed.png"

    }
*/
    Gradient  {
         id:lightgrey
         GradientStop { position: 0; color: Qt.rgba(0, 0, 0, 0.6) }
         GradientStop { position: 1; color: Qt.rgba(0, 0, 0, 0.5) }
    }

    Gradient  {
         id:grey
         GradientStop { position: 0; color: Qt.rgba(0, 0, 0, 0.9) }
         GradientStop { position: 1; color: Qt.rgba(0, 0, 0, 0.8) }
    }

  //  border.color:"black"
   // border.width:1
    gradient: buttonMouseArea.pressed ? grey : lightgrey
    radius:8

    function alwaysPressed(pressed){
        if(pressed){
            gradient= grey
        } else {
            gradient = buttonMouseArea.pressed ? grey : lightgrey
        }
    }

    Text{
        text: label
        color: "white"
        z:1
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        //anchors.centerIn: parent
        font.family: font1
        wrapMode: Text.WordWrap
        font.pointSize: 6
        font.bold: true
    }

    onButtonClick:  {
      //  console.log("bod");

    }

    MouseArea{
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: buttonClick()
        hoverEnabled: true


    }



}
