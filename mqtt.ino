void callback(char* reedTopic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(reedTopic);
 Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
 }
  Serial.println();
  payload[length] = '\0';
  String message = (char*)payload;

  if(message == "RESET"){
    Serial.println("Resetting ESP");
    client.publish(reportTopic,"Reset ESP"); 
    ESP.restart();
    while(message != "RESET"){
      break;
    }
  } 
  if(message == "RESCAN"){
    Serial.println("Rescanning MCP Bus");
    client.publish(reportTopic,"Rescanning MCP Bus"); 
  //  mcp_renew();
    while(message != "RESCAN"){
      break;
    }
  } 
  if(message == "OFF"){
    client.publish(reportTopic, "Off recieved");
    delay(2000);
    while(message != "OFF"){
      break;
    }
  }
}

void reconnect() 
{
  int retries = 0;
  while (!client.connected()) {
    if(retries < 3)
    {
      Serial.print("Attempting MQTT connection...");
      if (client.connect(conf.getValue("mqtt-address"), conf.getValue("mqtt-username"), conf.getValue("mqtt-pw"), willTopic, willQoS, willRetain, willMessage)) 
      {
        Serial.println("connected");
        MQTT_connected = true;
        delay (5000);
        if(boot == false)
        {
     //     client.publish(conf.getValue("mqtt-topic")"/checkIn","Reconnected"); 
          client.publish(conf.getValue("mqtt-topic"),"Reconnected"); 
          client.publish(reportTopic,"Reconnected"); 
        }
        if(boot == true)
        {
       //  client.publish(conf.getValue("mqtt-topic")"/checkIn","Online");
          client.publish(conf.getValue("mqtt-topic"),"Online");
        }
        // ... and resubscribe
        client.subscribe("/sensorin");
        client.subscribe(reportTopic);
        client.subscribe(reedTopic);
      } 
      else 
      {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        retries++;
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
//    if(retries > 149)  // dont need this, i dont want to restart if client doesnt connect 
//    {
//    ESP.restart();
//    }
  }
}
