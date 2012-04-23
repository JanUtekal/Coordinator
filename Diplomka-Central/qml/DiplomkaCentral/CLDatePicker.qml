/**
 *  Copyright © 2010 Digia Plc
 *  Copyright © 2010 Nokia Corporation
 *
 *  All rights reserved.
 *
 *  Nokia and Nokia Connecting People are registered trademarks of
 *  Nokia Corporation.
 *  Java and all Java-based marks are trademarks or registered
 *  trademarks of
 *  Sun Microsystems, Inc. Other product and company names
 *  mentioned herein may be
 *  trademarks or trade names of their respective owners.
 *
 *
 *  Subject to the conditions below, you may, without charge:
 *
 *  ·  Use, copy, modify and/or merge copies of this software and
 *     associated documentation files (the "Software")
 *
 *  ·  Publish, distribute, sub-licence and/or sell new software
 *     derived from or incorporating the Software.
 *
 *
 *  This file, unmodified, shall be included with all copies or
 *  substantial portions
 *  of the Software that are distributed in source code form.
 *
 *  The Software cannot constitute the primary value of any new
 *  software derived
 *  from or incorporating the Software.
 *
 *  Any person dealing with the Software shall not misrepresent
 *  the source of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 *  KIND, EXPRESS OR IMPLIED,
 *  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A
 *  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE
 *  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
import Qt 4.7
import "javascripts/datepicker.js" as CalendarEngine
import "javascripts/functions.js" as Functions
import "javascripts"
import "gradients/"
import "includes"

Rectangle {
    id: structure;

    property CLStyle style : CLStyle{}
    property string selected : day + "." + month + "." + year

    //three properties below means selected day, year and month
    property int day : Date.today().getDate();
    property int year : Date.today().getFullYear()
    property int month : Date.today().getMonth()+1

    property int monthCounter : month
    property int yearCounter : year


    property real fontSize: style.fontSize
    property string fontFamily: style.fontFamily

    //properties related to selected date screen
    property bool showSelectedDate: false// true
    property real selectedDateScreenHeight: structure.height*0.125
    property real selectedDateFontSize: selectedDateScreenHeight*0.4
    property string selectedDateFontFamily: fontFamily
    property Gradient selectedDateGradient: style.gradientWhenDefault
    property bool selectedDateGradientOn: style.gradientDefaultOn
    property color selectedDateBgColor: style.colorWhenDefault

    //properties related to day of month -box
    property int boxWidth : boxHeight
    property int boxHeight: (structure.height-monthChangerHeight-selectedDateScreenHeight-column.spacing*3-dayBoxSpacing*5)/7
    property int dayBoxSpacing: height*0.01
    property real boxRoundness: style.roundness

    property color boxColorWhenDefault : style.colorWhenDefault
    property color boxColorWhenHovered : style.colorWhenHovered
    property color boxColorWhenSelected : "blue"
    property color boxColorWhenToday : "red"

    property real boxFontSize: structure.height*0.04
    property string boxFontFamily: fontFamily

    property Gradient gradientWhenDefault: style.gradientWhenDefault
    property Gradient gradientWhenHovered: style.gradientWhenHovered
    property Gradient gradientWhenToday: Grey{}//style.gradientWhenDefault// LightBlue{}
    property Gradient gradientWhenSelected: LightBlue{}//Red{}
    property bool gradientDefaultOn: style.gradientDefaultOn
    property bool gradientHoveredOn: style.gradientHoveredOn
    property bool gradientSelectedOn: true
    property bool gradientTodayOn: true

    property bool gradientPressedOn: style.gradientPressedOn
    property Gradient gradientWhenPressed: style.gradientWhenPressed
    property color colorWhenPressed: style.colorWhenPressed

    property bool hoveredStateOn: style.hoveredStateOn

    property color textColor: style.textColor

    //properties related to month changer
    property real monthChangerRoundness: style.roundness
    property real monthChangerHeight: structure.height * 0.15
    property real monthChangerWidth: structure.width
    property real monthChangerFontSize: monthChanger.height*0.3
    property string monthChangerFontFamily: fontFamily
    property Gradient monthChangerGradient: gradientWhenDefault
    property bool monthChangerGradientOn: false//gradientDefaultOn
    property color monthChangerBgColor: "transparent"//boxColorWhenDefault

    property color bgColor : "transparent"

    property real weekDaysFontSize: height*0.042
    property string weekDaysFontFamily: fontFamily

    property bool pastDaysDisabled: false//true

    property Image leftArrowImage : Image{ source: "images/arrow_left_50x50.png"; smooth: false; scale: structure.height*0.002 }
    property Image rightArrowImage : Image{ source: "images/arrow_right_50x50.png"; smooth: false; scale: structure.height*0.002 }

    property Gradient gradientDisabled : Grey{}

    signal clicked()

    property int sDay : 0
    property int sMonth : 0
    property int sYear : 0

    /**
     * Change text in day Rectangles when changing month.
     */
    function changeDays() {

        //if(structure.day == dayBox.day && structure.month == monthCounter && structure.year == structure.yearCounter){

           // color= "black"
 //       }

        var missing=false;
        //below: monday = 0, sunday = 6
        var dayWhereMonthStarts = CalendarEngine.dayWhereMonthStarts(yearCounter,monthCounter);
        for (var i=0; i < grid.children.length; i++) {



            if(i < dayWhereMonthStarts)  {
                //grid.children[i].clickable = false;
                grid.children[i].opacity = 0.9999//0.0001
                                 //   grid.children[i].color = "black";

            } else {
                grid.children[i].opacity = 1
                if((i - dayWhereMonthStarts) < Date.getDaysInMonth(yearCounter,monthCounter-1)) {
                    grid.children[i].opacity = 1;
                    grid.children[i].day = i - CalendarEngine.dayWhereMonthStarts(yearCounter,monthCounter) + 1;
                } else {
                     grid.children[i].opacity = 0.9999

                    if(i==35){
                        missing=true;

                    }

                    if(missing){
                       grid.children[i].opacity = 0.0001;

                    }

                //    grid.children[i].clickable = false;
                    //grid.children[i].color = "black";
                }
            }
        }
    }


    /**
     * Next month.
     */
    function next(){
        if (monthCounter == 12) {
            monthCounter = 1
            yearCounter++;
        } else {
            monthCounter++;
        }
        changeDays();
    }


    /**
     * Previous month.
     */
    function previous() {
        if (monthCounter == 1) {
            monthCounter = 12
            yearCounter--;
        } else {
            monthCounter--;
        }
        changeDays();
    }

    Component.onCompleted: {
        buttonPrevious.fontSize = monthChanger.height*0.5;
        buttonNext.fontSize = monthChanger.height*0.5;
        selectedDate.fontSize = selectedDateFontSize
        if (!monthChangerGradientOn) monthChangerGradientContainer.destroy();
        if (!showSelectedDate) {
            selectedDate.visible = false;
            structure.boxHeight = (structure.height-monthChangerHeight-column.spacing*2-dayBoxSpacing*5)/7
        }
        changeDays()
    }

    onHeightChanged: {
       if (!showSelectedDate) structure.boxHeight = (structure.height-monthChangerHeight-column.spacing*2-dayBoxSpacing*5)/7
    }

    width: 220
    height: 300
    color: bgColor
   // smooth: true

    Column {
        id: column
        spacing: 5;

        Screen {
            id: selectedDate;
            anchors.horizontalCenter: parent.horizontalCenter;
            height: selectedDateScreenHeight;
         //   value: day + "." + month + "." + year
            Text{
                text:day + "." + month + "." + year
                width: parent.width
                height: parent.height
                font.pointSize: 12
                color: "white"
                horizontalAlignment:  Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

            }
            radius: Functions.countRadius(boxRoundness,width,height,0,1);
            fontFamily: selectedDateFontFamily
            color: selectedDateBgColor
            gradientOn: selectedDateGradientOn
            gradient: selectedDateGradient
            width: structure.width*0.7
        //    fontSize: 5//selectedDateFontSize
            style: structure.style
        }

        Rectangle {
            id: monthChanger
            width: monthChangerWidth
            height: monthChangerHeight
            anchors.horizontalCenter: parent.horizontalCenter;
            radius: Functions.countRadius(monthChangerRoundness,width,height,0,1)
            color: monthChangerBgColor

            Rectangle {
                id: monthChangerGradientContainer
                anchors.fill: parent
                gradient: monthChangerGradient
                radius: parent.radius
            }


            CLButton {
                style: structure.style;

                id: buttonPrevious;
                text: "";
                onClicked: {

                    previous();


                }


                height: parent.height-1;
                anchors.left: parent.left;
                leftMargin: parent.width*0.05;
                anchors.verticalCenter: parent.verticalCenter;
                width: parent.width/2; z:0;
                textAlign: "left"
                imageAlign: "left"
                borderColor: "transparent"
                borderColorWhenHovered: "transparent"
                borderColorWhenPressed: "transparent"
               // smooth: structure.smooth
                color: "transparent"
                backgroundImage: leftArrowImage



                gradientDefaultOn: false
                gradientHoveredOn: false
                gradientPressedOn: false
                gradientWhenDefault: structure.gradientWhenDefault
                gradientWhenHovered: structure.gradientWhenHovered
                gradientWhenPressed: structure.gradientWhenPressed
                colorWhenDefault: "transparent"
                colorWhenHovered: "transparent"
                colorWhenPressed: "transparent"
                hoveredStateOn: false//structure.hoveredStateOn
                /*
                gradientDefaultOn: structure.gradientDefaultOn
                gradientHoveredOn: structure.gradientHoveredOn
                gradientPressedOn: structure.gradientPressedOn
                gradientWhenDefault: structure.gradientWhenDefault
                gradientWhenHovered: structure.gradientWhenHovered
                gradientWhenPressed: structure.gradientWhenPressed
                colorWhenDefault: structure.boxColorWhenDefault
                colorWhenHovered: structure.boxColorWhenHovered
                colorWhenPressed: structure.colorWhenPressed
                hoveredStateOn: structure.hoveredStateOn*/
            }

            Text {
                id: monthName;
                text: CalendarEngine.getMonthName(monthCounter) + " " + yearCounter
                font.pointSize: 12//0.001+monthChangerFontSize;
                font.bold: true
                font.family: monthChangerFontFamily
                color: textColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                z:1
            }

            CLButton {
                id: buttonNext;
                style: structure.style;
                text: "";
                onClicked: next();
                height: buttonPrevious.height;
                width: buttonPrevious.width;
                anchors.right: parent.right;
                rightMargin: parent.width*0.05;
                borderColor: "transparent"
                borderColorWhenHovered: "transparent"
                borderColorWhenPressed: "transparent"
               // smooth: structure.smooth
                anchors.verticalCenter: parent.verticalCenter; z:0;
                textAlign: "right";
                imageAlign: "right"
                backgroundImage: rightArrowImage

                gradientDefaultOn: false
                gradientHoveredOn: false
                gradientPressedOn: false
                gradientWhenDefault: structure.gradientWhenDefault
                gradientWhenHovered: structure.gradientWhenHovered
                gradientWhenPressed: structure.gradientWhenPressed
                colorWhenDefault: "transparent"
                colorWhenHovered: "transparent"
                colorWhenPressed: "transparent"
                hoveredStateOn: false//structure.hoveredStateOn
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter;
            spacing: 0//dayBoxSpacing
            Repeater {
                model: 7
                delegate: Rectangle {
                    color: bgColor;
                    width: boxHeight//boxWidth
                    y:5

                    height: 35
                    Text {
                        text: CalendarEngine.stringShorter(CalendarEngine.getDayName(index),2);
                        color: "#696969"// structure.textColor;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        anchors.verticalCenter: parent.verticalCenter;
                        font.pointSize: 10//0.001+weekDaysFontSize;
                        font.family: weekDaysFontFamily
                    }
                }
            }
        }

        Grid {
            id: grid
            anchors.horizontalCenter: parent.horizontalCenter;
            y: 40

            rows: 6;
            columns: 7;
            spacing: 1//dayBoxSpacing

            Repeater {
                 model: 42

                 delegate: Rectangle {
                    id: dayBox

                    property alias day : dateField.text
                                         property bool clickable:true
                    width: boxHeight//boxWidth
                    height: 40
                    border.color : "black"
                    border.width: 2
                   // color: "black"
                    radius:0// Functions.countRadius(boxRoundness,width,height,0,1)
                    //smooth: structure.smooth


                    Rectangle {
                        id: boxGradientContainer
                        anchors.fill: parent
                       // gradient: gradientWhenDefault
                        radius: parent.radius
                        //color:"black"
                        //smooth: structure.smooth
                        onVisibleChanged: {
                            if(!visible){
                                visible=true;

                            }
                        }
                    }

                    Rectangle {
                        id: blueborder
                        //anchors.fill: parent
                       // gradient: gradientWhenDefault
                        width: parent.width-3
                        height: parent.height-3
                        x:1
                        y:1
                        border.color: "#19a9ff"
                        border.width: clickable ? mouseArea.pressed ? 3 : 0 : 0
                        radius: parent.radius
                        color:"transparent"
                        //smooth: structure.smooth


                    }

                    Text {
                        id: dateField;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        anchors.verticalCenter: parent.verticalCenter;
                        text: ""
                        color: textColor
                        font.pointSize: 11//0.001 + boxFontSize
                        font.family: boxFontFamily
                        font.bold: true
                        z:1
                    }

                    MouseArea {
                        id: mouseArea
                        anchors.fill: parent
                        hoverEnabled: true;
                        onClicked: {
                            if(clickable){
                                structure.day  = dateField.text;
                                structure.month = monthCounter
                                structure.year = yearCounter
                                structure.clicked();
                            }
                        }

                    }

                    onVisibleChanged: {
                        boxGradientContainer.visible=true;
                    }

                    onOpacityChanged: {
                       // console.log(opacity)
                        onOpacityChanged: {

                            if(opacity!=1){
                               // console.log("A")
                                clickable=false;

                             //   dayBox.color="lightgrey";
                                //console.log(dayBox.day);

                                boxGradientContainer.color="lightgrey";
                                dateField.text="";
                                dayBox.day="";
                            } else {
                              //  console.log("B")
                                clickable=true;
                             //   dayBox.color="white";
                                boxGradientContainer.color="white";



                                //dayBox.color=boxColorWhenDefault;
                            }

                        }

                    }




                    states: [
                /*    State {
                        name: "disabled"; when: pastDaysDisabled && CalendarEngine.dayBeforeToday(dayBox.day,structure.monthCounter,structure.yearCounter);
                        PropertyChanges {target: dayBox; enabled: false}
                        PropertyChanges {target: boxGradientContainer; gradient: gradientDisabled}
                        PropertyChanges {target: dateField; color: "black"}
                        PropertyChanges {target: dayBox; color: "grey"}

                    },*/
                    State {
                        name: "selected"; when: structure.day == dayBox.day && structure.month == monthCounter && structure.year == structure.yearCounter
                     //   PropertyChanges {target: dayBox; color: boxColorWhenSelected}
                        PropertyChanges {id: propertyChangesGradientSelected; target: boxGradientContainer; gradient: gradientWhenSelected; visible: true}// {if(gradientSelectedOn) true; else false}}
                    },
                    State {
                        name: "today"; when: ( (dayBox.day == Date.today().getDate()) && (structure.monthCounter == Date.today().getMonth() + 1)  && (structure.yearCounter == Date.today().getFullYear()) );
                        PropertyChanges {target: dayBox; color: boxColorWhenToday}
                        PropertyChanges {id: propertyChangesGradientToday; target: boxGradientContainer; gradient: gradientWhenToday; visible:true}// {if(gradientTodayOn) true; else false}}

                    }
                 /*   State {
                        id: stateHovered
                        name: "hovered"; when: mouseArea.containsMouse
                        PropertyChanges {target: dayBox; color: boxColorWhenHovered}
                        PropertyChanges {id: propertyChangesGradientHovered; target: boxGradientContainer; gradient: gradientWhenHovered; visible: true}//{if(gradientHoveredOn) true; else false}}
                    }*/
                    ]

                 //   Component.onCompleted: {

                      //  if (!hoveredStateOn) stateHovered.destroy();
          //          }
                }
            }
        }
    }
}
