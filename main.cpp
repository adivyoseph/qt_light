#include "mainwindow.h"
#include <QApplication>
#include "mqtt_sub.h"
#include <QObject>
#include <QtCore>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MQTT_sub myMqtt;

    w.SetMqtt(&myMqtt);
    myMqtt.setMainWindow(&w);
    QObject::connect(&myMqtt, SIGNAL(mqtt_switch_event(int)), &w, SLOT(mqtt_switch_event(int)));
    QObject::connect(&myMqtt, SIGNAL(mqtt_switch_level(int)), &w, SLOT(mqtt_switch_level(int)));

    w.show();

    return a.exec();
}
