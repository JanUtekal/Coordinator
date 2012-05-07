// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//screen with settings
Rectangle {
    color:"lightgrey"
    opacity:0.8
    radius:5
    border.width: 2
    border.color: "black"
///////

    Button{
        id:quit
        width: parent.width/8
        height: parent.height/8
        x: parent.width-width-20
        y: 20
        label: "Konec"
        onButtonClick: {
            Qt.quit();
        }
    }

    ButtonPicture{
        id:back
        width: parent.width/8
        height: parent.height/8
        x: parent.width-width-20
        y: parent.height-height-20
      //  label: "zpet"
        imageSource: "images/back.png"
        onButtonClick: {
            settings.visible=false;
            settingsButton.visible=true;
            messageButton.visible=true;
        }
    }
    Column{
        width: 4*parent.width/5
        height: parent.height
        spacing: (2*parent.height/5-40)/10
        x:20
        y:20



        Rectangle{
            width: parent.width
            height: parent.width/5
            color:"transparent"
            radius:5
            border.width:1
            border.color: "black"

            Column{
                width: parent.width
                height: parent.height
                x:20
                y:10
                spacing: 12

                Text{
                    width: parent.width
                    height: parent.height/3

                    text: "Přihlášení"
                    font.pointSize: textSize
                }

                Row{
                    width: parent.width
                    height: parent.height/2


                    spacing:(parent.width-usernameInput.width-passwordInput.width-40)/11
                    TextInputField{
                        id: usernameInput
                        width: 2*parent.width/5
                        height:35
                        //anchors.horizontalCenter: parent.horizontalCenter
                        input:"terrainuser2@jabber.cz"

                    }

                    TextInputField{
                        id: passwordInput
                        width: parent.width/4
                        height: 35
                        // anchors.horizontalCenter: parent.horizontalCenter
                        input:"asasasd"
                        Component.onCompleted: {
                            setPasswordType();
                        }

                    }

                    Button{
                        id:connect
                        //  anchors.horizontalCenter: parent.horizontalCenter
                        width: parent.width/5
                        height: 35


                        label: "Připoj"
                        onButtonClick: {
                            cont.reconnectMe(usernameInput.input,passwordInput.input);
                        }
                    }



                }
            }
        }


        Rectangle{
            width: parent.width
            height: parent.width/5
            color:"transparent"
            radius:5
            border.width: 1
            border.color: "black"

            Column{
                width: parent.width
                height: parent.height
                x:20
                y:10
                spacing: 10

                Text{
                    width: parent.width
                    height: parent.height/3
                    text: "Typ mapového podkladu"
                    font.pointSize: textSize
                }

                Row{
                    width: parent.width
                    height: parent.height/2


                    spacing:30

                    Button{
                        id:type1
                        //  anchors.horizontalCenter: parent.horizontalCenter
                        width: 120
                        height: 3*parent.height/4


                        label: "Klasická"
                        onButtonClick: {
                            map.setType(1);
                            alwaysPressed(true);
                            type4.alwaysPressed(false);
                            type2.alwaysPressed(false);
                        }

                        Component.onCompleted: {
                            alwaysPressed(true);
                        }
                    }

                    Button{
                        id:type2
                        //  anchors.horizontalCenter: parent.horizontalCenter
                        width: 120
                        height: 3*parent.height/4


                        label: "Satelitní"
                        onButtonClick: {
                            map.setType(2);
                            alwaysPressed(true);
                            type1.alwaysPressed(false);
                            type4.alwaysPressed(false);
                        }
                    }


                    Button{
                        id:type4
                        //  anchors.horizontalCenter: parent.horizontalCenter
                        width: 120
                        height: 3*parent.height/4


                        label: "Terénní"
                        onButtonClick: {
                            map.setType(4);
                            alwaysPressed(true);
                            type1.alwaysPressed(false);
                            type2.alwaysPressed(false);
                        }
                    }


                }
            }
        }

        Rectangle{
            width: parent.width
            height: parent.width/5
            color:"transparent"
            radius:5
            border.width: 1
            border.color: "black"

            Column{
                width: parent.width
                height: parent.height
                x:20
                y:10
                spacing: 10

                Text{
                    width: parent.width
                    height: parent.height/3
                    text: "Sledování na mapě"
                    font.pointSize: textSize
                }


                Button{
                    property bool on:true
                    id:sledovani
                    //  anchors.horizontalCenter: parent.horizontalCenter
                    width: 120
                    height: 3*parent.height/8


                    label: "Zapnuto"
                    onButtonClick: {
                        if(on){
                           sledovani.label="Vypnuto";
                           on=false;
                            alwaysPressed(false);
                            pinchmap.watchLocation=false;
                        } else {
                            sledovani.label="Zapnuto";
                            on=true;
                            alwaysPressed(true);
                             pinchmap.watchLocation=true;

                        }


                    }

                    Component.onCompleted: {
                        alwaysPressed(true);
                    }
                }

            }
        }
    }

}
