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
#define NUM_SERVOS        10

unsigned int localPort = 8888;      // local port to listen on
char UDPpktBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char SerialBuffer[SERIAL_BUF_LENGTH];
char ReplyBuffer[UDP_TX_PACKET_MAX_SIZE]; // a string to send back

Servo servoArray[NUM_SERVOS];

bool ProcessSerialCommand = false;

WiFiUDP Udp;

void processCommand(char *);
void getSerial(void);
int initWifi(void);

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);  
  WiFi.begin(STASSID, STAPSK);
  for(int i = 0; i < NUM_SERVOS; i++)
  {
     servoArray[i].attach(i);
     servoArray[i].write(90);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available())
  {
    getSerial();
  }
  if(ProcessSerialCommand)
  {
    ProcessSerialCommand = false;
    processCommand(&SerialBuffer[0]);
  }

}

int initWifi()
{
  
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
      else if (data == '\r') {
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
