#define MAX_ARGS 4

void printCommandList()
{
  Serial.println(F(
            "#help --  This menu\r\n"
            "#SetSSID:<SSID>\r\n"
            "#SetPass:<WifiPassword>\r\n"
            "#SetName:<DeviceName>\r\n"
            "#SetServo:<Servo>,<Position>,<step size>,<stepdly(ms)>\r\n"
            //"#SetServer:<ServerIP>,<ServerPort>\r\n"
            ));
}



void processCommand(char * cmdBuffer)
{
    char * cmd, arglist;
    char * args[MAX_ARGS];
    char * reply = &ReplyBuffer[0];
    strcpy(reply, PSTR("CMDFAIL"));
    
    if( *cmdBuffer == '#') 
    {
      strsep(&cmdBuffer,"#");
    }
    else
    {
      return;
    }
    cmd = strsep(&cmdBuffer,":");
    if(cmd == NULL)
    {
      return;
    }

    //If argument is a string
    if (strcmp_P(cmd, PSTR("SetSSID")) == 0) {
      strcpy(reply, PSTR("OK:SSID:"));
      strcpy(&reply[8],cmdBuffer);
    } else if (strcmp_P(cmd, PSTR("SetPass")) == 0) {
      strcpy(reply, PSTR("OK:Pass:"));
      strcpy(&reply[8],cmdBuffer);
    } else if (strcmp_P(cmd, PSTR("SetName")) == 0) {
      strcpy(reply, PSTR("OK:Name:"));
      strcpy(&reply[8],cmdBuffer);
    } else
    // If argument is a list of arguments
    {
      for(int i = 0; i < MAX_ARGS ; i ++)
      {
        args[i] = strsep(&cmdBuffer,":, ;");   
      }
      if (strcmp_P(cmd, PSTR("help")) == 0) {
        printCommandList();
      } else if (strcmp_P(cmd, PSTR("SetServo")) == 0) {
        if(args[3] != NULL)
        {
          int sPin = atoi(args[0]);
          int Position = atoi(args[1]);
          int Step = atoi(args[2]);
          int Delay = atoi(args[3]);
          servoArray[sPin].write(Position);
        }
      } else if (strcmp_P(cmd, PSTR("SetServer")) == 0) {
      } else {
        Serial.print(F("Error: Unknown command: "));
        Serial.println(cmd);
      }
    }

    Serial.println(reply);
}
