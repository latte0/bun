#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QtQml>
#include <QQuickView>
#include <QObject>
#include <QQuickItem>
#include "qtquick2applicationviewer.h"
#include "ImageProvider.h"
#include "FileIO.h"
#include "Timefunction.h"
#include "Timeprocess.h"
#include "Ipget.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FileIO, 1>("FileIO", 1, 0, "FileIO");
        qmlRegisterType<Timeprocess,1>("TimePro",1,0,"TimePro");
        qmlRegisterType<Ipget,1>("IpGet",1,0,"IpGet");
        QQuickView view;
    QQmlEngine* engine = view.engine();

    Timefunction time;

    view.rootContext()->setContextProperty("timefunction", &time);

    view.setSource(QUrl::fromLocalFile("qml/question/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    engine->addImageProvider(QLatin1String("codeimage"), new ImageProvider);
    view.showFullScreen();
    QQuickItem *item = view.rootObject();

    QObject::connect(item,SIGNAL(quit()),&app,SLOT(quit()));

    return app.exec();
}
