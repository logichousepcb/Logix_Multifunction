void setup_onboard_io () {
 pinMode(RELAY_PIN, OUTPUT);  // Might need to assign a default value for the output
 digitalWrite (RELAY_PIN, LOW);  // set all relays to low on restart 
 pinMode(BTN1_PIN, INPUT);
 pinMode(BTN2_PIN, INPUT);
 pinMode(BTN3_PIN, INPUT);
}

void onboard_io_compare () {
  int inval;
  inval = digitalRead (BTN1_PIN);
  if (inval != obiobuff[1]) {DLINE2 = "OB BUTT1";obiobuff[1] = inval;};
  inval = digitalRead (BTN2_PIN);
  if (inval != obiobuff[2]) {DLINE2 = "OB BUTT2";obiobuff[2] = inval;fan_toggle();};
  inval = digitalRead (BTN3_PIN);
  if (inval != obiobuff[3]) {DLINE2 = "OB BUTT3";obiobuff[3] = inval;}; 
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

// SETUP WS2812 LED
void setup_pixel () {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(10);
  pixels.setPixelColor(0, pixels.Color(200, 100, 255));
  pixels.show();
}
