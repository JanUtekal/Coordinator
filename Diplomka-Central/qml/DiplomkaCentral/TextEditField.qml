// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    property string input: inputText.text

    color: "white"
    radius: 5
    border.width: 1
    border.color: "black"

    function setText(textt){
        inputText.text=textt;
    }

    TextEdit {
        id: inputText
        width:parent.width
        height: parent.height

        x: 10
        color: "black"
        font.pixelSize: 15
        font.family: font1
        text: ""
        wrapMode: TextEdit.WordWrap

        onVisibleChanged: {
            //console.log("focus"+inputText.activeFocus)
            inputText.focus=false;

        }
    }
}
