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

        Column{
            width:3*parent.width/8
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
                text: "Name"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Surname"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Username"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Text{
                text: "Password"
                color: "black"
                z:1
                font.pixelSize: 15
                font.family: font1
            }

            Rectangle{
               width: 1
               height:30
               color:"transparent"
            }


            Text{
                text: "Captcha"
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
            Row{
                spacing: 30
                Image{
                    id: captcha
                    width: 120
                    height: 40
                    source: "";
                    Connections{
                        target: cont

                        onCaptchaReady:{
                            captcha.source=cont.getCaptchaUrl();
                            captcha.visible=false;
                            captcha.visible=true;
                            console.log(captcha.source)
                        }
                    }


                }

                Button{
                    width:60
                    height: 40


                    label: "Refresh"

                    onButtonClick: {

                        cont.prepareRegistration();
                    }

                }
            }

            TextInputField{
                id: textField5
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
        label: "Create"

        onButtonClick: {


            cont.registerUser(textField3.input, textField4.input, textField5.input)
            keyitem.focus=true;

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
            newTerrainUser.visible=false;
            userManagement.color="lightgrey"
            cont.stopRegistration();

            keyitem.focus=true;
        }

    }

    RegistrationError{
        id: regError
        width: 200
        height: 200
        anchors.centerIn: parent
        visible:false
    }

    Connections{
        target: cont
        onRegistrationError:{
            regError.visible=true;
        }

        onRegistrationSuccess:{

            cont.createNewTerrainUser(textField0.input, textField1.input, textField2.input, textField3.input, textField4.input);
            userManagement.color="lightgrey"
            userManagement.selectedUser=-1;
            cont.prepareTerrainUserList();
            newTerrainUser.visible=false;
        }
    }

    onVisibleChanged: {
        textField0.setText("");
        textField1.setText("");
        textField2.setText("");
        textField3.setText("");
        textField4.setText("");
    }
}
