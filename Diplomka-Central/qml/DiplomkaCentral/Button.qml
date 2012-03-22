import QtQuick 1.0

Rectangle{
    id: button
    signal buttonClick()
    property string font1: "Nokia Pure"
    property string label: "button"
    Image{
        width: parent.width
        height: parent.height
        source:  buttonMouseArea.pressed ? "images/toolbutton.png" : "images/toolbutton_pressed.png"

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
