#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&configDialog, SIGNAL(configChanged()), this, SLOT(on_configChanged()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::SetMqtt(MQTT_sub *p_mqtt_arg){
    p_mqtt = p_mqtt_arg;
}

void MainWindow::on_pushButton_clicked()
{
    QString buttonText = "";
    if(connect_state){
        //current state connected
        buttonText = "Connect";
        p_mqtt->mqtt_disconnect();
        ui->pushButton->setText(buttonText);
        connect_state = 0;   //new state disconnected
        ui->Light->setCheckState(Qt::Unchecked);
    }
    else {
        buttonText = "Disconnect";
        p_mqtt->mqtt_setRoom(getConfigRoom());
        p_mqtt->mqtt_setPri(getConfigPri());
        p_mqtt->mqtt_setSec(getConfigSec());
        p_mqtt->mqtt_connect();
        ui->pushButton->setText(buttonText);
        connect_state = 1;
    }
}


void MainWindow::mqtt_switch_event(int event){
    qDebug() << "mqtt_switch_event " << event;
    if(event){
        ui->Light->setCheckState(Qt::Checked);
    }
    else {
        ui->Light->setCheckState(Qt::Unchecked);
    }
}


void MainWindow::mqtt_switch_level(int event){
    qDebug() << "mqtt_switch_level " << event;
    ui->verticalSlider->setValue(event);
}


void MainWindow::on_actionConfigure_triggered()
{
    configDialog.show();
}

void MainWindow::on_configChanged(){
    QString text = QString("%1\\%2").arg(configDialog.getRoomName(), configDialog.getSwitchPri());

    ui->labelTopic->setText(text );
}

QString MainWindow::getConfigRoom(){
    return configDialog.getRoomName();
}
QString  MainWindow::getConfigPri(){
    return configDialog.getSwitchPri();
}
QString  MainWindow::getConfigSec(){
    return configDialog.getSwitchSec();
}
