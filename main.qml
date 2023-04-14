import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

ApplicationWindow {
    width: Screen.desktopAvailableWidth
    height: Screen.desktopAvailableHeight
//    visibility: "FullScreen"
    visible: true
    title: qsTr("Tabs")

    SwipeView {
        id: swipeView
        anchors.fill: parent
//        currentIndex: tabBar.currentIndex

        MainPage {
        }

//        Page2Form {
//        }
    }

//    footer: TabBar {
//        id: tabBar
//        currentIndex: swipeView.currentIndex

//        TabButton {
//            text: qsTr("Page 1")
//        }
////        TabButton {
////            text: qsTr("Page 2")
////        }
//    }
}
