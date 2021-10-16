// ******************** Auto Discovery Functions ********************************//


void AD_all_entities ()
{
  int i;
  String activelist;
  char activechip;
  activelist = conf.getValue("mcpactive");
  Serial.println ("Auto discovery setup all MCPs"); 
  for (i = 0; i<8; i++) {
    activechip = activelist.charAt(i);
    if (activechip == '1') {            // DO THIS IF CHIP IS ACTIVE
    Serial.print (MCP_CHIPNAME[i]);
    Serial.println (" process AD");
    AD_entities(i);  // auto discover all entities on chip = i
    }
   }
}

void AD_entities (int chipnum) {
    int i;
    char activepin;
    String pin_io = mcpdoc[chipnum]["IO"].as<String>();
 //   Serial.print (pin_io);
 //   Serial.print ("AD pins for ");
 //   Serial.println (chipnum); 
    for (i = 0; i<16; i++) {
      activepin = pin_io.charAt(i);  
 
      if (String(activepin) == "0") {            // BINARY IS FOR INPUT
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
        AD_entity (chipnum,i,mcpbuff[chipnum][i],0);  
      
      }
      if (String(activepin) == "1") {            // DOOR IS AN INPUT
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
        AD_entity (chipnum,i,mcpbuff[chipnum][i],1); 
      }    
      if (String(activepin) == "2") {            // WINDOW IS AN INPUT
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
        AD_entity (chipnum,i,mcpbuff[chipnum][i],2); 
      }    
      if (String(activepin) == "3") {            // SWITCH IS AN OUTPUT
       
        Serial.print ("=");
        Serial.println (" IS SWITCH");
      }    
      if (String(activepin) == "4") {            // RELAY IS OUTPUT
 
      }    
      if (String(activepin) == "5") {            // LIGHT IS OUTPUT
  
        Serial.print (i);
        Serial.print ("=");
        Serial.println (" IS LIGHT");
      }    
      if (String(activepin) == "6") {            // LOCK IS OUTPUT
       
        Serial.print (i);
        Serial.print ("=");
        Serial.println (" IS LOCK");
      }    
       if (String(activepin) == "7") {            // INVERTED BINARY IS FOR INPUT
        mcpbuff[chipnum][i] = mcp[chipnum].digitalRead(i);  // put current value into buffer to initialize it
        AD_entity (chipnum,i,mcpbuff[chipnum][i],7);  
      
      }
  }
}


void AD_entity (int mcpchip,int pinnum,int pinval,int pinclass)

// BUILD CHAR ARRAY TO PUBLISH

{
  StaticJsonDocument<256> pubdoc;
  char addbuf[6];
  char entityname[12];
  String entitystring;
  char addresstopic[100];
  char uniquetopic[100];
  char statetopic[100];
  char configtopic[100];
  char pubbuffer[256];
  char uniqueid[20];
  char* pclass;
 

  entitystring = mcpdoc[mcpchip][String(pinnum)].as<String>();
  entitystring.toCharArray(entityname, 12);
  strcpy(configtopic,"homeassistant/");    // start the topic for ha auto discovery
// "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock", "iBinary"  
  switch (pinclass) {    // set the specific details for each entiry class
  case 0:
    pclass = "binary_sensor/";
    pubdoc["pl_on"] = 0;
    pubdoc["pl_off"] = 1;
    break;
  case 1:
    pclass = "binary_sensor/";
    pubdoc["pl_on"] = 0;
    pubdoc["pl_off"] = 1;
    pubdoc["device_class"] = "door";
    break;
  case 2:
    pclass = "binary_sensor/";
    pubdoc["pl_on"] = 0;
    pubdoc["pl_off"] = 1;
    pubdoc["device_class"] = "window";
    break;
  case 3:
    pclass = "switch/";
    pubdoc["pl_on"] = 1;
    pubdoc["pl_off"] = 0;
    break;
  case 4:
    pclass = "relay/";
    break;
  case 5:
    pclass = "light/";
    break;
  case 6:
    pclass = "lock/";
    break;
  case 7:
    pclass = "binary_sensor/";
    pubdoc["pl_on"] = 1;
    pubdoc["pl_off"] = 0;
    break;
  default:
    // statements
    break;
  }
  
  
 
  strcat(configtopic,pclass);      // add the sensor type
  
  strcpy(addresstopic,mainTopic);      // create the mqtt main topic to the address
  
  strcpy(uniquetopic,mainTopic);
  strcat(uniquetopic,"/");
  strcat(uniquetopic,entityname);       // create the unique main topic

  strcpy(statetopic,uniquetopic);
  strcat(statetopic,stateTopic);

  strcat(configtopic,uniquetopic);
  strcat(configtopic,"/config");      // add the config topic
  
  Serial.print ("config state TO ----> ");
  Serial.println (configtopic);

  strcpy(uniqueid,entityname);
  strcat(uniqueid,UNIQUE_ADD_ON);

 
  
  pubdoc["name"] = entitystring;
//  pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();
//  pubdoc["pin"] = pinnum;
//  pubdoc["state"] = pinval;
 
  pubdoc["unique_id"] = uniqueid;
//  pubdoc["device_class"] = "motion";
//  pubdoc["force_update"] = "TRUE";
//  pubdoc["platform"] = "mqtt";
  pubdoc["state_topic"] = statetopic;
  pubdoc["value_template"] = "{{value_json.state}}";
//  pubdoc["ret"] = "TRUE";
  
 
  serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
//  Serial.print (pubbuffer); Serial.print (" = ");
//  Serial.println (configtopic);
 // delay(2000);
 // client.publish("homeassistant/binary_sensor/testunit/config/", pubbuffer);
  client.publish(configtopic, pubbuffer);// THIS IS WHERE TO PUBLISH THE SENSOR DATA
//  delay (500); 
}
