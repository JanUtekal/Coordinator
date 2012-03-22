// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 1024
    height: 768
    property string font1: "Nokia Pure"

    MyMap{
        width: parent.width
        height: parent.height
    }

}
