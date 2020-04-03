#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt_sub.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetMqtt(MQTT_sub *p_mqtt);

private slots:
    void on_pushButton_clicked();

public slots:
    void mqtt_switch_event(int);
    void mqtt_switch_level(int);

private:
    Ui::MainWindow *ui;
    MQTT_sub *p_mqtt;
    int connect_state = 0;
};

#endif // MAINWINDOW_H
