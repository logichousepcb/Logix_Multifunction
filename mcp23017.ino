void setup_mcp() { // FIX THIS SO IT ONLY INITIALIZES ACTIVE DEVICES
  int i;
  String activelist;
  char activechip;
  activelist = conf.getValue("mcpactive");
  Serial.print ("Activating MCPs"); 
  for (i = 0; i<8; i++) {
    activechip = activelist.charAt(i);
    if (activechip == '1') {            // DO THIS IF CHIP IS ACTIVE
    Serial.print (MCP_CHIPNAME[i]);
    Serial.println (" is ACTIVATED");
    mcp[i].begin(i);
    mcp_pin_assign(i);
    }
   }
}




void mcp_pin_assign(int chipnum) {  //fix this to assign INPUT or OUTPUT
    int i;
    char activepin;
    String pin_io = mcpdoc[chipnum]["IO"].as<String>();
  
    for (i = 0; i<16; i++) {
      activepin = pin_io.charAt(i);  
      if (String(activepin) == "0") {            // BINARY IS FOR INPUT
        mcp[chipnum].pinMode(i, INPUT); // set pin as input
        mcp[chipnum].pullUp(i, HIGH);   // pull high as default
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
      }
      if (String(activepin) == "1") {            // DOOR IS AN INPUT
        mcp[chipnum].pinMode(i, INPUT); // set pin as input
        mcp[chipnum].pullUp(i, HIGH);   // pull high as default
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
      }    
      if (String(activepin) == "2") {            // WINDOW IS AN INPUT
        mcp[chipnum].pinMode(i, INPUT); // set pin as input
        mcp[chipnum].pullUp(i, HIGH);   // pull high as default
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
      }    
      if (String(activepin) == "3") {            // SWITCH IS AN OUTPUT
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
        Serial.print ("=");
        Serial.println (" IS SWITCH");
      }    
      if (String(activepin) == "4") {            // RELAY IS OUTPUT
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
//        Serial.print ("Trigger = ");
//        Serial.print (i);
//        Serial.print ("-");
//        Serial.println (chipnum);
//        Serial.print ("Relay - ");Serial.print (i);Serial.println (" - ON");
//          mcp[chipnum].digitalWrite (i, HIGH);
//        delay (2000);
        mcp[chipnum].digitalWrite (i, LOW);  // set all relays to low on restart
//        Serial.print ("Relay - ");Serial.print (i);Serial.println (" - OFF");
 //       Serial.print (i);
 //       Serial.print ("=");
 //       Serial.println (" IS RELAY");
      }    
      if (String(activepin) == "5") {            // LIGHT IS OUTPUT
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
      }    
      if (String(activepin) == "6") {            // LOCK IS OUTPUT
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
      }    
      if (String(activepin) == "7") {            // INVERTED BINARY IS FOR INPUT
        mcp[chipnum].pinMode(i, INPUT); // set pin as input
        mcp[chipnum].pullUp(i, HIGH);   // pull high as default
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
      }
  }
} 

/***************** CURRENTLY NOT USED BUT CAM BE USED TO CONVERT IO VALUES ****************/
/*
int PINcheck (int chipnum, int pinnum) {
  String pinstates = mcpdoc[chipnum]["state"].as<String>();
  char pinvalue;
  pinvalue = pinstates.charAt(pinnum);
  if (pinvalue == '1') {
    return 1;
  }
  else {
    return 0;
  }
}
*/
void PINCompare(int mcpchip, int pinnum ) {
  int pinval;

// COMPARE IF STATE CHANGED AND UPDATE BUFFER
  pinval = mcp[mcpchip].digitalRead(pinnum);  // read the pin 
  if (pinval != mcpbuff[mcpchip][pinnum]) {   // compare read state to buffer state and if changed do the following
    mcpbuff[mcpchip][pinnum] = pinval;        // put new state in buffer
//    DLINE1 = "LISTEN";
//    DLINE1 = DLINE1+MCP_CHIPNAME[mcpchip];  // TAKE OUT THIS LINE ONCE CODE IS CONFIRMED WORKING
    DLINE2 = mcpdoc[mcpchip][String(pinnum)].as<String>();  // name of port changed
   
 //   DLINE3 = "CHANG TO ";
 //   DLINE3 = DLINE3 + pinval;
    PUB_entity (mcpchip,pinnum,pinval);
  }
}

void MCPCompare (int mcpchip) {    // This routine checks all pins for input/output from Json definition
  int i;
  String pin_name;
  char activepin;
  String pin_io = mcpdoc[mcpchip]["IO"].as<String>();
  // "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock", "iBinary"  
  for (i = 0; i<16; i++) {
    activepin = pin_io.charAt(i);
    if (activepin == '0') {            // DO THIS IF PIN IS Binary
      PINCompare (mcpchip,i);
    }
    if (activepin == '1') {            // DO THIS IF PIN IS Door
       PINCompare (mcpchip,i);
    }    
    if (activepin == '2') {            // DO THIS IF PIN IS Window
      PINCompare (mcpchip,i);
    }
    if (activepin == '3') {            // DO THIS IF PIN IS Switch
     //  PINCompare (mcpchip,i);
    }    
    if (activepin == '4') {            // DO THIS IF PIN IS Relay
     // PINCompare (mcpchip,i);
    }
    if (activepin == '5') {            // DO THIS IF PIN IS Light
     //  PINCompare (mcpchip,i);
    }    
    if (activepin == '6') {            // DO THIS IF PIN IS Lock
     // PINCompare (mcpchip,i);
    }
    if (activepin == '7') {            // DO THIS IF PIN IS Binary INVERTED
       PINCompare (mcpchip,i);
    }    
      
  }
  
}


void MCPReadAllActive () {
  int i;
  String activelist;
  char activechip;

  activelist = conf.getValue("mcpactive");
  for (i = 0; i<8; i++) {
    activechip = activelist.charAt(i);
    if (activechip == '1') {            // DO THIS IF CHIP IS ACTIVE
 //     Serial.print ("CHIP ACTIVE AT---> ");
 //     Serial.println (MCP_CHIPNAME[i]);
    MCPCompare (i);
    }
    if (activechip == '0') {            // DO THIS IF CHIP IS NOT ACTIVE
 //     Serial.print ("CHIP NOT ACTIVE AT---> ");
 //     Serial.println (MCP_CHIPNAME[i]);
    }
  }
}
