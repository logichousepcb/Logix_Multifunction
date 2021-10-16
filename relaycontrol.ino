
void mcp_output_pin (int chipnum,int pinnum,int lowhigh) {
        Serial.print ("Trigger = ");
 //       Serial.print (chipnum);
 //       Serial.print ("-");
 //       Serial.print (pinnum);
 //       Serial.print ("-");
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
  String activelist;
  char activechip;
  String pinlist;
  char activepin;
  
  activelist = conf.getValue("mcpactive");
  for (i = 0; i<8; i++) {
    activechip = activelist.charAt(i);
    String pin_io = mcpdoc[i]["IO"].as<String>();
    if (activechip == '1') {            // DO THIS IF CHIP IS ACTIVE
 //      check if the name is a valid device against only valid input (switch,relay,light)
 // "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock", "iBinary"  
     for (pincount = 0; pincount<16; pincount++){ 
//      pinlist = mcp[i]["IO"].as<String>();
//      pinlist = mcp.getValue[i]["IO"];
      activepin = pin_io.charAt(pincount);
      
      switch (activepin){     // set the specific details for each entiry class
      case '3':
        Serial.print (pincount);
        Serial.println (mcpdoc[i][PIN_BINARY[pincount]].as<String>());
        
      break;
      case '4':
        Serial.print (pincount);
        Serial.print (mcpdoc[i][PIN_BINARY[pincount-1]].as<String>());
        Serial.print ("<--comapre to-->");
        Serial.print (entity_received);
        Serial.print ("--is-->");
        if (mcpdoc[i][PIN_BINARY[pincount-1]].as<String>()==entity_received) {
          Serial.println ("TRUE");
          mcp_output_pin (i,pincount,lowhigh);
        //  delay (1500);
        //  mcp_output_pin (i,pincount,0);
        //  break;
        } else {Serial.println ("FALSE");};
      break;
      case '5':
      //   Serial.println (mcpdoc[i][activepin].as<String>());
      break;
      case '6':
      //   Serial.println (mcpdoc[i][activepin].as<String>());
      break;
      default:
           // statements
      break;
      }
     }
    }
  }
}
