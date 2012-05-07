// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 800
    height: 600
    color: "lightgrey"
    border.width: 3
    border.color: "black"
    radius: 10


    Button{
        id: backButton
        width: 120
        height: 50
        x: parent.width-150
        y: parent.height-80
        z: 2
        label: "Zpět"
        imageSource: "images/back.png"
        onButtonClick: {
            history.visible=false;

        }

    }


    Button{
        id: showButton
        width: 120
        height: 50
        x: 30
        y: parent.height-80
        z: 2
        label: "Zobrazit"
        imageSource: "images/show.png"


        onButtonClick: {
            history.visible=false;
            terrainUserFromAclHistoryListMap.visible=true;
            aclListHistoryMap.visible=true;
            aclListMap.visible=false;
            leftButtons.visible=false;
            closeHistoryButton.visible=true;
            pinchmap.selectingPermited=true;
            cont.clearMapObjects();


            if(userManagement.selectedHistoryAcl!=-1){
                cont.getMapObjectsForAcl(userManagement.selectedHistoryAcl);
                if(userManagement.selectedAclHistoryUser!=-1){
                    cont.prepareUserTrajectory(userManagement.selectedAclHistoryUser, userManagement.selectedHistoryAcl);
                }
            }
            pinchmap.movingPermitted=true;

        }

    }

    CLDatePicker{
        id:fromPicker
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
      //  y: 90
     //   x:250
        z:32
        radius: 5
        width: 330
        height: 400
        color:"white"
        border.width: 5
        border.color: "black"

        onDayChanged: {

            fromPicker.visible=false;

            //dateList.visible=true;
          //  console.log(fromPicker.day,fromPicker.month,fromPicker.year);

       /*     if(dt.visible){
                dateChanging=true;

            }*/
        }
        onMonthChanged: {
       //     fromPicker.visible=false;
            //dateList.visible=true;
         //   console.log(fromPicker.day,fromPicker.month,fromPicker.year);
         /*   if(dt.visible){
                dateChanging=true;

            }
*/
        //    fromDate.setText(fromPicker.day+"-"+fromPicker.month+"-"+fromPicker.year);


        }
        onYearChanged: {
         //   fromPicker.visible=false;
            //dateList.visible=true;
        //    console.log(fromPicker.day,fromPicker.month,fromPicker.year);
          /*  if(dt.visible){
                fromPicker=true;
            }*/

        }



        visible:false
    }

    CLDatePicker{
        id:toPicker
        anchors.verticalCenter: parent.verticalCenter
             anchors.horizontalCenter: parent.horizontalCenter
       // y: 90
       // x:250
        z:32
        radius: 5
        width: 330
        height: 400
        color:"white"
        border.width: 5
        border.color: "black"

        onDayChanged: {

            toPicker.visible=false;
            //dateList.visible=true;
           // console.log(toPicker.day,toPicker.month,toPicker.year);

       /*     if(dt.visible){
                dateChanging=true;

            }*/
        }
        onMonthChanged: {
       //     fromPicker.visible=false;
            //dateList.visible=true;
            //console.log(toPicker.day,toPicker.month,toPicker.year);
         /*   if(dt.visible){
                dateChanging=true;

            }
*/



        }
        onYearChanged: {
         //   fromPicker.visible=false;
            //dateList.visible=true;
           // console.log(toPicker.day,toPicker.month,toPicker.year);
          /*  if(dt.visible){
                fromPicker=true;
            }*/

        }



        visible:false
    }



    Column{
        x:50
        y:30
        width: parent.width-20
        height: parent.height-20
   //     spacing: 10

        Row{
            width: parent.width
            height: parent.height/8
            spacing: 20

            Text{
                height: parent.heigh
                width: 40
                font.pointSize: 12
                text: "Od: "
            }

            TextInputField{
                id: fromDate
                width: 100
                height: 20
                input:fromPicker.day+". "+fromPicker.month+". "+fromPicker.year
                onlyRead: true

                onInputChanged: {
                    cont.prepareAclHistoryList(fromPicker.year,fromPicker.month,fromPicker.day,toPicker.year,toPicker.month,toPicker.day);
                }

            }

            ButtonPicture{
                id: fromButton
                width: 80
                height: 40
                y:-8

                imageSource: "images/history.png"
                onButtonClick: {
                    if(fromPicker.visible){
                        fromPicker.visible=false;
                        fromButton.alwaysPressed(false);

                    } else {
                        fromPicker.visible=true;
                        toPicker.visible=false;
                        fromButton.alwaysPressed(true);
                        toButton.alwaysPressed(false);

                    }
                }

            }


            Text{
                height: parent.height
                width: 20
                font.pointSize: 12
                text: "Do: "
            }

            TextInputField{
                id: toDate
                width: 100
                height: 20
                input:toPicker.day+". "+toPicker.month+". "+toPicker.year
                onlyRead: true

                onInputChanged: {
                    cont.prepareAclHistoryList(fromPicker.year,fromPicker.month,fromPicker.day,toPicker.year,toPicker.month,toPicker.day);
                }

            }

            ButtonPicture{
                id: toButton
                width: 80
                height: 40
                y:-8

                imageSource: "images/history.png"
                onButtonClick: {
                    if(toPicker.visible){
                        toPicker.visible=false;
                        toButton.alwaysPressed(false);
                    } else {
                        toPicker.visible=true;
                        fromPicker.visible=false;
                        toButton.alwaysPressed(true);
                        fromButton.alwaysPressed(false);

                    }
                }

            }

            Button{
                id: allButton
                width: 100
                height: 40
                y:-8
                x: 40

                label: "Všechny akce"

                onButtonClick: {
                    cont.prepareAclHistoryList(2010,1,1,2099,1,1);
                }

            }

        }

        Row{
            width: parent.width
            height: 7*parent.height/8


            spacing: 40

            Row{
                spacing: 20


                Column{
                    spacing: 10
                    width: parent.parent.width/4
                    height: 5*parent.parent.height/7

                    Text{

                        text:"Vybrané akce"
                        font.pointSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter

                    }

                    AclListHistory{
                        width:parent.width
                        height: parent.height-2

                        //color: userManagement.color
                    }

                }

                Column{
                    spacing: 10
                    width: parent.parent.width/4
                    height: 5*parent.parent.height/7

                    Text{

                        text:"Přidělené jednotky"
                        font.pointSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter

                    }

                    TerrainUserFromAclHistoryList{
                        width:parent.width
                        height: parent.height-2
                        //color: userManagement.color
                    }

                }

                Column{
                    spacing: 10
                    width: parent.parent.width/3
                    height: 5*parent.parent.height/7

                    Text{

                        text:"Výpis komunikace"
                        font.pointSize: 12
                        anchors.horizontalCenter: parent.horizontalCenter

                    }

                    TextEditField{
                        id: messageWindow
                        width:parent.width+10
                        height: parent.height-2
                        radius: 0
                        onlyRead: true

                        Component.onCompleted: {
                            messageWindow.setBottomAlignment();
                        }

                    }

                }
            }

        }

    }

    Connections{
        target: cont

        onMessagesHistoryReady:{
            messageWindow.setText("");
            var number=cont.getMessagesHistoryNum();
            for(var i=0;i<number;i++){
                messageWindow.setText(messageWindow.input+"\n"+cont.getMessageHistoryLineAt(i));
            }
        }
    }
}
