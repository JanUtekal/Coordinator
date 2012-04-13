// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    color:"lightgrey"
    opacity:0.8
    radius:5
    border.width: 2
    border.color: "black"


    Row{
        width:9*parent.width/10
        height: 9*parent.height/10
        anchors.centerIn: parent
        spacing: 20


        Column{
             width: 6*parent.width/7 - parent.spacing
            height: parent.height
           // anchors.fill: parent
            spacing:10
            anchors.verticalCenter: parent.verticalCenter
            TextEditField{
                id: textField
                width:parent.width
                height: parent.height/5
                radius:0
               // input: "Tap here to type"

            }
            TextEditField{
                id: messageWindow
                width:  parent.width
                height: 4*parent.height/5-parent.spacing
                radius: 0
                onlyRead: true


                Component.onCompleted: {
                    messageWindow.setTopAlignment();
                }

                MouseArea{
                    anchors.fill: parent

                    onClicked: {
                        textField.loseFocus()
                     //   keyItem.focus=true

                    }
                }

            }


        }

        Column {
            width: 1*parent.width/7
            height: 6*parent.height/7
            y: 1*height/5
            spacing:3*height/6
          //  anchors.verticalCenter: parent.verticalCenter



            Button{
                id:quit
                width: parent.width
                height: parent.height/4


                label: "Send"
                onButtonClick: {
                    cont.sendMessageToUser(textField.input);
                    messageWindow.setText(cont.getCurrentDateTime()+" Me: " +textField.input+"\n"+ messageWindow.input);
                    textField.setText("");
                }
            }

            Button{
                id:back
                width: parent.width
                height: parent.height/6

                label: "Back"
                onButtonClick: {
                    messageScreen.visible=false;
                    settingsButton.visible=true;
                    messageButton.visible=true;
                }


            }
        }

    }

    MouseArea{
        anchors.fill: parent
        z: -1
        onClicked: {
            textField.loseFocus()
         //   keyItem.focus=true

        }
    }

    Connections {
        target: cont

        onNewMessageFromUser:{


            messageWindow.setText(line+"\n"+messageWindow.input);

        }

    }

}
