
import QtQuick 2.12
import QtQuick.Window 2.12

Item {
    id: root
    property int radiusTopLeft: 0
    property int radiusTopRight: 0
    property int radiusBottomLeft: 0
    property int radiusBottomRight: 0
    property color color: "white"
    property color borderColor: "white"
    property int borderWidth: 1
    Canvas {
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);

            ctx.fillStyle = color;
            ctx.beginPath();
            ctx.moveTo(radiusTopLeft, 0);
            ctx.arcTo(0, 0, 0, radiusTopLeft, radiusTopLeft);
            ctx.lineTo(0, height - radiusBottomLeft);
            ctx.arcTo(0, height, radiusBottomLeft, height, radiusBottomLeft);
            ctx.lineTo(width - radiusBottomRight, height);
            ctx.arcTo(width, height, width, height - radiusBottomRight, radiusBottomRight);
            ctx.lineTo(width, radiusTopRight);
            ctx.arcTo(width, 0, width - radiusTopRight, 0, radiusTopRight);
            ctx.closePath();
            ctx.fill();
            ctx.strokeStyle = borderColor;
            ctx.lineWidth=borderWidth
            ctx.stroke()
        }
    }
}

