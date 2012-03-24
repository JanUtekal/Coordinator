
import QtQuick 1.1



Rectangle {

    // color: "white"


    function create(n){
        mod.clear();
        for(var i=0;i<n;i++){
            mod.append({

                           "num":i,


                       })

        }
    }

    border.color: "black"
    border.width: 1

    ListModel {
        id:mod

    }


    ListView {
        id: view

        width: parent.width
        height: parent.height

        //    x:5
        // highlightRangeMode:ListView.StrictlyEnforceRange
        //x:0

        clip:true
        model: mod
        //  spacing: 2

        delegate:
            Rectangle{
            //z:-1017

            width: view.width
            height:  30
            border.color: "black"
            border.width: 1
            color: num==userManagement.selectedUser ? "grey" : "transparent"


            Text{
                id: label
                text: cont.getTerrainUserNameAt(num) + " " + cont.getTerrainUserSurnameAt(num)
                x:20

                anchors.verticalCenter: parent.verticalCenter

                font.family: font1
                font.pixelSize: 15
            }

            Rectangle{
                height: parent.height
                width:height
                color:"transparent"
                x:parent.width-width
                border.width:1
                border.color: "black"
                z:2

                Text{

                    text: "x"


                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    font.family: font1
                    font.pixelSize: 15
                    color:"red"
                }



                MouseArea{
                    id: removeMouseArea
                    anchors.fill: parent
                    onClicked: {

                        cont.removeTerrainUser(num);
                        userManagement.selectedUser=-1;
                        cont.prepareTerrainUserList();

                    }

                    hoverEnabled: true

                }

            }

            MouseArea{
                id: letterMouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("click",num,cont.getTerrainUserNameAt(num))
                    userManagement.selectedUser=num;
                }

                hoverEnabled: true

            }


            Component.onCompleted: {
               // console.log(num,y)
          /*      if(num==-1 || num>=cont.getTerrainUserNum()){
                    height=1;
                    visible=false;

                } else {
                    label.text=cont.getTerrainUserNameAt(num) + " " + cont.getTerrainUserSurnameAt(num);
                }*/
            }






        }


    }




    Connections{
        target: cont

        onTerrainUserListReady:{
            console.log("tvorim list",cont.getTerrainUserNum());
            create(cont.getTerrainUserNum());
        }

    }

    onVisibleChanged: {

        if(visible){

            //  letterReady=0;
        } else {
            //   mod.clear();
            // visible=false;

        }

    }


}

