
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
    color: Qt.rgba(1, 1, 1, 0.8)

    border.color: "black"
    border.width: 2
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

        clip:true
        model: mod
        //  spacing: 2

        delegate:
            Rectangle{
            id: row
            //z:-1017

            width: view.width-1
            height:  30
            border.color: "black"
            border.width: 1
            color: num==userManagement.selectedMapAcl ? "grey" : "transparent"


            Text{
                id: label
                text: cont.getAclNameAt(num)

                x:20

                anchors.verticalCenter: parent.verticalCenter

                font.family: font1
                font.pixelSize: 15

                Component.onCompleted: {
                    var changed=false;

                    while(label.paintedWidth>row.width-30){
                        label.text=label.text.substr(0,label.text.length-1);
                        changed=true;
                    }
                    if(changed){
                        label.text+="..."
                    }
                }
            }

            MouseArea{
                id: aclMouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("click",num)
                    //cont.prepareTerrainUserFromAclList(num);
                    userManagement.selectedMapAcl=num;
                }

                hoverEnabled: true

            }





            Component.onCompleted: {
                //console.log(num,y)
              /*  if(num==-1 || num>=cont.getAclNum()){
                    height=1;
                    visible=false;

                } else {
                    label.text=cont.getAclNameAt(num);
                }*/
            }






        }


    }




    Connections{
        target: cont

        onAclListReady:{
            //  console.log("tvorim list",cont.getAclNum());
            if(view.count!=cont.getAclNum()){

                create(cont.getAclNum());

                userManagement.selectedMapAcl=-1
            }
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

