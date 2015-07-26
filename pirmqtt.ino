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
PubSubClient client(MQTT_SERVER, 1883, 0, CLIENT_ID);


void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
    Ethernet.begin(mac);
  client.connect("arduinoClient");
client.publish(MQTT_TOPIC,"Sensor UP");
}

void loop() {
  val = digitalRead(pirPin); //read state of the PIR
  
  if (val == LOW) {
    digitalWrite(11, LOW);

  }
  else {
  
    digitalWrite(11, HIGH);
    Serial.println("Motion!"); //if the value read was high, there was motion
    client.publish(MQTT_TOPIC,"Motion");
  }
  
  delay(1000);
}
