


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "SpeedReceiver.h" // Include the new header
#include "ButtonsReceiver.h"
#include "RPMReceiver.h"
#include "oilreceiver.h"
#include <qqml.h>
#include <QMetaType>
#include <string>
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "ClusterStubImpl.hpp"
#include "HandleReceiver.h"
#include "WeatherAPI.h"
#include <QApplication>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDesktopServices>
#include <QUrl>
#include <cstdlib>
#include <QMediaPlayer>
#include <QMediaPlaylist>


using namespace std;
Q_DECLARE_METATYPE(std::string)
QMediaPlayer player;

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::string>();

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<ClusterStubImpl> myService =
        std::make_shared<ClusterStubImpl>();
    runtime->registerService("local", "cluster_service", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    SpeedReceiver speedStorage;
    ButtonsReceiver buttonStorage;
    RPMReceiver rpmStorage;
    OilReceiver oilStorage;
    HandleReceiver handleStorage;
    WeatherAPI weatherAPIStorage;

    QWebEngineView view;
    QWebChannel channel;
    view.page()->setWebChannel(&channel);
    view.load(QUrl::fromLocalFile("/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/map (2).html"));


    engine.rootContext()->setContextProperty("speedReceiver", &speedStorage);
    engine.rootContext()->setContextProperty("buttonsReceiver", &buttonStorage);
    engine.rootContext()->setContextProperty("rpmReceiver", &rpmStorage);
    engine.rootContext()->setContextProperty("oilReceiver", &oilStorage);    
    engine.rootContext()->setContextProperty("handleReceiver", &handleStorage);
    engine.rootContext()->setContextProperty("weatherAPI", &weatherAPIStorage);

    QObject::connect(&(*myService), &ClusterStubImpl::signalSpeed, &speedStorage, &SpeedReceiver::receiveSpeed); // Connect the instances
    QObject::connect(&(*myService), &ClusterStubImpl::signalButtons, &buttonStorage, &ButtonsReceiver::receiveButtons); // Connect the instances
    QObject::connect(&(*myService), &ClusterStubImpl::signalRPM, &rpmStorage, &RPMReceiver::receiveRPM); // Connect the instances
    QObject::connect(&(*myService), &ClusterStubImpl::signalOil, &oilStorage, &OilReceiver::receiveOil); // Connect the instances
    QObject::connect(&(*myService), &ClusterStubImpl::signalHandle, &handleStorage, &HandleReceiver::receiveHandle); // Connect the instances

    const char* pythonFilePath = "/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/web_human.py";

    QMediaPlayer player1;
    QMediaPlayer player2;
    player1.setMedia(QUrl::fromLocalFile("/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/mp3/map.mp3"));

    QObject::connect(&buttonStorage, &ButtonsReceiver::buttonsValueChanged, [&](const QString& currentButtonValue){

        if (currentButtonValue == "Yes") {
            view.show();
            player1.play();
        } else if (currentButtonValue == "R") {
            std::system(("python3 " + std::string(pythonFilePath)).c_str());
        } else {
            view.hide();
        }

    });

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject::connect(&oilStorage, &OilReceiver::oilValueChanged, [&](const double& currentOilValue) {
            if (currentOilValue <= 50.0) {
                player.setMedia(QUrl::fromLocalFile("/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/mp3/fuel.mp3"));
                player.play();
            }
        });

    QObject::connect(&handleStorage, &HandleReceiver::handleValueChanged, [&](const double& currentHandleValue) {
            if (currentHandleValue >= 130.0) {
                player2.setMedia(QUrl::fromLocalFile("/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/mp3/sleep.mp3"));
                player2.play();
            }
        });




//    QMediaPlayer player;
//    player.setMedia(QUrl::fromLocalFile("/home/wogur/sea-me-hackathon-2023_0713_jhdhsh/Cluster/src/mp3/fuel.mp3"));
//    player.play();

//    std::system("python3 mp3/fuel.py");
// sudo apt install sox

    
//    std::system(("python3 " + std::string(pythonFilePath)).c_str());
    


    return app.exec();
}



// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>
// #include "SpeedReceiver.h"
// #include "ButtonsReceiver.h"
// #include "RPMReceiver.h"
// #include "oilreceiver.h"
// #include <qqml.h>
// #include <QMetaType>
// #include <string>
// #include <iostream>
// #include <thread>
// #include <CommonAPI/CommonAPI.hpp>
// #include "ClusterStubImpl.hpp"
// #include "HandleReceiver.h"
// #include "WeatherAPI.h"
// #include <QApplication>
// #include <QWebEngineView>
// #include <QWebEngineProfile>
// #include <QWebChannel>
// #include <QDesktopServices>
// #include <QUrl>

// using namespace std;
// Q_DECLARE_METATYPE(std::string)

// int main(int argc, char *argv[])
// {
//     qRegisterMetaType<std::string>();

//     std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
//     std::shared_ptr<ClusterStubImpl> myService =
//         std::make_shared<ClusterStubImpl>();
//     runtime->registerService("local", "cluster_service", myService);
//     std::cout << "Successfully Registered Service!" << std::endl;

//     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//     QApplication app(argc, argv);
//     QQmlApplicationEngine engine;

//     SpeedReceiver speedStorage;
//     ButtonsReceiver buttonStorage;
//     RPMReceiver rpmStorage;
//     OilReceiver oilStorage;
//     HandleReceiver handleStorage;
//     WeatherAPI weatherAPIStorage;

//     engine.rootContext()->setContextProperty("speedReceiver", &speedStorage);
//     engine.rootContext()->setContextProperty("buttonsReceiver", &buttonStorage);
//     engine.rootContext()->setContextProperty("rpmReceiver", &rpmStorage);
//     engine.rootContext()->setContextProperty("oilReceiver", &oilStorage);    
//     engine.rootContext()->setContextProperty("handleReceiver", &handleStorage);
//     engine.rootContext()->setContextProperty("weatherAPI", &weatherAPIStorage);

//     QObject::connect(&(*myService), &ClusterStubImpl::signalSpeed, &speedStorage, &SpeedReceiver::receiveSpeed); 
//     QObject::connect(&(*myService), &ClusterStubImpl::signalButtons, &buttonStorage, &ButtonsReceiver::receiveButtons);
//     QObject::connect(&(*myService), &ClusterStubImpl::signalRPM, &rpmStorage, &RPMReceiver::receiveRPM);
//     QObject::connect(&(*myService), &ClusterStubImpl::signalOil, &oilStorage, &OilReceiver::receiveOil);
//     QObject::connect(&(*myService), &ClusterStubImpl::signalHandle, &handleStorage, &HandleReceiver::receiveHandle);

//     engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//     if (engine.rootObjects().isEmpty())
//         return -1;

//     QWebEngineView view;

//     QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
//     profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
//     profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
//     profile->setHttpUserAgent("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.122 Safari/537.36");

//     view.setPage(new QWebEnginePage(profile, &view));

//     QString url = "http://localhost:8000/human.html";
//     view.load(QUrl(url));
//     view.show();
//     return app.exec();
// }


// #include <QApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>
// #include "SpeedReceiver.h" // Include the new header
// #include "ButtonsReceiver.h"
// #include "RPMReceiver.h"
// #include "oilreceiver.h"
// #include <qqml.h>
// #include <QMetaType>
// #include <string>
// #include <iostream>
// #include <thread>
// #include <CommonAPI/CommonAPI.hpp>
// #include "ClusterStubImpl.hpp"
// #include "HandleReceiver.h"
// #include "WeatherAPI.h"
// #include <QApplication>
// #include <QWebEngineView>
// #include <QWebChannel>
// #include <QDesktopServices>
// #include <QUrl>
// #include <cstdlib>

// using namespace std;
// Q_DECLARE_METATYPE(std::string)

// int main(int argc, char *argv[])
// {
//     qRegisterMetaType<std::string>();

//     std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
//     std::shared_ptr<ClusterStubImpl> myService =
//         std::make_shared<ClusterStubImpl>();
//     runtime->registerService("local", "cluster_service", myService);
//     std::cout << "Successfully Registered Service!" << std::endl;

