
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
            id:row
            //z:-1017

            width: view.width
            height:  30
            border.color: "black"
            border.width: 1
            color: num==userManagement.selectedAcl ? "grey" : "transparent"

            Rectangle{
                id: check
                height: parent.height
                width:height
                color:"transparent"

                border.width:1
                border.color: "black"
                z:2

                Text{

                    text: "o"


                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    font.family: font1
                    font.pixelSize: 15
                    color:"green"
                }



                MouseArea{
                    id: checkMouseArea
                    anchors.fill: parent
                    onClicked: {

                        cont.invalidateAcl(num);
                        userManagement.selectedAcl=-1;
                        cont.prepareAclList();



                    }

                    hoverEnabled: true

                }

            }


            Text{
                id: label
                text: cont.getAclNameAt(num)
                x:check.width+20
                width: parent.width
                anchors.verticalCenter: parent.verticalCenter

                font.family: font1
                font.pixelSize: 15

                Component.onCompleted: {
                    var changed=false;

                    while(label.paintedWidth>row.width-100){
                        label.text=label.text.substr(0,label.text.length-1);
                        changed=true;
                    }
                    if(changed){
                        label.text+="..."
                    }
                }
            }


            Rectangle{
                id: ex
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

                        cont.removeAcl(num);
                        userManagement.selectedAcl=-1;
                        cont.prepareAclList();



                    }

                    hoverEnabled: true

                }

            }

            MouseArea{
                id: aclMouseArea
                anchors.fill: parent
                onClicked: {
                    console.log("click",num)
                    cont.prepareTerrainUserFromAclList(num);
                    userManagement.selectedAcl=num;
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
              console.log("tvorim list",cont.getAclNum());
            create(cont.getAclNum());
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

