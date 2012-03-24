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
                text: "Název"
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
                id: textField1
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
            newACL.visible=false;
            cont.createNewAcl(textField1.input);
            userManagement.color="lightgrey"
            userManagement.selectedAcl=-1;
            cont.prepareAclList();
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
            newACL.visible=false;
            userManegement.color="lightgrey"

        }

    }

}
