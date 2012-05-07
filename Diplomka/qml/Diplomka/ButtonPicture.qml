import QtQuick 1.0

Rectangle{
    id: button
    signal buttonClick()
    property string font1: "Arial"
    property string label: "button"
    property bool highlighted: false

    property string imageSource: ""
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
        GradientStop { position: 0; color: Qt.rgba(0.2, 0.2, 0.2, 0.9) }
        GradientStop { position: 1; color: Qt.rgba(0, 0, 0, 0.8) }
    }

    Gradient  {
        id:yellow
        GradientStop { position: 0; color: Qt.rgba(0.9, 0.9, 0, 0.7) }
        GradientStop { position: 1; color: Qt.rgba(0.7, 0.7, 0, 0.6) }
    }

    //  border.color:"black"
    // border.width:1
    gradient: highlighted ? yellow : buttonMouseArea.pressed ? grey : lightgrey
    radius:8
    smooth:true

    function alwaysPressed(pressed){
        if(pressed){
            gradient= grey
        } else {
            gradient = buttonMouseArea.pressed ? grey : lightgrey
        }
    }


        Image{
            id:img
            height: 3*parent.height/4
            fillMode: Image.PreserveAspectFit
            source:imageSource
            smooth: true
            anchors.centerIn: parent

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
