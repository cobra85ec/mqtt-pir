#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include "config.h"
int pirPin = 7;
int val;


// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
byte ip[]     = { 192, 168, 1, 200 };


EthernetClient ethClient;
PubSubClient client(MQTT_SERVER, 1883, 0, ethClient);


void setup() {
  Ethernet.begin(mac);
  client.connect(CLIENT_ID);
  client.publish(MQTT_TOPIC,"Sensor UP");
}

void loop() {
  val = digitalRead(pirPin); //read state of the PIR
  
  if (val == LOW) {
    client.publish(MQTT_TOPIC, "0");
  }
  else {
    client.publish(MQTT_TOPIC,"1");
  }
  
  delay(1000);
  client.loop();
}
