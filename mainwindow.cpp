#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    std::string buttonText = "";
    if(connect_state){
        buttonText = "Connect";
        p_mqtt->mqtt_disconnect();
        ui->pushButton->setText(buttonText.c_str());
        connect_state = 0;
        ui->Light->setCheckState(Qt::Unchecked);
    }
    else {
        buttonText = "Disconnect";
        p_mqtt->mqtt_connect();
        ui->pushButton->setText(buttonText.c_str());
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

