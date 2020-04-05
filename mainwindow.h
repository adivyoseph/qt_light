#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mqtt_sub.h"
#include "lightconfig.h"

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void     SetMqtt(MQTT_sub *p_mqtt);
    QString  getConfigRoom();
    QString  getConfigLight();
    void     light_state_set(int);

private slots:
    void on_pushButton_clicked();

    void on_actionConfigure_triggered();

    void on_switch_event(int);

    void on_switch_level(int);

    void on_connect_event(int);

public slots:


    void on_configChanged();

private:
    Ui::MainWindow *ui;
    LightConfig configDialog;
    MQTT_sub *p_mqtt;
    int connect_state = 0;
    int light_state = 0;
};

#endif // MAINWINDOW_H
