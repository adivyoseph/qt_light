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

signals:
   void mqtt_switch_event(int);
   void mqtt_switch_level(int);

private:

    struct mosquitto *mosq;
    int state = 0;
    int port  = 1883;
    std::string host;

    void * pMainWindow;
 };

#endif // MQTT_SUB_H
