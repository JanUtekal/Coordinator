// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    property int selectedUser:-1
    property int selectedAclUser:-1
    property int selectedAcl:-1
    property int selectedMapAcl:-1

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
        label: "Vytvořit nového uživatele v terénu"

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
        label: "Vytvořit nový ACL"

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

        spacing: 40

        Row{
            spacing: 20

            TerrainUserList{
                width: parent.parent.width/4
                height: 5*parent.parent.height/7
                //color: userManagement.color
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
                    label: ">>"

                    onButtonClick: {
                        if(userManagement.selectedUser!=-1 && userManagement.selectedAcl!=-1){
                            cont.setTerrainUserAcl(userManagement.selectedUser,userManagement.selectedAcl);
                            cont.prepareTerrainUserFromAclList(userManagement.selectedAcl);
                            userManagement.selectedAclUser=-1
                        }

                    }

                }

                Button{
                    id: userLeftButton
                    width: 50
                    height: 50
                    //  x: 180

                    z: 2
                    label: "<<"

                    onButtonClick: {
                        console.log("fff",selectedAclUser)
                        if(userManagement.selectedAclUser!=-1 && userManagement.selectedAcl!=-1){
                            cont.unsetTerrainUserAcl(userManagement.selectedAclUser);
                            cont.prepareTerrainUserFromAclList(userManagement.selectedAcl);
                            userManagement.selectedAclUser=-1;
                        }

                    }

                }
            }

        }

        TerrainUserFromAclList{
            id: terrainUserFromAclList
            width: parent.width/5
            height: 4*parent.height/7
            y:parent.height/10
         //   color: userManagement.color
        }

        AclList{
            width: parent.width/4
            height: 5*parent.height/7
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

}
