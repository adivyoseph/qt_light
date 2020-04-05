#ifndef MQTT_SUB_H
#define MQTT_SUB_H


#include <mqtt_protocol.h>
#include <mosquitto.h>
#include <QObject>






class MQTT_sub : public QObject
{
    Q_OBJECT


public:
   MQTT_sub();
   virtual ~MQTT_sub() {};
   void setMainWindow(void *);
   int mqtt_connect();
   int mqtt_disconnect();
   void mqtt_publish(int);

   void mqtt_setRoom(QString room);
   QString mqtt_getRoom();
   void mqtt_setLight(QString name);
   QString  mqtt_getLight();

   void mqtt_set_connect_state(int);



signals:
   void mqtt_switch_event(int);
   void mqtt_switch_level(int);
   void mqtt_connect_event(int);

private:

    struct mosquitto *mosq;
    QString stringRoom;
    QString stringLight;

    int connect_state = 0;
    int port  = 1883;
    std::string host;

    void * pMainWindow;
 };

#endif // MQTT_SUB_H
