// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//screen of note text displayed when clicked at the note
Rectangle {
    property color noteTextColor: Qt.rgba(1, 1, 1, 0.8)

    border.width: 2
    border.color: "black"
    radius: 5
    color: noteTextColor
    visible: false


    Flickable{//text
      //  z:-1
        flickableDirection: Flickable.VerticalFlick
        width: parent.width-10
        height: parent.height
        x: 5
       // contentWidth: 360
      //  contentHeight: 50//text1.height + 50
        clip: true


        Rectangle{
            width: parent.width
            color:"transparent"
         //   height: 100

            Text{
                id: text1
                text: ""
              //  x: 10
             //   y: 10

                font.pointSize: textSize
                width: parent.width
                wrapMode: Text.WordWrap

            }

        }
    }

    Connections{
        target: cont
        onDisplayNoteText: {
            if(mapObject.note!=""){
                var text=mapObject.note.split("////")[1];
                if(text!=""){
                    nodeTextDisplay.visible=true;

                    text1.text=text
                }
            }
        }

        onHideNoteText:{
            nodeTextDisplay.visible=false;
        }

    }

}
