
/*
void callback(char* topic, byte* payload, unsigned int length) {
  StaticJsonDocument<256> doc;
  String name = "";
  String entity = "";
  String stateof = "";
  char* wrd = strstr(topic,"/");
  char topbuff[20];
  
  
  deserializeJson(doc, payload, length);
  char namebuffer[256];
  Serial.print ("RECEIVED COMMAND FROM --->");Serial.println(topic);
//   Serial.print ("PAYLOAD OF --->");Serial.println(payload);
  
  strcpy(topbuff,wrd);
  byte len= strlen(topbuff);
  topbuff [len - 5] = '\0';
  for( int i = 1 ; i < 50 ; ++i ){
    topbuff[ i - 1 ] = topbuff[ i ];
  } 


  Serial.print ("MODIFIED COMMAND --->");Serial.print(topbuff);Serial.print ("<===>");
  
  // Serial.println (namebuffer);
  Serial.println (atoi(namebuffer));

  serializeJson(doc, namebuffer);
  
//  Serial.print (topbuff);Serial.print (" = "); Serial.println (namebuffer); 
  if (atoi(namebuffer) == 99) {ESP.restart();};    //if a command of 99 is sent to any switch topic restart esp
  control_check_activate (topbuff,atoi(namebuffer));
  
  
//  control_check_activate (doc["entity"].as<String>(),doc["state"].as<int>());
// check if name is a valid input


// act on valid input
  
}
*/
// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.
  char topbuff[20];
  char* wrd = strstr(topic,"/");
  StaticJsonDocument<256> doc;
  // Allocate the correct amount of memory for the payload copy
  Serial.println ("--------------------START MSG PROCESSING-----------------");
  deserializeJson(doc, payload, length);
  char namebuffer[256];
  Serial.print ("RECEIVED COMMAND FROM --->");Serial.println(topic);
 // byte* p = (byte*)malloc(length);
  // Copy the payload to the new buffer
 // memcpy(p,payload,length);
 
  strcpy(topbuff,wrd);
  byte len= strlen(topbuff);
  topbuff [len - 5] = '\0';
  for( int i = 1 ; i < len ; ++i ){
    topbuff[ i - 1 ] = topbuff[ i ];
  } 

  serializeJson(doc, namebuffer);
  if (atoi(namebuffer) == 99) {ESP.restart();};    //if a command of 99 is sent to any switch topic restart esp
  Serial.print ("RECEIVED CMD FOR ENTITY --->");Serial.print(topbuff);Serial.print("<--->");Serial.print(atoi(namebuffer));Serial.println("<---");
  
  control_check_activate (topbuff,atoi(namebuffer));
  Serial.println ("----------------------END MSG PROCESSING-----------------");
}


boolean reconnect() {
   // char subtopic[100];
 // if (client.connect(conf.getValue("mqtt-address"), conf.getValue("mqtt-username"), conf.getValue("mqtt-pw"), willTopic, willQoS, willRetain, willMessage)) {
    if (client.connect(conf.getValue("mqtt-topic"), conf.getValue("mqtt-username"), conf.getValue("mqtt-pw"), willTopic, willQoS, willRetain, willMessage)) {
    // Once connected, publish an announcement...
    client.publish(willTopic,"online");
    // ... and resubscribe
    MQTT_connected = true;
 // SUBSCRIBE TO ALL THE OUTPUTS
    
    char subtopic[100];
    strcpy(subtopic,mainTopic);
  //  strcat (subtopic,"/RESTART");
    strcat(subtopic,cmndTopic);
    AD_all_entities ();
 //   if (atoi(conf.getValue("mqtt-ad"))== 1) {AD_all_entities ();};
   // client.subscribe(subtopic);   // subscribe to the cmnd topic mqtt-topic/cmnd
  //  client.subscribe (subtopic);     // subscribe to the cmnd topic mqtt-topic/RESTART/cmnd
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
  char findmetopic[100];
  strcpy (addresstopic,mainTopic);      // add the mqtt main topic to the address

  if (mcpchip==9) {pubdoc["entity"] = conf.getValue("relay-1");entitystring = conf.getValue("relay-1");}
    else {pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();entitystring = mcpdoc[mcpchip][String(pinnum)].as<String>();};

  entitystring.toCharArray(entityname, 12);  
//  if (mcpchip==9) {entitystring = conf.getValue("relay-1");}
//    else {entitystring = mcpdoc[mcpchip][String(pinnum)].as<String>();};
//  entitystring.toCharArray(entityname, 12);

 // pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();
/*
  if (mcpchip==9) {
    // pubdoc["entity"] = conf.getValue("relay-1");}
    pubdoc["entity"] = "OBRelay";}
    else {pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();}; 
*/


  pubdoc["state"] = pinval;
  
  strcat(addresstopic,"/"); 
  strcpy (findmetopic,addresstopic);
  strcat (findmetopic,"stat");
  strcat(addresstopic,entityname);
 // strcat(addresstopic,pubdoc["entity"]);
  strcat (addresstopic,stateTopic);
  Serial.print ("publishing state to ----> ");
  Serial.println (addresstopic);
  Serial.print ("publishing FindMe to ----> ");
  Serial.println (findmetopic);
  
  char pubbuffer[256];
  serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
  Serial.println (pubbuffer);
  client.publish(addresstopic, pubbuffer,true);// THIS IS WHERE TO PUBLISH THE SENSOR DATA
  client.publish(findmetopic, pubbuffer,true); // this will puiblish to a text sensor
 
}  

void PUB_ann_only (int mcpchip,int pinnum,int pinval)

{
  StaticJsonDocument<256> pubdoc;
  char addbuf[6];
  char entityname[12];
  String entitystring;
  char addresstopic[100];
  char findmetopic[100];
  strcpy (addresstopic,mainTopic);      // add the mqtt main topic to the address
  entitystring = mcpdoc[mcpchip][String(pinnum)].as<String>();
  entitystring.toCharArray(entityname, 12);
  strcat(addresstopic,"/"); 
  strcpy (findmetopic,addresstopic);
  strcat (findmetopic,"stat");
  strcat(addresstopic,entityname);
  strcat (addresstopic,stateTopic);
  Serial.print ("publishing state to ----> ");
  Serial.println (addresstopic);
  pubdoc["entity"] = mcpdoc[mcpchip][String(pinnum)].as<String>();
  pubdoc["state"] = pinval;
  
  char pubbuffer[256];
  serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
//  client.publish(addresstopic, pubbuffer);// THIS IS WHERE TO PUBLISH THE SENSOR DATA
  client.publish(findmetopic, pubbuffer); // this will puiblish to a text sensor
 
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
