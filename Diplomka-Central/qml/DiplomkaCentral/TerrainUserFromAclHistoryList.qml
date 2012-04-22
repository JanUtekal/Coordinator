
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

        //    anchors.fill:parent
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
            color:num==userManagement.selectedAclHistoryUser ? "grey" : "transparent"


            Text{
                id: label
                text: cont.getTerrainUserFromAclHistoryNameAt(num) + " " + cont.getTerrainUserFromAclHistorySurnameAt(num)
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
                    userManagement.selectedAclHistoryUser=num;
                    cont.prepareMessageHistoryList(num, userManagement.selectedHistoryAcl);

                }

                hoverEnabled: true

            }


            Component.onCompleted: {
               // console.log(num,y)
            /*    if(num==-1 || num>=cont.getTerrainUserFromAclNum()){
                    height=1;
                    visible=false;

                } else {
                    label.text=cont.getTerrainUserFromAclNameAt(num) + " " + cont.getTerrainUserFromAclSurnameAt(num);
                }*/
            }






        }


    }




    Connections{
        target: cont

        onTerrainUserFromAclHistoryListReady:{
          //  console.log("tvorim list",cont.getTerrainUserFromAclNum());
            create(cont.getTerrainUserFromAclHistoryNum());
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

