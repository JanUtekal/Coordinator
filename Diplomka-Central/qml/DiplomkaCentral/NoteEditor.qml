// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
Rectangle {

    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10
    Column{

        anchors.fill: parent

        spacing: 10

        Text{
            anchors.horizontalCenter: parent.horizontalCenter
            height: 20
            width:paintedWidth
            font.pointSize: 15
            text:"New Note"
        }

        Text{
            x:20
            height: 20
            width:paintedWidth
            font.pointSize: 10
            text:"Name"
        }

        TextInputField{
            id: textInput
            width: parent.width-20
            height: 20
            anchors.horizontalCenter: parent.horizontalCenter
         //   input:""
            onVisibleChanged: {
                if(visible){
                    if(cont.getSelectedMapObject()){
                        if(cont.getSelectedMapObject().note!=""){
                            if( cont.getSelectedMapObject().note.indexOf("////") !==-1){
                                textInput.setText(cont.getSelectedMapObject().note.split("////")[0]);

                            }
                        } else {
                            textInput.setText("");
                        }
                    }
                }
            }
        }

        Text{
            x:20
            height: 20
            width:paintedWidth
            font.pointSize: 10
            text:"Description"
        }

        TextEditField{
            id: textField
            width: parent.width-20
            height: 70
            anchors.horizontalCenter: parent.horizontalCenter
          //  input: ""
            onVisibleChanged: {

                if(visible){
                    if(cont.getSelectedMapObject()){
                        if(cont.getSelectedMapObject().note!=""){
                            if( cont.getSelectedMapObject().note.indexOf("////") !==-1){
                                textField.setText(cont.getSelectedMapObject().note.split("////")[1]);

                            }
                        } else {
                            textField.setText("");
                        }
                    }
                }
            }
        }

        Row{

            anchors.horizontalCenter: parent.horizontalCenter
            width:parent.width-40
            height: 50
            spacing: 50

            Button{

                id: okButton
                width: 80
                height: 35

                label: "Ok"

                onButtonClick: {
                    var newNote=textInput.input+"////"+textField.input;
                    if(newNote!==cont.getSelectedMapObject().note){

                        cont.addNoteTo(textInput.input, textField.input,cont.getSelectedMapObject().name);

                        cont.getSelectedMapObject().note=newNote;

                    }
                    noteEditor.visible=false;
                    selectingPermited=false;
                    pinchmap.deselect();

                    keyitem.focus=true;

                }

            }

            Button{

                id: backButtonNote
                width: 80
                height: 35

                label: "Back"

                onButtonClick: {
                    noteEditor.visible=false;
                    selectingPermited=false;
                    pinchmap.deselect();

                    keyitem.focus=true;
                }
            }


        }
    }


}
