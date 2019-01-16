#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <Servo.h>

#ifndef STASSID
#define STASSID "Lordy"
#define STAPSK  "benjaminchristopherlord"
#define DEVID   "WifiServoA"
#endif

#define SERIAL_BUF_LENGTH 128

unsigned int localPort = 8888;      // local port to listen on
char UDPpktBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char SerialBuffer[SERIAL_BUF_LENGTH];
char ReplyBuffer[UDP_TX_PACKET_MAX_SIZE]; // a string to send back

#define NUM_SERVOS        10
Servo servoArray[NUM_SERVOS];
short servoPins[] = {0,2,4,5,9,10,12,13,14,15,16};

bool ProcessSerialCommand = false;
bool ProcessUDPCommand = false;

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  Serial.write(PSTR("Wifi Servo Controller\r\n"));
  printCommandList();
  WiFi.mode(WIFI_STA);  
  WiFi.begin(STASSID, STAPSK);
  for(int i = 0; i < NUM_SERVOS; i++)
  {
     servoArray[i].attach(servoPins[i]);
     servoArray[i].write(90);
  }
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}

void loop() {
  if(Udp.parsePacket())
  {
    getUDP();
  }
  if(Serial.available())
  {
    getSerial();
  }
  if(ProcessSerialCommand)
  {
    ProcessSerialCommand = false;
    processCommand(&SerialBuffer[0]);
  }
  if(ProcessUDPCommand)
  {
    ProcessUDPCommand = false;
    processCommand(&UDPpktBuffer[0]);
    for(int i = 0; i < SERIAL_BUF_LENGTH ; i++) UDPpktBuffer[i] = 0;
  }

}

int initWifi()
{
}

void getUDP()
{
    Udp.read(UDPpktBuffer, UDP_TX_PACKET_MAX_SIZE);
    ProcessUDPCommand = true;
//      // send a reply, to the IP address and port that sent us the packet we received
//    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
//    Udp.write(ReplyBuffer);
//    Udp.endPacket();


}

void getSerial()
{
  static int length = 0;
  while (Serial.available()) 
  {
      int data = Serial.read();
      if (data == '\b' || data == '\177') {  // BS and DEL
        if (length) {
          length--;
          Serial.write("\b \b");
        }
      }
      else if (data == '\r' || data == ';') {
        Serial.write("\r\n");    // output CRLF
        SerialBuffer[length] = '\0';
        if (length){
          ProcessSerialCommand = true;
          length = 0;
        }
      }
      else if (length < SERIAL_BUF_LENGTH - 1) {
            SerialBuffer[length++] = data;
            Serial.write(data);
      }
  }
}
