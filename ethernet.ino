void handleEvent(WiFiEvent_t event) {
  switch (event) {
    case SYSTEM_EVENT_ETH_START:
      //set Ethernet hostname
      ETH.setHostname("esp32mx-e");
      Serial.println("ETH Started");
      Serial.print("ETH MAC: ");
      Serial.println(ETH.macAddress());
      break;
    case SYSTEM_EVENT_ETH_CONNECTED:
      Serial.println("ETH Connected");
      
      break;
    case SYSTEM_EVENT_ETH_GOT_IP:
      Serial.print("ETH IPv4: ");
      Serial.println(ETH.localIP());
     
      if (ETH.fullDuplex()) {
        Serial.print("FULL_DUPLEX, ");
      }
      Serial.print(ETH.linkSpeed());
      Serial.println("Mbps");
      eth_connected = true;
      break;
    case SYSTEM_EVENT_ETH_DISCONNECTED:
      Serial.println("ETH Disconnected");
      eth_connected = false;
      break;
    case SYSTEM_EVENT_ETH_STOP:
      Serial.println("ETH Stopped");
      eth_connected = false;
      break;
    default:
      break;
  }
}


boolean initEth() {
    boolean connected = false;
   // WiFi.mode(WIFI_STA);
    WiFi.onEvent(handleEvent);
    ETH.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_CLK_MODE);
 //   Serial.print("Verbindung zu ");
 //   Serial.print(conf.values[0]);
 //   Serial.println(" herstellen");
   //**** if there are no values do this ***//
    if (conf.values[0] != "") {
 //     WiFi.begin(conf.values[0].c_str(),conf.values[1].c_str());
      uint8_t cnt = 0;
 //     while ((WiFi.status() != WL_CONNECTED) && (cnt<20)){
 //       delay(500);
 //       Serial.print(".");
 //       cnt++;
 //     }
/*      if (WiFi.status() == WL_CONNECTED) {
        Serial.print("IP-Adresse = ");
        Serial.println(WiFi.localIP());
        connected = true;
      } */
    }
//******  if not connected do this - will be an icon on display **********************//

    if (!connected) {
      //    WiFi.mode(WIFI_AP);
      //    WiFi.softAP(conf.getApName(),"",1);  
    }
    return connected; 
}
/*
void handleRoot() {
  conf.handleFormRequest(&server);
  if (server.hasArg("SAVE")) {
    uint8_t cnt = conf.getCount();
 //   Serial.println("*********** Configuration ************");
    for (uint8_t i = 0; i<cnt; i++) {
//      Serial.print(conf.getName(i));
//      Serial.print(" = ");
//      Serial.println(conf.values[i]);
    }
    if (conf.getBool("switch")) Serial.printf("%s %s %i %5.2f \n",
                                conf.getValue("ssid"),
                                conf.getString("continent").c_str(), 
                                conf.getInt("amount"), 
                                conf.getFloat("float"));
  }
} */
