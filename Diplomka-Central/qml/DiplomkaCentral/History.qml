// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 800
    height: 500
    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10


    Button{
        id: backButton
        width: 120
        height: 50
        x: parent.width-150
        y: parent.height-80
        z: 2
        label: "Back"

        onButtonClick: {
            history.visible=false;

        }

    }


    Button{
        id: showButton
        width: 120
        height: 50
        x: 30
        y: parent.height-80
        z: 2
        label: "Show"

        onButtonClick: {
            history.visible=false;
            terrainUserFromAclHistoryListMap.visible=true;
            aclListHistoryMap.visible=true;
            aclListMap.visible=false;
            leftButtons.visible=false;
            closeHistoryButton.visible=true;
            pinchmap.selectingPermited=true;
            cont.clearMapObjects();
        }

    }

    Row{
        width: parent.width-20
        height: parent.height-20
        x:50
        y:20

        spacing: 40

        Row{
            spacing: 20


            Column{
                spacing: 10
                width: parent.parent.width/4
                height: 5*parent.parent.height/7

                Text{

                    text:"Events between dates"
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter

                }

                AclListHistory{
                    width:parent.width
                    height: parent.height
                    //color: userManagement.color
                }

            }

            Column{
                spacing: 10
                width: parent.parent.width/4
                height: 5*parent.parent.height/7

                Text{

                    text:"Users for event"
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter

                }

                TerrainUserFromAclHistoryList{
                    width:parent.width
                    height: parent.height
                    //color: userManagement.color
                }

            }

            Column{
                spacing: 10
                width: parent.parent.width/3
                height: 5*parent.parent.height/7

                Text{

                    text:"Chat for user"
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter

                }

                TextEditField{
                    id: messageWindow
                    width:parent.width+10
                    height: parent.height
                    radius: 0
                    onlyRead: true

                    Component.onCompleted: {
                        messageWindow.setBottomAlignment();
                    }

                }

            }
        }

    }

    Connections{
        target: cont

        onMessagesHistoryReady:{
            messageWindow.setText("");
            var number=cont.getMessagesHistoryNum();
            for(var i=0;i<number;i++){
                messageWindow.setText(messageWindow.input+"\n"+cont.getMessageHistoryLineAt(i));
            }
        }
    }
}
