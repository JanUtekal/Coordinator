// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property int selectedUser:-1
    property int selectedAclUser:-1
    property int selectedAclHistoryUser:-1
    property int selectedAcl:-1
    property int selectedMapAcl:-1
    property int selectedHistoryAcl:-1
    property int selectedUserMessage:-1

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
        label: "Zpět"
        imageSource: "images/back.png"
        onButtonClick: {
            userManagement.visible=false;

        }

    }

    Button{
        id: newTerrainUserButton
        width: 120
        height: 50
        x: 30
        y: parent.height-80
        z: 2
        label: "Nová jednotka"
        imageSource: "images/user.png"
        onButtonClick: {
            cont.prepareRegistration();
            newTerrainUser.visible=true;
            userManagement.color="darkgrey";

        }

    }

    Button{
        id: newAclButton
        width: 120
        height: 50
        x: 180
        y: parent.height-80
        z: 2
        label: "Nová akce"

        onButtonClick: {
            newACL.visible=true;
            userManagement.color="darkgrey";

        }

    }


    Row{
        width: parent.width-20
        height: parent.height-20
        x:50
        y:20

        spacing: 20

        Row{
            spacing: 20


            Column{
                spacing: 10
                width: parent.parent.width/4
                height: 5*parent.parent.height/7

                Text{

                    text:"Všechny jednotky"
                    font.pointSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter

                }

                TerrainUserList{
                    width:parent.width
                    height: parent.height
                    //color: userManagement.color
                }

            }

            Column{
                y: 3*(terrainUserFromAclList.y + terrainUserFromAclList.height)/7

                spacing: 30




                Button{
                    id: userRightButton
                    width: 50
                    height: 50
                    //   x: 180
                    // y: parent.height-80
                    z: 2
                    label: ""
                    imageSource: "images/arrowright.png"

                    onButtonClick: {
                        if(userManagement.selectedUser!=-1 && userManagement.selectedAcl!=-1){
                            cont.setTerrainUserAcl(userManagement.selectedUser,userManagement.selectedAcl);
                            cont.prepareTerrainUserFromAclList(userManagement.selectedAcl);
                            userManagement.selectedAclUser=-1
                            cont.prepareTerrainUserList();
                        }

                    }

                }

                Button{
                    id: userLeftButton
                    width: 50
                    height: 50
                    //  x: 180

                    z: 2
                    label: ""
                    imageSource: "images/arrowleft.png"

                    onButtonClick: {
                        console.log("fff",selectedAclUser)
                        if(userManagement.selectedAclUser!=-1 && userManagement.selectedAcl!=-1){
                            cont.unsetTerrainUserAcl(userManagement.selectedAclUser);
                            cont.prepareTerrainUserFromAclList(userManagement.selectedAcl);
                            userManagement.selectedAclUser=-1;
                            cont.prepareTerrainUserList();
                        }

                    }

                }
            }

        }

        Column{
            spacing: 40
            width: parent.width/5
            height: 4*parent.height/7


            Text{

                text:"Přiřazené jednotky"
                font.pointSize: 12
                anchors.horizontalCenter: parent.horizontalCenter

            }

            TerrainUserFromAclList{
                id: terrainUserFromAclList
                width:parent.width
                height: parent.height
                y:parent.height/10
             //   color: userManagement.color
            }

        }

        Column{
            spacing: 10
            width: 3*parent.width/10
            height: 5*parent.height/7

            Text{

                text:"Akce"
                font.pointSize: 12
                anchors.horizontalCenter: parent.horizontalCenter

            }

            AclList{
                width:parent.width
                height: parent.height
            }

        }


    }



    NewTerrainUser{
        id: newTerrainUser
        anchors.centerIn: parent
        visible: false;
        width: 400
        height: 400
        z:2
    }

    NewACL{
        id: newACL
        anchors.centerIn: parent
        visible: false;
        width: 400
        height: 300
        z:2
    }


    Connections{
        target:cont

        onUserAclUpdated:{
            console.log("TTTTTTTTTTT")

            cont.prepareTerrainUserList();

            userManagement.selectedAcl=-1;
            userManagement.selectedAclUser=-1
            terrainUserFromAclList.create(0);
        }
    }

}
