// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 400
    height: 300
    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10

    Row{
        width: parent.width-20
        height: parent.height-20
        x:20
        y:20

        Column{
            width:parent.width/4
            height: 2*parent.height/3
            spacing: 20

            Text{
                text: "ID"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Jméno"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Příjmení"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "JID"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Heslo"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }
        }

        Column{
            width:parent.width/2
            height: 2*parent.height/3
            spacing: 17

            TextInputField{
                id: textField0
                width: parent.width
                height: 20
            }

            TextInputField{
                id: textField1
                width: parent.width
                height: 20
            }

            TextInputField{
                id: textField2
                width: parent.width
                height: 20
            }

            TextInputField{
                id: textField3
                width: parent.width
                height: 20
            }

            TextInputField{
                id: textField4
                width: parent.width
                height: 20
            }


        }

    }


    Button{
        id: saveButton
        width: 120
        height: 50
        x: 30
        y: parent.height-80
        z: 2
        label: "Vytvořit"

        onButtonClick: {
            newTerrainUser.visible=false;
            cont.createNewTerrainUser(textField0.input, textField1.input, textField2.input, textField3.input, textField4.input);
            userManegement.color="lightgrey"
            userManagement.selectedUser=-1;
            cont.prepareTerrainUserList();


        }

    }

    Button{
        id: backButton
        width: 120
        height: 50
        x: parent.width-140
        y: parent.height-80
        z: 2
        label: "Zpět"

        onButtonClick: {
            newTerrainUser.visible=false;
            userManegement.color="lightgrey"

        }

    }

}
