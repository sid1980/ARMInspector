#include <QApplication>
#include <QtQml/QQmlApplicationEngine>

#include "ServerClient.h"
#include "ClientController.h"
#include "CoreLogger.h"
#include "JsonSerializer.h"
#include "ModelWrapper.h"
#include "myForm.h"
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    //QGuiApplication app(argc, argv);
    QApplication app(argc, argv);

    //QQmlApplicationEngine engine;

    //const QUrl url(QStringLiteral("qrc:/main.qml"));
    //QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
    //        &app, [url](QObject *obj, const QUrl & objUrl) {
    //            if (!obj && url == objUrl)
    //                QCoreApplication::exit(-1);
    //        }, Qt::QueuedConnection);
    //engine.load(url);

    /// Создание обработчика событий логирования.
    CoreLogger coreLogger;
#if defined(Q_OS_LINUX)
    coreLogger.setLogFile(QString("/opt/ARMInspector/log/%1GUI.log").arg(ARM_BRAND));
#elif defined (Q_OS_WIN)
    coreLogger.setLogFile(QString("%1/%2GUI.log").arg(QCoreApplication::applicationDirPath()).arg(ARM_BRAND));
#endif

    /// Клиент.
    ServerClient serverClient;
    /// Контроллер-обработчик RPC-протокола.
    ClientController &clientController = ClientController::getInstance();
    clientController.init(&serverClient);
    /// Подключение к серверу.
    serverClient.connectToServer();
    ///Ждать сигнала установления соединения с сервером и присвоения ID клиенту .
    clientController.waitReady();
    ///Сигнал получен. 
    ///На сервере клиенту создана сессия.
    ///Можно на сервере  выполнять операции с данными и
    ///получать результат обработки.
    QApplication::setQuitOnLastWindowClosed(true);
    myForm form;
    form.initClient(&clientController);
    //form.initApp(&app);
    form.show();
    clientController.waitReady();
    form.hide();
    if (!clientController.getLogged()) {
        return 0;
    }
    /// ПРИМЕР ИСПОЛЬЗОВАНИЯ
    //clientController.getListModels("Select * from pass_list", ModelWrapper::Model::PassList);QApplication app(argc, argv);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.initClient(&clientController);
    w.show();
    return app.exec();
}
