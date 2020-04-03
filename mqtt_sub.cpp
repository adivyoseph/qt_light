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




void my_connect_callback(struct mosquitto *mosq, void *obj, int result, int flags, const mosquitto_property *properties)
{


    UNUSED(mosq);
    UNUSED(flags);
    UNUSED(properties);
   MQTT_sub * pthis = (MQTT_sub * ) obj;

    qDebug() << "connect_callback " << result;
    //pthis->pm_set_state(1);

}

void my_disconnect_callback(struct mosquitto *mosq, void *obj, int rc, const mosquitto_property *properties)
{
    UNUSED(mosq);
    UNUSED(obj);
    UNUSED(rc);
    UNUSED(properties);
    MQTT_sub * pthis = (MQTT_sub * ) obj;

    qDebug() << "disconnect_callback " << rc;
    //pthis->pm_set_state(0);
    //mosquitto_unsubscribe_v5(mosq, NULL, cfg.unsub_topics[i], cfg.unsubscribe_props);

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

    qDebug() << "message_callback " << msg->topic << "len " << msg->payloadlen;

    // topic
    if( strcmp("bedroom/main_switch_level",msg->topic) == 0){
        int value = atoi(pchar);
        if(value <= 100){
            emit pthis->mqtt_switch_level(value);
        }
    }
    else if(strcmp("bedroom/main_switch",msg->topic) == 0){
        if(msg->payloadlen == 3){
            emit pthis->mqtt_switch_event(1);
        }
        else {
            emit pthis->mqtt_switch_event(0);
        }
    }


}



void MQTT_sub::setMainWindow(void * pointer){
    pMainWindow = pointer;

    mosquitto_connect_v5_callback_set(mosq, my_connect_callback);
    mosquitto_disconnect_v5_callback_set(mosq, my_disconnect_callback);
    mosquitto_message_v5_callback_set(mosq, my_message_callback);

    //QObject::connect(this, SIGNAL(mqtt_switch_event), (MainWindow *)pMainWindow, SLOT(MainWindow::mqtt_switch_event));
}


int MQTT_sub::mqtt_connect(){
    int rc;
    int mid = 5;
    qDebug() <<  "mqtt_connect";



    rc = mosquitto_connect_bind_v5(mosq, (const char *) host.c_str(), port, host.size(), (const char *) host.c_str(), nullptr);
    if(rc>0){
        qDebug() <<  "Error: mosquitto_connect_bind_v5 " << rc;
        return 1;
    }
    else{
        qDebug() <<  "mosquitto_connect_bind_v5";
        state = 1;
        rc = mosquitto_subscribe_v5(mosq, nullptr,  "bedroom/main_switch_level", 0, 0, nullptr);
        rc = mosquitto_subscribe_v5(mosq, nullptr,  "bedroom/main_switch", 0, 0, nullptr);
        qDebug() <<  "subscribe_v5" << rc;
        mosquitto_loop_start(mosq);

    }


    return 0;
}

int MQTT_sub::mqtt_disconnect(){
    int rc = 0;
    if(state){
         mosquitto_loop_stop(mosq, true);
         rc =mosquitto_disconnect(mosq);
         qDebug() <<  "mosquitto_disconnect rc " << rc;
         state = 0;
    }
    return rc;
}




