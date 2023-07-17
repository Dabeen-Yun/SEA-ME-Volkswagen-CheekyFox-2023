import QtQuick 2.7
import QtQuick.Controls 2.2
import "."
import QtMultimedia 5.5
import QtWebEngine 1.7

ApplicationWindow {
    visible: true
    width: screen.width
    height: screen.height
//    property alias gearImage: gearImage
    property string bState: "P"
    property bool showWeather: false
    property bool showWarn: false
    property bool showLight: false

    title: qsTr("Speedometer")

    // Background Image
    Image {
        id: backgroundImage
        anchors.fill: parent
        source: "image/ui.png" // Replace with the path to your background image
    }

    Image {
        id: redoilImage
        width: 40
        height: 40
        z:3
        anchors.verticalCenterOffset: -230
        anchors.horizontalCenterOffset: -200
        anchors.centerIn: parent
        source: "image/redoil.png" // Replace with the path to your arc image
        visible: false
    }

    Timer {
        id: blinkTimer2
        interval: 500 // 500ms = 0.5 seconds
        running: false
        repeat: true
        onTriggered: redoilImage.visible = !redoilImage.visible
    }


    Text {
        id: oildigital
        text: oilReceiver.oilValue + "L"
        font.pixelSize: 40
        color: "white"
        font.bold: true
        font.italic: true
        anchors.verticalCenterOffset: -230
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        visible: true
    }

    Text {
        id: speeddigital
        text: speedReceiver.speedValue
        font.pixelSize: 60
        color: "white"
        font.bold: true
        font.italic: true
        anchors.verticalCenterOffset: 60
        anchors.horizontalCenterOffset: -450
        anchors.centerIn: parent
        visible: true
    }
    Text {
        id: rpmdigital
        text: rpmReceiver.rpmValue
        font.pixelSize: 40
        color: "white"
        font.bold: true
        font.italic: true
        anchors.verticalCenterOffset: 40
        anchors.horizontalCenterOffset: 470
        anchors.centerIn: parent
        visible: true
    }
    Text {
        id: handledigital
        text: handleReceiver.handleValue
        font.pixelSize: 30
        color: "white"
        font.bold: true
        font.italic: true
        anchors.verticalCenterOffset: 180
        anchors.horizontalCenterOffset: 720
        anchors.centerIn: parent
        visible: true
    }


    Image {
        id: oillistImage
        width: 700
        height: 550
        z:2
        anchors.verticalCenterOffset: -60
        anchors.horizontalCenterOffset: 0
        anchors.centerIn: parent
        source: "image/oillist2.png" // Replace with the path to your arc image
        visible: false
    }

    Connections {
        target: oilReceiver
        onOilValueChanged: {
//            onOilValueChanged: {
//                digitalValue.text = oilReceiver.oilValue;
//                }
            if (oilReceiver.oilValue < 50) {
                oillistImage.visible = true;
                if (blinkTimer2.running) { // If timer is running
                    blinkTimer2.stop(); // Stop timer
                    redoilImage.visible = false; // Ensure the image is hidden

                }
            } else {
                oillistImage.visible = false;
            }
        }
    }

    Image {
        id: weatherIcon
        width: 166
        height: 166
        anchors.verticalCenterOffset: -100
        anchors.horizontalCenterOffset: -6
        anchors.centerIn: parent
        source: weatherAPI.weatherIcon
        visible: true //showWeather
    }

    Image {
        id: warnIcon
        width: 864
        height: 80
        anchors.verticalCenterOffset: -314
        anchors.horizontalCenterOffset: 1
        anchors.centerIn: parent
        source: "image/warning.png"
        visible: showWarn
    }
    Timer {
        id: blinkTimer
        interval: 500 // Blink every 500ms
        running: false // Don't start running automatically
        repeat: true
        onTriggered: {
            warnIcon.visible = !warnIcon.visible // Toggle visibility
        }
    }
    Image {
        id: starIcon
        width: 80
        height: 80
        anchors.verticalCenterOffset: -344
        anchors.horizontalCenterOffset: -547
        anchors.centerIn: parent
        source: "image/star.png"
        visible: showLight
    }

    Text {
        id: temperature
        z:1
        font.pixelSize: 40
        font.bold: true
        font.italic: true
        color: 'white'
        anchors.horizontalCenter: weatherIcon.horizontalCenter
        anchors.top: weatherIcon.bottom
        anchors.topMargin: 37
        text: weatherAPI.temperature + "°C"
        anchors.horizontalCenterOffset: 0
        visible: showWeather
    }


    Item {
        anchors{
            centerIn: parent
            horizontalCenterOffset: -720
            verticalCenterOffset: 160
        }


        Text {
            id: pText
            font.pixelSize: 40
            font.italic: true
            font.bold: true
            text: "P"
            color: 'red'
            visible: true
        }

        Text {
            id: rText
            font.pixelSize: 40
            font.italic: true
            font.bold: true
            text: "R"
            color: 'white'
            visible: false
        }

        Text {
            id: nText
            font.pixelSize: 40
            font.italic: true
            font.bold: true
            text: "N"
            color: 'white'
            visible: false
        }

        Text {
            id: dText
            font.pixelSize: 40
            font.italic: true
            font.bold: true
            text: "D"
            color: 'white'
            visible: false
        }

    }

    Connections {
        target: buttonsReceiver
        onButtonsValueChanged: {
            var buttonValue = buttonsReceiver.buttonsValue;

            if (buttonValue === "P" || buttonValue === "R" || buttonValue === "N" || buttonValue === "D") {
                bState = buttonValue;
                pText.visible = bState === "P" ? true : false;
                rText.visible = bState === "R" ? true : false;
                nText.visible = bState === "N" ? true : false;
                dText.visible = bState === "D" ? true : false;

                videoOutput.visible = bState === "R";
            }
            else if(buttonValue === "Weather"){
                showWeather = !showWeather;
                weatherAPI.requestWeather("Seoul");
            }
            else if(buttonValue === "Warn"){
                if (showWarn) {
                    blinkTimer.stop(); // Stop blinking
                    warnIcon.visible = false; // Ensure the icon is hidden
                } else {
                    blinkTimer.start(); // Start blinking
                }
                showWarn = !showWarn;
            }
            else if(buttonValue === "Light"){
                showLight = !showLight;
            }
            else if(buttonValue === "No"){
                oillistImage.visible = false; // Do not display the oillist image
                blinkTimer2.start();
            }
            else if(buttonValue === "Yes"){
                oillistImage.visible = false; // Do not display the oillist image

            }


        }
    }

    Camera {
        id: camera
        deviceId: "/dev/video1"
    }

//    VideoOutput {
//        id: videoOutput
//        width: 492 // Set width of the camera output
//        height: 441
//        anchors.verticalCenterOffset: -208
//        anchors.horizontalCenterOffset: 0 // Set height of the camera output
//        anchors.horizontalCenter: parent.horizontalCenter // Center the output horizontally
//        anchors.verticalCenter: parent.verticalCenter // Center the output vertically
//        source: camera
//        visible: false
//    }
}
