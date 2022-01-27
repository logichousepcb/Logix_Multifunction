void setup_onboard_io () {
 pinMode(RELAY_PIN, OUTPUT);  // Might need to assign a default value for the output
 digitalWrite (RELAY_PIN, LOW);  // set all relays to low on restart 
 pinMode(BTN1_PIN, INPUT);
 pinMode(BTN2_PIN, INPUT);
 pinMode(BTN3_PIN, INPUT);
 pinMode (LED_PIN, OUTPUT); // Backlight LED 
 digitalWrite (LED_PIN, HIGH);  // TURN ON BACKLIGHT AT START
}

void onboard_io_compare () {
  int inval;
  char buttontopic[100];
  StaticJsonDocument<256> pubdoc;
  inval = digitalRead (BTN1_PIN);
  if (inval != obiobuff[1]) {
      DLINE2 = "BUTT1-";
      DLINE2 = DLINE2 + inval;
      ICONLINE = '0';
      obiobuff[1] = inval;
      strcpy(buttontopic,mainTopic);
      strcat(buttontopic,"/"); 
      strcat(buttontopic,conf.getValue("button-1")); 
      strcat(buttontopic,"/stat");
      pubdoc["entity"] = conf.getValue("button-1");
      pubdoc["state"] = inval;
      char pubbuffer[256];
      serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
 //     client.publish(findmetopic, pubbuffer); // this will puiblish to a text sensor
      client.publish(buttontopic, pubbuffer, true);   
      pubdoc.garbageCollect();
      };
  inval = digitalRead (BTN2_PIN);
  if (inval != obiobuff[2]) {
      DLINE2 = "BUTT2-";
      DLINE2 = DLINE2 + inval;
      ICONLINE = '0';
      obiobuff[2] = inval;
      strcpy(buttontopic,mainTopic);
      strcat(buttontopic,"/"); 
      strcat(buttontopic,conf.getValue("button-2")); 
      strcat(buttontopic,"/stat");
      pubdoc["entity"] = conf.getValue("button-2");
      pubdoc["state"] = inval;
      char pubbuffer[256];
      serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
 //     client.publish(findmetopic, pubbuffer); // this will puiblish to a text sensor
      client.publish(buttontopic, pubbuffer, true);   
      pubdoc.garbageCollect();
      };
  inval = digitalRead (BTN3_PIN);
  if (inval != obiobuff[3]) {
      DLINE2 = "BUTT3-";
      DLINE2 = DLINE2 + inval;
      ICONLINE = '0';
      obiobuff[3] = inval;
      strcpy(buttontopic,mainTopic);
      strcat(buttontopic,"/"); 
      strcat(buttontopic,conf.getValue("button-3")); 
      strcat(buttontopic,"/stat");
      pubdoc["entity"] = conf.getValue("button-3");
      pubdoc["state"] = inval;
      char pubbuffer[256];
      serializeJson(pubdoc, pubbuffer); // Serialize json for publihing
 //     client.publish(findmetopic, pubbuffer); // this will puiblish to a text sensor
      client.publish(buttontopic, pubbuffer, true);   
      pubdoc.garbageCollect();
      };
  

}


void fan_control (int state) {
 // digitalWrite (RELAY_PIN, state);
  obiobuff[0] = state;
 // if (state == 1) {DLINE2 = "FAN ON";} else {DLINE2 = "FAN OFF";};  
}

void fan_toggle () {
 if (breturn) {
  if (obiobuff[0] == 1) {obiobuff[0] = 0;breturn = false;} else {obiobuff[0] = 1;breturn = false;};
 } else (breturn = true);
 digitalWrite (RELAY_PIN, obiobuff[0]);
 
}

void obrelay_control (int tstat) {
  digitalWrite (RELAY_PIN, tstat);
  obiobuff[0] = tstat;
 
}
// SETUP WS2812 LED
/*
void setup_pixel () {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(10);
  pixels.setPixelColor(0, pixels.Color(200, 100, 255));
  pixels.show();
} */
