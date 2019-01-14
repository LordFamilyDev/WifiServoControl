void processCommand(char * cmdBuffer)
{
    if(strsep(&cmdBuffer,"#") == NULL)
    {
        Serial.print(F("Error: Unknown command: "));
        Serial.println(cmdBuffer);
        return;
    }
    char * command = strsep(&cmdBuffer,":");
    if(command == NULL)
    {
      Serial.print(F("Error: Unknown command: "));
      Serial.println(cmdBuffer);
      Serial.print(F("Type #help for a list of cammands"));
      return;
    }
    char * reply = &ReplyBuffer[0];

    if (strcmp_P(command, PSTR("help")) == 0) {
        Serial.println(F(
            "#help --  This menu\r\n"
            "#SetSSID:<SSID>\r\n"
            "#SetPass:<WifiPassword>\r\n"
            "#SetName:<DeviceName>\r\n"
            "#SetServo:<Servo>,<Position>,<step size>,<stepdly(ms)>\r\n"
            "#SetOutput:<Output>,<1(on)||0(off)>\r\n"
            //"#SetServer:<ServerIP>,<ServerPort>\r\n"
            ));
    } else if (strcmp_P(command, PSTR("SetSSID")) == 0) {
    } else if (strcmp_P(command, PSTR("SetPass")) == 0) {
    } else if (strcmp_P(command, PSTR("SetName")) == 0) {
    } else if (strcmp_P(command, PSTR("SetServo")) == 0) {
            int sPin = atoi(strsep(&cmdBuffer, ","));
            int Position = atoi(strsep(&cmdBuffer, ","));
            servoArray[sPin].write(Position);
    } else if (strcmp_P(command, PSTR("SetOutput")) == 0) {
    } else if (strcmp_P(command, PSTR("SetServer")) == 0) {
    } else {
        Serial.print(F("Error: Unknown command: "));
        Serial.println(command);
    }

//        
//        analogWrite(pin, value);
}
