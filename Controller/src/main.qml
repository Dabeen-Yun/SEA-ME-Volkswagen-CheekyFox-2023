import QtQuick 2.7
import QtQuick.Controls 2.2
import com.seame.Speed 1.0
import com.seame.Buttons 1.0
import com.seame.RPM 1.0
import com.seame.Oil 1.0
import com.seame.Handle 1.0

ApplicationWindow {
    visible: true
    width: 1280
    height: 960
    title: qsTr("Controller")

    property string clickedButton: "P"

    Speed {
        id: speed
    }

    Buttons {
        id: buttons
    }

    RPM {
        id: rpm
    }

    Oil {
        id: oil
    }

    Handle {
        id: handle
    }



    Slider {
        id: speedBar
        width: 500
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -101
        anchors.horizontalCenterOffset: -236
        from: 0
        to: 260
        value: 0

        onValueChanged: {
            speed.adjustSpeed(speedBar.value);
        }

        anchors.centerIn: parent
    }

    Slider {
        id: rpmBar
        width: 500
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -100
        anchors.horizontalCenterOffset: 231
        from: 0
        to: 8000
        value: 0

        onValueChanged: {
            rpm.adjustRPM(rpmBar.value);
        }

        anchors.centerIn: parent
    }

    Slider {
        id: oilBar
        width: 500
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -100
        anchors.horizontalCenterOffset: -400
        from: 100
        to: 0
        value: 100

        onValueChanged: {
            oil.adjustOil(oilBar.value);
        }

        anchors.centerIn: parent
    }

    Slider {
        id: handleBar
        width: 500
        height: 219
        rotation: 270
        anchors.verticalCenterOffset: -100
        anchors.horizontalCenterOffset: 400
        from: 0
        to: 260
        value: 0

        onValueChanged: {
            handle.adjustHandle(handleBar.value);
        }

        anchors.centerIn: parent
    }

    Column {
        id: orderButtons
        anchors.verticalCenterOffset: -81
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        spacing: 10

        Button {
            id: buttonP
            text: "P"
            onClicked: {
                buttons.adjustButtons("P");
                clickedButton = "P";
            }
            width: 100
            height: 100
            font.pixelSize: 40
            font.bold: true
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "black" }
                    GradientStop { position: 1.0; color: "gray" }
                }
            }
            contentItem: Text {
                text: buttonP.text
                color: clickedButton === "P" ? "red" : "white"
                font.pointSize: 40
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            id: buttonR
            text: "R"
            onClicked: {
                buttons.adjustButtons("R");
                clickedButton = "R";
            }
            width: 100
            height: 100
            font.pixelSize: 40
            font.bold: true
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "black" }
                    GradientStop { position: 1.0; color: "gray" }
                }
            }
            contentItem: Text {
                text: buttonR.text
                color: clickedButton === "R" ? "red" : "white"
                font.pointSize: 40
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            id: buttonN
            text: "N"
            onClicked: {
                buttons.adjustButtons("N");
                clickedButton = "N";
            }
            width: 100
            height: 100
            font.pixelSize: 40
            font.bold: true
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "black" }
                    GradientStop { position: 1.0; color: "gray" }
                }
            }
            contentItem: Text {
                text: buttonN.text
                color: clickedButton === "N" ? "red" : "white"
                font.bold: true
                font.pointSize: 40
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Button {
            id: buttonD
            text: "D"
            onClicked: {
                buttons.adjustButtons("D");
                clickedButton = "D";
            }
            width: 100
            height: 100
            font.pixelSize: 40
            font.bold: true
            background: Rectangle {
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "black" }
                    GradientStop { position: 1.0; color: "gray" }
                }
            }
            contentItem: Text {
                text: buttonD.text
                color: clickedButton === "D" ? "red" : "white"
                font.bold: true
                font.pointSize: 40
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
    }
    Button {
        id: buttonWeather
        property bool isToggled: false
        x: 355
        y: 681 // Add this line

        onClicked: {
            buttons.adjustButtons("Weather");
            isToggled = !isToggled; // This line toggles the state
        }
        width: 100
        height: 100

        contentItem: Image {
            id: weatherImage
            width: 100
            height: 100
            source: buttonWeather.isToggled ? "image/weather1.png" : "image/weather.png" // Use the state here
        }

        background: Rectangle {
            color: "transparent"
        }
    }
    Button {
        id: buttonWarn
        property bool isToggled: false
        x: 590
        y: 681 // Add this line

        onClicked: {
            buttons.adjustButtons("Warn");
            isToggled = !isToggled; // This line toggles the state
        }
        width: 100
        height: 100

        contentItem: Image {
            id: warnImage
            width: 100
            height: 100
            source: buttonWarn.isToggled ? "image/warn.png" : "image/warn1.png" // Use the state here
        }

        background: Rectangle {
            color: "transparent"
        }
    }
    Button {
        id: buttonLight
        property bool isToggled: false
        x: 772
        y: 671 // Add this line

        onClicked: {
            buttons.adjustButtons("Light");
            isToggled = !isToggled; // This line toggles the state
        }
        width: 200
        height: 120

        contentItem: Image {
            id: starImage
            width: 100
            height: 100
            source: buttonLight.isToggled ? "image/on.png" : "image/off.png" // Use the state here
        }

        background: Rectangle {
            color: "transparent"
        }
    }

    Button {
        id: buttonYes
        x: 772
        y: 671 // Add this line

        onClicked: {
            buttons.adjustButtons("Yes");

        }
        width: 200
        height: 120

        contentItem: Image {
            id: yesImage
            width: 50
            height: 50
            source: "image/yes_1.png" // Use the state here
        }
        background: Rectangle {
            color: "transparent"
        }
    }

    Button {
        id: buttonNo
        x: 900
        y: 674 // Add this line

        onClicked: {
            buttons.adjustButtons("No");

        }
        width: 200
        height: 120

        contentItem: Image {
            id: noImage
            width: 50
            height: 50
            source: "image/no_1.png" // Use the state here
        }
        background: Rectangle {
            color: "transparent"
        }
    }


    TextEdit {
        id: textEdit
        x: 128
        y: 59
        width: 80
        height: 20
        font.pixelSize: 12
    }
}
