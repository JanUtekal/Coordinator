// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    property string input: inputText.text
    property bool onlyRead:false

    color: "white"
    radius: 5
    border.width: 1
    border.color: "black"



    function setText(textt){
        inputText.text=textt;
    }

    TextInput {
        id: inputText
        width:parent.width-15
        height: parent.height

        x: 10
        color: "black"
        font.pixelSize: 15
        font.family: font1
        text: ""
        readOnly: onlyRead
        selectByMouse: true




    }
    onInputChanged: {

        inputText.text=input;

    }
}
