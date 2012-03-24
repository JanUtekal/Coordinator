// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{


    Rectangle{
        width: parent.width+1

        height: parent.height/15
        color: userManagement.color
        z:2
        Rectangle{
            width: parent.width
            height: 1
            border.color: "black"
            border.width: 1
            y:parent.height
        }


    }

    TerrainUserList{

        id:aclList
        width: parent.width

        height: 13*parent.height/15+1
        y: parent.height/15

          //  radius: 10
        border.color: "black"
        border.width: 1
    }

    Rectangle{
        width: parent.width+1

        height: parent.height/5
        y: 14*parent.height/15
        color: userManagement.color
        z:2
        Rectangle{
            width: parent.width
            height: 1
            border.color: "black"
            border.width: 1

        }
    }
}
