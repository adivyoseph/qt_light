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


//connect button
void MainWindow::on_pushButton_clicked()
{

    if(connect_state){
        //current state connected
         p_mqtt->mqtt_disconnect();

    }
    else {

        p_mqtt->mqtt_setRoom(getConfigRoom());
        p_mqtt->mqtt_setLight(getConfigLight());
        p_mqtt->mqtt_connect();
    }
}

void MainWindow::on_connect_event(int state){
    qDebug() << "on_connect_event" << state;
    if(state){
       ui->pushButton->setText("Disconnect");
       connect_state = 1;
   }
   else {
       ui->pushButton->setText("Connect");
       connect_state = 0;
       light_state_set(0);
   }
}

void MainWindow::light_state_set(int state){
    if(state){
        ui->Light->setCheckState(Qt::Checked);
        light_state = 1;
        p_mqtt->mqtt_publish(1);
    }
    else {
        ui->Light->setCheckState(Qt::Unchecked);
        light_state = 0;
        p_mqtt->mqtt_publish(0);
    }
}

void MainWindow::on_switch_event(int event){
    qDebug() << "mqtt_switch_event " << event;
    if(light_state){
        light_state_set(0);
    }
    else {
        light_state_set(1);
    }
}


void MainWindow::on_switch_level(int event){
    qDebug() << "mqtt_switch_level " << event;
    ui->verticalSlider->setValue(event);
}


void MainWindow::on_actionConfigure_triggered()
{
    configDialog.show();
}

void MainWindow::on_configChanged(){
    QString text = QString("%1//%2").arg(configDialog.getRoomName(), configDialog.getLightName());

    ui->labelTopic->setText(text );
}

QString MainWindow::getConfigRoom(){
    return configDialog.getRoomName();
}
QString  MainWindow::getConfigLight(){
    return configDialog.getLightName();
}

