import QtQuick 1.0
import QtMobility.systeminfo 1.1
Rectangle {
    width: 854
    height: 480
    MyMap{
        width: parent.width+1
        height: parent.height+1
    }
    ScreenSaver {
        id: screenSaver
        Component.onCompleted: {screenSaver.setScreenSaverDelayed(true) }
    }

}