//     QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//     QApplication app(argc, argv);
//     QQmlApplicationEngine engine;

//     SpeedReceiver speedStorage;
//     ButtonsReceiver buttonStorage;
//     RPMReceiver rpmStorage;
//     OilReceiver oilStorage;
//     HandleReceiver handleStorage;
//     WeatherAPI weatherAPIStorage;

//     engine.rootContext()->setContextProperty("speedReceiver", &speedStorage);
//     engine.rootContext()->setContextProperty("buttonsReceiver", &buttonStorage);
//     engine.rootContext()->setContextProperty("rpmReceiver", &rpmStorage);
//     engine.rootContext()->setContextProperty("oilReceiver", &oilStorage);    
//     engine.rootContext()->setContextProperty("handleReceiver", &handleStorage);
//     engine.rootContext()->setContextProperty("weatherAPI", &weatherAPIStorage);

//     QObject::connect(&(*myService), &ClusterStubImpl::signalSpeed, &speedStorage, &SpeedReceiver::receiveSpeed); // Connect the instances
//     QObject::connect(&(*myService), &ClusterStubImpl::signalButtons, &buttonStorage, &ButtonsReceiver::receiveButtons); // Connect the instances
//     QObject::connect(&(*myService), &ClusterStubImpl::signalRPM, &rpmStorage, &RPMReceiver::receiveRPM); // Connect the instances
//     QObject::connect(&(*myService), &ClusterStubImpl::signalOil, &oilStorage, &OilReceiver::receiveOil); // Connect the instances
//     QObject::connect(&(*myService), &ClusterStubImpl::signalHandle, &handleStorage, &HandleReceiver::receiveHandle); // Connect the instances

//     // Create a QWebEngineView
//     QWebEngineView webEngineView;
//     webEngineView.resize(200, 200);

//     // Create a QWebChannel and register C++ object
//     QWebChannel webChannel;
//     webChannel.registerObject(QStringLiteral("myService"), myService.get());

//     // Load the HTML file
//     webEngineView.setHtml(R"(
//         <!DOCTYPE html>
//         <html>
//         <head>
//             <title>Teachable Machine Image Model</title>
//         </head>
//         <body>
//             <div>Teachable Machine Image Model</div>
//             <div id="webcam-container"></div>
//             <div id="label-container"></div>

//             <script src="https://cdn.jsdelivr.net/npm/@tensorflow/tfjs@latest/dist/tf.min.js"></script>
//             <script src="https://cdn.jsdelivr.net/npm/@teachablemachine/image@latest/dist/teachablemachine-image.min.js"></script>
//             <script type="text/javascript">
//                 const URL = "https://teachablemachine.withgoogle.com/models/DsSGEzan3/";
//                 let model, webcam, labelContainer, maxPredictions;

//                 async function init() {
//                     const modelURL = URL + "model.json";
//                     const metadataURL = URL + "metadata.json";

//                     model = await tmImage.load(modelURL, metadataURL);
//                     maxPredictions = model.getTotalClasses();

//                     const flip = true;
//                     webcam = new tmImage.Webcam(200, 200, flip);
//                     await webcam.setup();
//                     await webcam.play();
//                     window.requestAnimationFrame(loop);

//                     document.getElementById("webcam-container").appendChild(webcam.canvas);
//                     labelContainer = document.getElementById("label-container");
//                     for (let i = 0; i < maxPredictions; i++) {
//                         labelContainer.appendChild(document.createElement("div"));
//                     }
//                 }

//                 async function loop() {
//                     webcam.update();
//                     await predict();
//                     window.requestAnimationFrame(loop);
//                 }

//                 async function predict() {
//                     const prediction = await model.predict(webcam.canvas);
//                     for (let i = 0; i < maxPredictions; i++) {
//                         const classPrediction =
//                             prediction[i].className + ": " + prediction[i].probability.toFixed(2);
//                         labelContainer.childNodes[i].innerHTML = classPrediction;
//                     }
//                 }

//                 window.onload = init;
//             </script>
//         </body>
//         </html>
//     )");

//     webEngineView.page()->setWebChannel(&webChannel);
//     webEngineView.show();
//     return app.exec();
// }

