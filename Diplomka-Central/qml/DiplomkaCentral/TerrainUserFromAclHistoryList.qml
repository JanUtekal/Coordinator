
import QtQuick 1.1



Rectangle {

    // color: "white"
    property bool onMap:false

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

    Rectangle{
        property bool selected: false

        id: all
        //z:-1017
        y:-30
        width: view.width
        height:  30
        border.color: "black"
        border.width: 2
        color: selected ? Qt.rgba(0.5 , 0.5, 0.5, 0.8):Qt.rgba(0.8, 0.8, 0.8, 0.8)
        visible: onMap

        Text{
            id: labelAll
            text: "Všechny jednotky"

            x:15

            anchors.verticalCenter: parent.verticalCenter

            font.family: font1
            font.pixelSize: 14
            font.bold: true
            Component.onCompleted: {

            }
        }

        MouseArea{
            id: mouseAreaAll
            anchors.fill: parent
            onClicked: {

                userManagement.selectedAclHistoryUser=-1;
                if(userManagement.selectedHistoryAcl!=-1){
                    all.selected=true;
             //       cont.removeLastTrajectory();
                    cont.prepareTrajectories(userManagement.selectedHistoryAcl);
                }
            }

            hoverEnabled: true

        }












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
                   // console.log("click")
                    all.selected=false;
                    userManagement.selectedAclHistoryUser=num;
                    cont.prepareMessageHistoryList(num, userManagement.selectedHistoryAcl);

                    if(onMap){
                        cont.removeLastTrajectory();
                        cont.prepareUserTrajectory(num, userManagement.selectedHistoryAcl);
                    }

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

