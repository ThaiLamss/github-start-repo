import QtQuick 2.0

Rectangle {



    id:root
    width: parent.width
    height: itemHeight

    color: "lightblue"
    Rectangle
    {
        id: rectMain
        anchors.centerIn: parent
        height: parent.height-10
        width: parent.width
        radius: height/4
        color: "red"
        border.color: "black"
        clip: true
        Row
        {
            anchors.fill: parent
            CustomRadiusRect{
                id: rectID
                height: parent.height
                color: "blue"
                width: rectMain.width/5
                radiusTopLeft: rectMain.radius
                radiusBottomLeft: rectMain.radius
            }
            Rectangle{
                id: rectProduction
                height: parent.height
                color: "red"
                width: rectMain.width/5
            }
            Rectangle{
                id: rectWip
                height: parent.height
                color: "purple"
                width: rectMain.width/5
            }
            Rectangle{
                id: rectAGV
                height: parent.height
                color: "yellow"
                width: rectMain.width/5
            }
            CustomRadiusRect{
                id: rectStatus
                height: parent.height
                color: "green"
                width: rectMain.width/5
                clip: true
                radiusTopRight: rectMain.radius
                radiusBottomRight: rectMain.radius
            }

        }
    }

}
