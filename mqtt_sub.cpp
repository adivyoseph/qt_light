#include "mqtt_sub.h"
#include <QtCore>
#include <QDebug>
#include "mainwindow.h"

#define UNUSED(expr) (void)(expr)

MQTT_sub::MQTT_sub()
{
    host = "localhost";
    mosquitto_lib_init();
    mosq = mosquitto_new(nullptr, true, this);
    if(!mosq){
        qDebug() <<  "Error: mosquitto_new failed";

    }


}

void MQTT_sub::mqtt_set_connect_state(int state){
    connect_state = state;
}


void my_connect_callback(struct mosquitto *mosq, void *obj, int result, int flags, const mosquitto_property *properties)
{


    UNUSED(mosq);
    UNUSED(flags);
    UNUSED(properties);
    MQTT_sub * pthis = (MQTT_sub * ) obj;

    qDebug() << "connect_callback " << result;
    pthis->mqtt_set_connect_state(1);
    emit pthis->mqtt_connect_event(1);

}

void my_disconnect_callback(struct mosquitto *mosq, void *obj, int rc, const mosquitto_property *properties)
{
    UNUSED(mosq);
    UNUSED(obj);
    UNUSED(rc);
    UNUSED(properties);
    MQTT_sub * pthis = (MQTT_sub * ) obj;

    qDebug() << "disconnect_callback " << rc;
    pthis->mqtt_set_connect_state(0);
    emit pthis->mqtt_connect_event(0);

}

/*
struct mosquitto_message{
    int mid;
    char *topic;
    void *payload;
    int payloadlen;
    int qos;
    bool retain;
};
*/
void my_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg, const mosquitto_property *properties){
    char *pchar = (char *) msg->payload;
    MQTT_sub * pthis = (MQTT_sub * ) obj;
    QString topicSwitch;
    QString topicLevel;

    topicSwitch = QString("%1\\%2_switch").arg(pthis->mqtt_getRoom(), pthis->mqtt_getLight());
    topicLevel  = QString("%1\\%2_level").arg(pthis->mqtt_getRoom(), pthis->mqtt_getLight());


    qDebug() << "message_callback " << msg->topic << "len " << msg->payloadlen;
    //only get here when connected



    // topic
    if( strcmp(topicLevel.toStdString().c_str(),msg->topic) == 0){
        //qDebug() << "   level ";
        int value = atoi(pchar);
        if(value <= 100){
            emit pthis->mqtt_switch_level(value);
        }
    }
    else if(strcmp(topicSwitch.toStdString().c_str(),msg->topic) == 0){
            emit pthis->mqtt_switch_event(1);
    }
}



void MQTT_sub::setMainWindow(void * pointer){
    pMainWindow = pointer;

    mosquitto_connect_v5_callback_set(mosq, my_connect_callback);
    mosquitto_disconnect_v5_callback_set(mosq, my_disconnect_callback);
    mosquitto_message_v5_callback_set(mosq, my_message_callback);

    //QObject::connect(this, SIGNAL(mqtt_switch_event), (MainWindow *)pMainWindow, SLOT(MainWindow::mqtt_switch_event));
}

void  MQTT_sub::mqtt_publish(int state){
    int mid = 5;
    int rc =1;
    QString topic = QString("%1\\%2_light").arg(stringRoom, stringLight);
    QString msg  = QString("%1").arg(state);

    qDebug() <<  "mqtt_pubSwitch state  " << connect_state;
    if(connect_state)
    {
        rc = mosquitto_publish_v5(mosq, &mid, topic.toStdString().c_str(), msg.size(), msg.toStdString().c_str(), 0, 0, nullptr);
        qDebug() <<  "mqtt_pub rc " << rc;
    }
}


int MQTT_sub::mqtt_connect(){
    int rc;
    int mid = 5;
    qDebug() <<  "mqtt_connect";

    QString topicSwitch;
    QString topicLevel;

    topicSwitch = QString("%1\\%2_switch").arg(stringRoom, stringLight);
    topicLevel = QString("%1\\%2_level").arg(stringRoom, stringLight);


    rc = mosquitto_connect_bind_v5(mosq, (const char *) host.c_str(), port, host.size(), (const char *) host.c_str(), nullptr);
    if(rc>0){
        qDebug() <<  "Error: mosquitto_connect_bind_v5 " << rc;
        return 1;
    }
    else{
        qDebug() <<  "mosquitto_connect_bind_v5";
        rc = mosquitto_subscribe_v5(mosq, nullptr,  topicSwitch.toStdString().c_str(), 0, 0, nullptr);
        rc = mosquitto_subscribe_v5(mosq, nullptr,  topicLevel.toStdString().c_str(), 0, 0, nullptr);

        qDebug() <<  "subscribe_v5" << rc;
        mosquitto_loop_start(mosq);

    }


    return 0;
}

int MQTT_sub::mqtt_disconnect(){
    int rc = 0;
    int mid = 5;
    QString topicSwitch;
    QString topicLevel;

    topicSwitch = QString("%1\\%2_switch").arg(stringRoom, stringLight);
    topicLevel = QString("%1\\%2_level").arg(stringRoom, stringLight);

    if(connect_state){
         mosquitto_loop_stop(mosq, true);
         //
         rc = mosquitto_unsubscribe_v5(mosq, nullptr,  topicSwitch.toStdString().c_str(),  nullptr);
         rc = mosquitto_unsubscribe_v5(mosq, nullptr,  topicLevel.toStdString().c_str(),  nullptr);
         rc =mosquitto_disconnect(mosq);
         qDebug() <<  "mosquitto_disconnect rc " << rc;
         //state = 0;
    }
    return rc;
}

void MQTT_sub::mqtt_setRoom(QString room){
    stringRoom = room;
}

void MQTT_sub::mqtt_setLight(QString light){
    stringLight = light;
}

QString MQTT_sub::mqtt_getLight(){
    return stringLight;
}

QString MQTT_sub::mqtt_getRoom(){
    return stringRoom;
}





