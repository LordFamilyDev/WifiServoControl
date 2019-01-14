# WifiServoControl_Server
PC server
    - Manages Wifi servo clients
    - Accepts local host UDP messaging and frowards commands to attached servo clients
    - Logs commands and retries lost commands to servo clients

-------------------------------------------------------------
Local UDP Server Operation:
-------------------------------------------------------------
- Listen for broadcasts on broadcast port
    On Client ident, acknowledge client add client to client list

- Listen for UDP on localhost command port
    On commands, if client in list, add command to client's queue
    Intended to receive commands from Spikemark UDP messenger onlocal host:
            https://creativeconners.com/products/software/

- Continuously pings clients at 10 sec rate to verify status
    If Client lost > 30sec alert operator & log

- Send commands to client from client queue
    Retry every second until ACK

- Host HTTP server on localhost
    - Lists attached clients
    - Allows changing config options
    - Allows sending commands to clients

- Configurable via Http, settigns stored in local config file

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
Command List:
-------------------------------------------------------------
Command format:
    #[Devicename].[Command]:<arg1>,<arg2>,<...>

*Note: Server Will strip off [Devicename] on forward