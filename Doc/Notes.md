
Dev Board:
https://www.amazon.com/gp/product/B010N1SPRK

Instructions:
Product description:
ESP8266 is a highly integrated chip designed for the needs of a new connected world. It offers a complete and self-contained Wi-Fi networking solution, allowing it to either host the application or to offload all Wi-Fi networking functions from another application processor. 
Instruction & Steps of How to use:
1. Download the Arduino IDE, the latest version. 
2. Install the IDE
3. Set up your Arduino IDE as: Go to File->Preferences and copy the URL below to get the ESP board manager extensions: http://arduino.esp8266.com/stable/package_esp8266com_index.json Placing the http:// before the URL lets the Arduino IDE use it...otherwise it gives you a protocol error.
4. Go to Tools > Board > Board Manager> Type "esp8266" and download the Community esp8266 and install. 
5. Set up your chip as:
Tools -> Board -> NodeMCU 1.0 (ESP-12E Module)
Tools -> Flash Size -> 4M (3M SPIFFS)
Tools -> CPU Frequency -> 80 Mhz
Tools -> Upload Speed -> 921600
Tools-->Port--> (whatever it is)
6. Download and run the 32 bit flasher exe at Github(Search for nodemcu/nodemcu-flasher/tree/master/ at Github) github.com/nodemcu/nodemcu-flasher/tree/master/Win32/Release Or download and run the 64 bit flasher exe at: github.com/nodemcu/nodemcu-flasher/tree/master/Win64/Release
7. In Arduino IDE, look for the old fashioned Blink program. Load, compile and upload. 
8. Go to FILE> EXAMPLES> ESP8266> BLINK, it will start blinking. 

Note: Please contact us if you need the driver or meet any issue when using. We provide 100% satisfication service for customers. 

Package included: 
2* New Version ESP8266 NodeMCU LUA CP2102 WiFi Wireless Development Board

https://github.com/nodemcu/nodemcu-flasher


ComandLine Parser:
https://gist.githubusercontent.com/edgar-bonet/607b387260388be77e96/raw/de29a5428bff34a9d820fcef291ad253ca9df7c4/interpreter.ino


https://arduino-esp8266.readthedocs.io/en/latest/index.html


-------------------------------------------------------------
Command List:
-------------------------------------------------------------
Command format:
    #[Devicename].[Command]:<arg1>,<arg2>,<...>


Available cammands listed by typing 
    #help

-------------------------------------------------------------
Ports:
-------------------------------------------------------------
Client:
HTTP Port:8010
UDP Listen Port: 5513

Server:
HTTP Port:8010
UDP Broadcast Listen Port:5512
UDP Server Local cmd Listen Port: 5514
UDP Server Ack Port: 5515


-------------------------------------------------------------
Remote Operation:
-------------------------------------------------------------

On Boot:
- Init Servo's to 90°
- Look for SSID in EEprom for 30sec
- If SSID doesn't exist
    Start WIFI in access point mode
- If SSID exists
    Bradcast message every 10 seconds until server is found
- On Server response store server ip and go into listen mode (Stop broadcasting unless server is lost for > 1 minute)


Interfaces:
    Serial Link
    UDP client
    Http Server

-------------------------------------------------------------
Local UDP Server Operation:
-------------------------------------------------------------
- Listen for broadcasts on broadcast port
    On Client ident, acknowledge client add client to clinet list

- Listen for UDP on localhost, command port
    On commands, if client in list, add command to client's queue

- Send commands to client from client queue
    Retry every second until ACK
    Ping client every 10sec and get update
    If Client lost > 30sec  fire alert.

- Host HTTP server on localhost
    - Lists attached clients
    - allows remapping of client names and commands, stored in local ini file
    - running log of commands sentacked
