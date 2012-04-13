import QtQuick 1.0
import QtMobility.systeminfo 1.1
Rectangle {
    width: 640
    height: 360
    MyMap{
        width: parent.width
        height: parent.height
    }
    ScreenSaver {
        id: screenSaver
        Component.onCompleted: {screenSaver.setScreenSaverDelayed(true) }
    }

}
