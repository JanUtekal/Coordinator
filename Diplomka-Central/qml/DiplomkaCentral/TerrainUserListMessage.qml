
import QtQuick 1.1



Rectangle {

    function highlightItemAt(i){
        view.currentIndex=i;
        view.currentItem.highlighted=true;
    }



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
            property bool highlighted: false
            //z:-1017
            id: row
            width: view.width
            height:  40
            border.color: "black"
            border.width: 1
            color: highlighted ? "yellow" : num===userManagement.selectedUserMessage ? "grey" : "transparent"


                Text{
                    id: label
                    text: cont.getTerrainUserNameAt(num) + " " + cont.getTerrainUserSurnameAt(num)
                    anchors.verticalCenter: parent.verticalCenter
                    x:20



                    font.family: font1
                    font.pixelSize: 15

                    Component.onCompleted: {
                        var changed=false;

                        while(label.paintedWidth>row.width-60){
                            label.text=label.text.substr(0,label.text.length-1);
                            changed=true;
                        }
                        if(changed){
                            label.text+="..."
                        }
                    }
                }





            MouseArea{
                id: letterMouseArea
                anchors.fill: parent
                onClicked: {

                    userManagement.selectedUserMessage=num;
                    row.highlighted=false;
                    cont.prepareMessageList(num);
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
            cont.prepareTerrainUserList();
            //  letterReady=0;
        } else {
            //   mod.clear();
            // visible=false;

        }

    }


}

