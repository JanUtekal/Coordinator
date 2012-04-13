// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 800
    height: 500
    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10

    Row{
        anchors.centerIn: parent
        width:7*parent.width/8
        height: 7*parent.height/8
        spacing: 40

        Column{
            width: 5*parent.width/7
            height: parent.height
            spacing:20

            TextEditField{
                id: messageWindow
                width:parent.width
                height: 3*parent.height/4 - parent.spacing
                radius: 0
                onlyRead: true

                Component.onCompleted: {
                    messageWindow.setBottomAlignment();
                }

            }

            TextEditField{
                id: textField
                width:parent.width
                height: parent.height/4
                radius:0
            }
        }

        Column{
            width: 2*parent.width/7 - parent.spacing
            height: parent.height
            spacing:20

            TerrainUserListMessage{
                id:userList
                width:parent.width
                height: 3*parent.height/4 - parent.spacing

            }

            Column{
                width:parent.width
                height: parent.height/4
                spacing:20


                Button{
                    id: sendButton
                    width:2*parent.width/3
                    height: parent.height/2
                    anchors.horizontalCenter: parent.horizontalCenter

                    z: 2
                    label: "Send"

                    onButtonClick: {


                        cont.sendMessageToUserAt(textField.input,userManagement.selectedUserMessage);
                        cont.setSentMessage(textField.input,userManagement.selectedUserMessage);

                        messageWindow.setText(messageWindow.input+"\n"+ cont.getCurrentDateTime()+" Me: " +textField.input);
                        textField.setText("");

                    }


                }

                Button{
                    id: backButton
                    width:2*parent.width/3
                    height: parent.height/3
                    anchors.horizontalCenter: parent.horizontalCenter

                    z: 2
                    label: "Back"

                    onButtonClick: {
                       // messageScreen.visible=false;
                        userList.pok();

                    }


                }

            }

        }






    }

    Connections {
        target: cont

        onNewMessageFromUserAt:{
            console.log("zprava",i);
            if(userManagement.selectedUserMessage===i){
                messageWindow.setText(messageWindow.input+"\n"+line);
            } else {
                userList.highlightItemAt(i);
            }
        }

        onMessagesReady:{
            messageWindow.setText("");
            var number=cont.getMessagesNum();
            for(var i=0;i<number;i++){
                messageWindow.setText(messageWindow.input+"\n"+cont.getMessageLineAt(i));
            }
        }
    }
}
