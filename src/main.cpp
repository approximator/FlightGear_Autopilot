#include "mainwindow.h"

#include <QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine(QUrl("qrc:/res/qml/main.qml"));

    QStringList aircrafts;
    aircrafts.append("Aircraft 1");
    aircrafts.append("Aircraft 2");
    aircrafts.append("Long Long Long Long Long aircraft name");
    aircrafts.append("Aircraft 3");
    aircrafts.append("Aircraft 4");
    engine.rootContext()->setContextProperty("aircraftsModel", QVariant::fromValue(aircrafts));

    return app.exec();
}
