// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    color:"lightgrey"
    opacity:0.8
    radius:5
    border.width: 2
    border.color: "black"

    Button{
        id:quit
        width: parent.width/8
        height: parent.height/8
        x: parent.width-width-20
        y: 20
        label: "Quit"
        onButtonClick: {
            Qt.quit();
        }
    }

    Button{
        id:back
        width: parent.width/8
        height: parent.height/8
        x: parent.width-width-20
        y: parent.height-height-20
        label: "Back"
        onButtonClick: {
            settings.visible=false;
            settingsButton.visible=true;
        }
    }
}
