void setup_mcp() { // FIX THIS SO IT ONLY INITIALIZES ACTIVE DEVICES
 
  Serial.print ("Activating MCPs"); 
  for (int i = 0; i<8; i++) {
    if (mcpactivebuff[i] == 1) {            // DO THIS IF CHIP IS ACTIVE
    Serial.print (MCP_CHIPNAME[i]);
    Serial.println (" is ACTIVATED");
    mcp[i].begin(i);
    mcp_pin_assign(i);
    }
   }
}




void mcp_pin_assign(int chipnum) {  //fix this to assign INPUT or OUTPUT (**** make sure and assign INPUT or OUTPUT for all new class types ***)
    int i;
    char activepin;
    String pin_io = mcpdoc[chipnum]["IO"].as<String>();
  // "Binary", "Door", "Window", "Switch", "Relay", "iBinary", "Relay3", "INACTIVE"  
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
        mcp[chipnum].digitalWrite (i, LOW);  // set all relays to low on restart
      }    
      if (String(activepin) == "4") {            // RELAY IS OUTPUT
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
        mcp[chipnum].digitalWrite (i, LOW);  // set all relays to low on restart
      }    
      if (String(activepin) == "5") {            // iBinary
        mcp[chipnum].pinMode(i, INPUT); // set pin as input
        mcp[chipnum].pullUp(i, HIGH);   // pull high as default
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
      }
      if (String(activepin) == "6") {            // Timed 3 second relay
        mcp[chipnum].pinMode(i, OUTPUT);  // Might need to assign a default value for the output
        mcp[chipnum].digitalWrite (i, LOW);  // set all relays to low on restart
      }   
      if (String(activepin) == "7") {            // INPUT THAT DOES NOT auto discover or publish
          mcp[chipnum].pinMode(i, INPUT); // set pin as input
          mcp[chipnum].pullUp(i, HIGH);   // pull high as default
          mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
    //    mcp[chipnum].pinMode(i, INPUT); // set pin as input
    //    mcp[chipnum].pullUp(i, HIGH);   // pull high as default
    //    mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
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
  String pin_io = mcpdoc[mcpchip]["IO"].as<String>();
// COMPARE IF STATE CHANGED AND UPDATE BUFFER
  pinval = mcp[mcpchip].digitalRead(pinnum);  // read the pin 
  
  if (freshboot && pin_io.charAt(pinnum) != '7') {PUB_entity (mcpchip,pinnum,pinval);}; // PUBLISH THE CURRENT STATE ON FIRST BOOT
  
  if (pinval != mcpbuff[mcpchip][pinnum]) {   // compare read state to buffer state and if changed do the following
   // if (pin_io.charAt(pinnum) == '7') {fan_toggle();}; // IF IT'S THE INTERNAL RELAY CONTROL TOGGLE
    
    mcpbuff[mcpchip][pinnum] = pinval;        // put new state in buffer
//    DLINE1 = "LISTEN";
//    DLINE1 = DLINE1+MCP_CHIPNAME[mcpchip];  // TAKE OUT THIS LINE ONCE CODE IS CONFIRMED WORKING
    DLINE2 = mcpdoc[mcpchip][String(pinnum)].as<String>();  // name of port changed
    String classstring = mcpdoc[mcpchip]["IO"].as<String>();
    ICONLINE = classstring.charAt(pinnum);
       
 //   DLINE3 = "CHANG TO ";
 //   DLINE3 = DLINE3 + pinval;
    if (pin_io.charAt(pinnum) == '7') {PUB_ann_only (mcpchip,pinnum,pinval);} 
      else {PUB_entity (mcpchip,pinnum,pinval);};
    
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
    if (activepin == '5') {            // DO THIS IF PIN IS iBinary
       PINCompare (mcpchip,i);
    }    
    if (activepin == '6') {            // DO THIS IF PIN IS 3 second relay
     // PINCompare (mcpchip,i);
    }
    if (activepin == '7') {            /// DO THIS IF INACTIVE
       PINCompare (mcpchip,i);
    }  
    if (activepin == '8') {            // not used yet
        PINCompare (mcpchip,i);
    }     
      
  }
  
}


void MCPReadAllActive () {
 
  for (int i = 0; i<8; i++) {
   if (mcpactivebuff[i] == 1) {            // DO THIS IF CHIP IS ACTIVE
    
     MCPCompare (i);
   }
  }
}
