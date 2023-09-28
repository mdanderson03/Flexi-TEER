/*
 This example connects to an unencrypted WiFi network.
 Then it prints the MAC address of the WiFi module,
 the IP address obtained, and other network details.
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoMqttClient.h>





#define SECRET_SSID "raspi-webgui" // your WiFi access point name
#define SECRET_PASS "ChangeMe" // your WiFi password 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status


const char broker[] = "10.3.141.1"; // Address of the MQTT server
int        port     = 1883;
const char topic[]  = "control/#";
const char IR1[]  = "readings/IR1";
const char IR2[]  = "readings/IR2";

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);



#define SLP A7
#define STP A6




int cmd1 = 0;
int cmd2 = 0;
int cmd3 = 0;
int message = 0;
int pump_delay = 2;


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  //while (!Serial) {
 //   ; // wait for serial port to connect. Needed for native USB port only
  //}

  // attempt to connect to WiFi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // You can provide a username and password for authentication
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic);
  

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Waiting for messages on topic: ");
  Serial.println(topic);
  Serial.println();


pinMode(A7, OUTPUT);
pinMode(A6, OUTPUT);
pinMode(A5, OUTPUT);
pinMode(2, OUTPUT);
pinMode(3, OUTPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);

pinMode(A0, INPUT);
pinMode(A2, INPUT);

digitalWrite(A7, LOW);
digitalWrite(A5, LOW);

}


void loop() {




//int messageSize = mqttClient.parseMessage();
//String topic = String(mqttClient.messageTopic());
//String subtopic = topic.substring(8);

  if (mqttClient.parseMessage() > 0) {
    Serial.print("Got a message on topic: ");
    String topic = String(mqttClient.messageTopic());
    String subtopic = topic.substring(8);
    Serial.println(subtopic);

    // read the message:
    while (mqttClient.available()) {
      // convert numeric string to an int:
      int message = mqttClient.parseInt();
      Serial.println(message);
      cmd1 = message/100;
      cmd2 = (message - cmd1*100)/10;
      cmd3 = message - cmd1*100 - cmd2*10;
      Serial.println(cmd1);
      Serial.println(cmd2);
      Serial.println(cmd3);
    
    

      if (subtopic == "peristaltic"){
        if (cmd1 == 1){
          Serial.println(" turned pump on");
          digitalWrite(A7, HIGH);
        }
        if (cmd1 == 0 && cmd2 != 0){
          Serial.println("pump off");
          digitalWrite(A7, LOW);
        }
        if (cmd2 > 0){
        pump_delay = cmd2;
        }
      }

      if (subtopic == "valve"){
        if (cmd1 == 1){
          if (cmd2 == 1){
          digitalWrite(6, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(6, LOW);
          }
        }

        if (cmd1 == 2){
          if (cmd2 == 1){
          digitalWrite(7, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(7, LOW);
          }
        }

        if (cmd1 == 3){
          if (cmd2 == 1){
          digitalWrite(8, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(8, LOW);
          }
        }

        if (cmd1 == 4){
          if (cmd2 == 1){
          digitalWrite(9, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(9, LOW);
          }
        }

        if (cmd1 == 5){
          if (cmd2 == 1){
          digitalWrite(10, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(10, LOW);
          }
        }

        if (cmd1 == 6){
          if (cmd2 == 1){
          digitalWrite(11, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(11, LOW);
          }
        }

        if (cmd1 == 7){
          if (cmd2 == 1){
          digitalWrite(12, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(12, LOW);
          }
        }

        if (cmd1 == 8){
          if (cmd2 == 1){
          digitalWrite(13, HIGH);
          }
          if (cmd2 ==0){
          digitalWrite(13, LOW);
          }
        }      
      }
    
    if (subtopic == "dc_pump"){
      if (cmd1 == 1){
        if (cmd2 == 1){
          digitalWrite(2, HIGH);
        }
        if (cmd2 == 0){
          digitalWrite(2, LOW);
        }
        if (cmd3 == 1){
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
        }
        if (cmd3 == 0){
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
        }
      }

      if (cmd1 == 2){
        if (cmd2 == 1){
          digitalWrite(5, HIGH);
        }
        if (cmd2 == 0){
          digitalWrite(5, LOW);
        }
      }
    }
    
 }
  }  
  
    
//mqttClient.beginMessage(IR1);
    // add the value:
//mqttClient.print(analogRead(A0));
    // send the message:
//mqttClient.endMessage();

//mqttClient.beginMessage(IR2);
    // add the value:
//mqttClient.print(analogRead(A2));
    // send the message:
//mqttClient.endMessage();

    
  
digitalWrite(A6, HIGH);
delay(pump_delay);
digitalWrite(A6, LOW);

}
