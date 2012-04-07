// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
Rectangle {

    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10
    Column{

        anchors.fill: parent

        spacing: 20

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            height: 20
            width:50
            font.pointSize: 15
            text:"Error"
        }

        Text{
            id: errorText
            anchors.horizontalCenter: parent.horizontalCenter
            width:parent.width-20
            height: 80
            text:""
            wrapMode: Text.WrapAnywhere
        }

        Button{
            anchors.horizontalCenter: parent.horizontalCenter
            id: okButton
            width: 50
            height: 35

            label: "Ok"

            onButtonClick: {
               regError.visible=false;
               cont.prepareRegistration();

            }
        }
    }

    onVisibleChanged: {
        errorText.text=cont.getErrorMessage();
    }
}
