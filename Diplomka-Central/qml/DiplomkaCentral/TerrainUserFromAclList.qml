
import QtQuick 1.1



Rectangle {

    // color: "white"


    function create(n){
        mod.clear();
        for(var i=-1;i<n+1;i++){
            mod.append({

                           "num":i,


                       })

        }
    }


    ListModel {
        id:mod

    }


    ListView {
        id: view

        width: parent.width
        height: parent.height
        y:-1
        //    anchors.fill:parent
        //    x:5
        // highlightRangeMode:ListView.StrictlyEnforceRange
        //x:0


        model: mod
        //  spacing: 2

        delegate:
            Rectangle{
            //z:-1017

            width: view.width
            height:  30
            border.color: "black"
            border.width: 1
            color:num==userManagement.selectedAclUser ? "grey" : "transparent"


            Text{
                id: label
                text: ""
                x:20

                anchors.verticalCenter: parent.verticalCenter

                font.family: font1
                font.pixelSize: 15
            }

            MouseArea{
                id: letterMouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("click")
                    userManagement.selectedAclUser=num;

                }

                hoverEnabled: true

            }


            Component.onCompleted: {
               // console.log(num,y)
                if(num==-1 || num>=cont.getTerrainUserFromAclNum()){
                    height=1;
                    visible=false;

                } else {
                    label.text=cont.getTerrainUserFromAclNameAt(num) + " " + cont.getTerrainUserFromAclSurnameAt(num);
                }
            }






        }


    }




    Connections{
        target: cont

        onTerrainUserFromAclListReady:{
            console.log("tvorim list",cont.getTerrainUserFromAclNum());
            create(cont.getTerrainUserFromAclNum());
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

