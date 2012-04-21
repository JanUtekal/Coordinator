// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

//multi line field of text
Rectangle{
    property string input: inputText.text
    property bool onlyRead:false
    color: "white"
    radius: 5
    border.width: 1
    border.color: "black"

    function setTopAlignment(){
        inputText.verticalAlignment=TextEdit.AlignTop
    }

    function setText(textt){
        inputText.text=textt;
    }

    function loseFocus(){
        console.log("foc")
        inputText.closeSoftwareInputPanel();
       inputText.focus = false;

    }

    Flickable {
        id: flick
        width:parent.width-20
        height: parent.height-20
     //   contentWidth: inputText.paintedWidth
     //   contentHeight: inputText.paintedHeight
        clip: true
        flickableDirection: Flickable.VerticalFlick

        function ensureVisible(r)
        {
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;
            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
        }

        TextEdit {
            id: inputText
            width:parent.width
        //    height: parent.height

            x: 10
            color: "black"
            font.pixelSize: 15

            text: ""
            wrapMode: TextEdit.WrapAnywhere
            readOnly: onlyRead


        //    selectByMouse: true
        //    y: flick.visibleArea.yPosition * flick.height
            height: flick.visibleArea.heightRatio * flick.height
        //    onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
            onTextChanged: {
              // flick.returnToBounds()
            }

            onVisibleChanged: {

            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (!inputText.activeFocus) {
                        inputText.forceActiveFocus();
                        inputText.openSoftwareInputPanel();

                    } else {
                      //  inputText.focus = false;
                         inputText.closeSoftwareInputPanel();
                        inputText.focus = false;

                    }
                }

            }
        }

    }
}
