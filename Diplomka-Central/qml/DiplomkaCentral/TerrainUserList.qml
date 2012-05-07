
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
            id: row
            width: view.width
            height:  40
            border.color: "black"
            border.width: 1
            color: num===userManagement.selectedUser ? "grey" : "transparent"

            Column{
                spacing:2
                anchors.verticalCenter: parent.verticalCenter
                Text{
                    id: label
                    text: cont.getTerrainUserNameAt(num) + " " + cont.getTerrainUserSurnameAt(num)
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

                Text{
                    id: acl
                    text: cont.getAclNameForUserAt(num)
                    x:30
                    color:"blue"



                    font.family: font1
                    font.pixelSize: 13

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

            }

            Rectangle{
                height: parent.height
                width:height
                color:"transparent"
                x:parent.width-width
                border.width:1
                border.color: "black"
                z:2

                Image{
                    id:img2
                    height: 3*parent.height/7
                    fillMode: Image.PreserveAspectFit
                    source:"images/cross.png"
                    smooth: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

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

