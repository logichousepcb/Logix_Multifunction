
void mcp_output_pin (int chipnum,int pinnum,int lowhigh) {
        Serial.print ("Trigger = ");
        Serial.print (lowhigh);
        Serial.print ("-");
        Serial.print ("Relay - ");
        mcp[chipnum].digitalWrite (pinnum, lowhigh);
        read_ina260();
      
    //    if (lowhigh == 1) {mcp[chipnum].digitalWrite (pinnum, HIGH);Serial.println (" - ON");};
    //    if (lowhigh == 0) {mcp[chipnum].digitalWrite (pinnum, LOW);Serial.println (" - OFF");};
   //     mcp[chipnum].digitalWrite (i, LOW);
   //     Serial.print ("Relay - ");Serial.print (i);Serial.println (" - OFF");
   //    Serial.print (i);
   //    Serial.print ("=");
   //    Serial.println (" IS RELAY");
  
}

void control_check_activate (String entity_received,int lowhigh) {
  int i;
  int pincount;
  String pinlist;
  char activepin;
  
  if (entity_received == conf.getValue("relay-1")) {
    //fan_toggle();
    digitalWrite (RELAY_PIN, lowhigh);
    PUB_entity (9,1,lowhigh);  
    DLINE2 = entity_received;
    ICONLINE = '3';
  };
    
  for (i = 0; i<8; i++) {
    String pin_io = mcpdoc[i]["IO"].as<String>();
    if (mcpactivebuff[i] == 1) {            // DO THIS IF CHIP IS ACTIVE
 //      check if the name is a valid device against only valid input (switch,relay,light)
 //"Binary", "Door", "Window", "Switch", "Relay", "iBinary", "Relay3", "INACTIVE"
     for (pincount = 0; pincount<16; pincount++){ 
      activepin = pin_io.charAt(pincount);
      
      switch (activepin){     // set the specific details for each entiry class
      case '3':                           // SWITCH
        if (mcpdoc[i][PIN_BINARY[pincount-1]].as<String>()==entity_received) {
        PUB_entity (i,pincount,lowhigh);  // publish state change after command
        mcp_output_pin (i,pincount,lowhigh);
        DLINE2 = entity_received;
        ICONLINE = '3';
        } else {
          // Serial.println ("FALSE");
        };
      break;
      case '4':                           // RELAY
        if (mcpdoc[i][PIN_BINARY[pincount-1]].as<String>()==entity_received) {
        PUB_entity (i,pincount,lowhigh);  // publish state change after command
        mcp_output_pin (i,pincount,lowhigh);
        DLINE2 = entity_received;
        ICONLINE = '4';
        } else {
          // Serial.println ("FALSE");
        };
      break;
      case '6':                              // TIMED RELAY
        if (mcpdoc[i][PIN_BINARY[pincount-1]].as<String>()==entity_received) {
        PUB_entity (i,pincount,lowhigh);  // publish state change after command
        mcp_output_pin (i,pincount,lowhigh);
        delay (3000);        // THIS IS WHERE THE GARAGE DELAY WILL GO
        mcp_output_pin (i,pincount,0);
        PUB_entity (i,pincount,0); 
        DLINE2 = entity_received;
        ICONLINE = '6';
        } else {
          // Serial.println ("FALSE");
        };
      break;
      default:
           // statements
      break;
      }
     }
    }
  }
}
