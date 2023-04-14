import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: page
    width: 640
    height: 480
    property real itemHeight: 150
    property alias gridView: gridView

    header: Rectangle {
        id: header
        color: "#607cb4"
        height: txtHeader.implicitHeight
        width: parent.width
        Row
        {
            anchors.fill: parent

            Rectangle{
                id: rectbanner
                height: header.height
                width: header.width-rectBtn.width
                color: "purple"
                Text {
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    id: txtHeader
                    color: "#ffffff"
                    text: "Màn Hình Mornitor hệ thống cung cấp vật liệu RB Line"
                    wrapMode: Text.WordWrap
                    font.pointSize: 30
                }
            }
            Rectangle{
                id: rectBtn
                height: header.height
                width: btnLogin.implicitWidth+10
                color: "green"
                Button{
                    id: btnLogin
                    anchors.centerIn: parent
                    text: "Login"
                }
            }


        }

    }


    Rectangle {
        id: bodyRect
        color: "#d6e4ea"
        anchors.fill: parent

        GridView {
            id: gridView
            anchors.fill: parent
            property int minWidth:page.width// 400
            cellHeight:itemHeight
            model: 6
            delegate: LineDelegate{
                width: gridView.cellWidth
            }


            cellWidth: Math.max(minWidth, page.width / Math.floor(page.width / minWidth))

            Menu {
                id: contextMenu
                MenuItem {
                    text: "Edit"
                    onTriggered: {
                        popupEditLine.visible = true
                    }
                }
                MenuItem {
                    text: "Delete"
                    onTriggered: {
                        popupDeleteLine.visible = true
                    }
                }
            }
        }
    }

    footer: Rectangle {
        id: footer
        color: "#607cb4"
        height: 50
        width: parent.width
        Row {
            id: row
            anchors.centerIn: parent
            spacing: 20
            Button{
                id: btnAddLine
                height: footer.height
                width: 150
                text: "Add Line"

            }
        }
    }
}
