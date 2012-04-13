// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {

    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10

    Row{
        width: parent.width-20
        height: parent.height-20
        x:20
        y:20
        spacing: 20

        Column{
            width:parent.width/4
            height: 2*parent.height/3
            spacing: 20

            Text{
                text: "Name"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }


            Text{
                text: "Duration (hours)"
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


            Row{
                spacing: 10
                width: parent.width

                Button{
                    id: minusButton
                    width: textField2.width
                    height: textField2.height

                    z: 2
                    label: "-"

                    onButtonClick: {
                        if(textField2.input>0){
                            textField2.input-=1;
                        }
                    }

                }

                TextInputField{
                    id: textField2
                    width: parent.width/4
                    height: 20
                    onlyRead: true
                    input: "0"

                }



                Button{
                    id: plusButton
                    width: textField2.width
                    height: textField2.height

                    z: 2
                    label: "+"

                    onButtonClick: {
                        textField2.input=Number(textField2.input*1+1);

                    }

                }
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
        label: "Create"

        onButtonClick: {

            var validity="null";
            if(textField2.input!="null"){
                validity=textField2.input;
            }

            cont.createNewAcl(textField1.input,validity);
            userManagement.color="lightgrey"
            userManagement.selectedAcl=-1;
            cont.prepareAclList();

            keyitem.focus=true;
            newACL.visible=false;
        }

    }

    Button{
        id: backButton
        width: 120
        height: 50
        x: parent.width-140
        y: parent.height-80
        z: 2
        label: "Back"

        onButtonClick: {
            newACL.visible=false;
            userManagement.color="lightgrey"

            keyitem.focus=true;
        }

    }


    onVisibleChanged: {

        textField1.setText("");
        textField2.setText("0");

    }
}
