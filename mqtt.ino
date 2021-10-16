

void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<256> doc;
  String name = "";
  String entity = "";
  String stateof = "";
  
  deserializeJson(doc, payload, length);
  char namebuffer[256];
  serializeJson(doc, namebuffer);
  Serial.println (namebuffer);
  Serial.print (doc["entity"].as<String>());Serial.print (" = "); Serial.println (doc["state"].as<int>()); 
  control_check_activate (doc["entity"].as<String>(),doc["state"].as<int>());
// check if name is a valid input


// act on valid input
  
}

boolean reconnect() {
    char subtopic[100];
 // if (client.connect(conf.getValue("mqtt-address"), conf.getValue("mqtt-username"), conf.getValue("mqtt-pw"), willTopic, willQoS, willRetain, willMessage)) {
    if (client.connect(conf.getValue("mqtt-topic"), conf.getValue("mqtt-username"), conf.getValue("mqtt-pw"), willTopic, willQoS, willRetain, willMessage)) {
    // Once connected, publish an announcement...
    client.publish(mainTopic,"connected");
    // ... and resubscribe
    MQTT_connected = true;
 // SUBSCRIBE TO ALL THE OUTPUTS
    strcpy(subtopic,mainTopic);
    strcat(subtopic,cmndTopic);
    client.subscribe(subtopic);   // subscribe to the cmnd topic mqtt-topic/cmnd
    
 //   client.subscribe(binarySensor.getConfigTopic());
 //       client.subscribe(reportTopic);

  }
  
  return client.connected();
  
}

// ******************** Publish Function ********************************//

void SUB_entities () {
  
}

// ******************** Publish Function ********************************//

void PUB_entity (int mcpchip,int pinnum,int pinval)

// BUILD CHAR ARRAY TO PUBLISH

{
  StaticJsonDocument<256> pubdoc;
  char addbuf[6];
  char entityname[12];
  String entitystring;
  char addresstopic[100];
  

// make a unique identifier out of clint+chip+port    


  
  strcpy (addresstopic,mainTopic);      // add the mqtt main topic to the address
  
  entitystring = mcpdoc[mcpchip][String(pinnum)].as<String>();
  entitystring.toCharArray(entityname, 12);
  strcat(addresstopic,"/"); 
  strcat(addresstopic,entityname);
  strcat (addresstopic,stateTopic);

  Serial.print ("publishing state to ----> ");
  Serial.println (addresstopic);
  
  
  pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();
//  pubdoc["pin"] = pinnum;
  pubdoc["state"] = pinval;
   
  char pubbuffer[256];
  serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
  client.publish(addresstopic, pubbuffer);// THIS IS WHERE TO PUBLISH THE SENSOR DATA
 
}  


void setupMQTT()
{
  client.setBufferSize(512); // set buffer size for config doc  
 // DLINE2 = conf.getValue("mqtt-address");
 
 // client.setServer(mqtt_server,mqtt_port);
 // Serial.print("MQTT ADDRESS---->");
 // Serial.println(conf.getValue("mqtt-address"));
 // Serial.print("MQTT PORT---->");
 // Serial.println(conf.getValue("mqtt-port"));
  client.setServer(conf.getValue("mqtt-address"),atoi(conf.getValue("mqtt-port")));
  client.setCallback(callback);
 
 // Ethernet.begin(mac, ip);
 // delay(1000);
  lastReconnectAttempt = 0;
}
