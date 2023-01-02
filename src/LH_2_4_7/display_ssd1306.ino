#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
// #define WHITE   0xFFFF
#define GREY     0xD6BA


/*
void setup_display() {
//  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;);
//  }
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
//  display.begin(SH1106_SWITCHCAPVCC, 0x78);
//  delay(1000);
  display.clearDisplay();
  display.display(); 
  showBitmap();
//  display.clearDisplay();
//  display_status();
}
*/

void setup_oled() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display(); 
};




void showBitmap(void) {
  if (oled_connected) { display.clearDisplay();
    display.drawBitmap(0, 0, bitmap, bitmap_height, bitmap_width, WHITE);
    display.display();
  }; 

  if (tft_35_connected) {tft_35.drawRGBBitmap (0,0,splash_tft_128,128,128);
    delay(4000);
    tft_35.fillScreen(ST77XX_BLACK);
  };
  
  if (tft_89_connected) {tft_89.drawRGBBitmap (0,0,splash_tft_240,240,240);
    delay(4000);
    tft_89.fillScreen(ST77XX_BLACK);
  };
}

void showEthconnected() {
  if (oled_connected) {display.drawBitmap(0, 0, bitmapEthOn, 16, 16, WHITE);};
  if (tft_35_connected) {tft_35.drawBitmap(25, 5, bitmapEthOn, 16, 16, GREEN);};
  if (tft_89_connected) {tft_89.drawBitmap(25, 5, bitmapEthOn, 16, 16, GREEN);};
}

void showEthNot() {
  if (tft_35_connected) {tft_35.drawBitmap(25, 5, bitmapEthOn, 16, 16, RED);};
  if (tft_89_connected) {tft_89.drawBitmap(25, 5, bitmapEthOn, 16, 16, RED);};
}

void showWificonnected() {
  if (oled_connected) {display.drawBitmap(0, 0, bitmapWifiOn, 16, 16, WHITE);};
  if (tft_35_connected) {tft_35.drawBitmap(5, 5, bitmapWifiOn, 16, 16, GREEN);};
  if (tft_89_connected) {tft_89.drawBitmap(5, 5, bitmapWifiOn, 16, 16, GREEN);};
}

void showMQTTconnected() {
  if (oled_connected) {display.drawBitmap(112, 0, bitmapMQTTOn, 16, 16, WHITE);};
  if (tft_89_connected) {tft_89.drawBitmap(220, 5, bitmapMQTTOn, 16, 16, GREEN);};
  if (tft_35_connected) {tft_35.drawBitmap(110, 5, bitmapMQTTOn, 16, 16, GREEN);};
}

void showEthoff() {
  if (oled_connected) {display.drawBitmap(0, 0, bitmapEthOff, 16, 16, WHITE);};
  if (tft_35_connected) {tft_35.drawBitmap(25, 5, bitmapEthOff, 16, 16, RED);};
  if (tft_89_connected) {tft_89.drawBitmap(25, 5, bitmapEthOff, 16, 16, RED);};
}

void showMQTToff() {
  if (oled_connected) {display.drawBitmap(112, 0, bitmapMQTTOff, 16, 16, WHITE);};
  if (tft_89_connected) {tft_89.drawBitmap(220, 5, bitmapMQTTOff, 16, 16, RED);};
  if (tft_35_connected) {tft_35.drawBitmap(110, 5, bitmapMQTTOff, 16, 16, RED);};
}
void display_status_tft_89 () {
  // tft_89.setRotation(1);

  tft_89.setCursor(70, 5);
  tft_89.setTextColor(ST77XX_CYAN);
  tft_89.setTextSize(2);
  tft_89.print(" LH ");
  tft_89.println(CURR_VERS);
  tft_89.setCursor(0, 40);

  tft_89.setTextColor(ST77XX_WHITE,BLACK);
  tft_89.setTextSize(2);
  if (XDLINE1 != DLINE1) {tft_89.println(DLINE1);XDLINE1 = DLINE1;};
  tft_89.setTextSize(2);
  tft_89.setTextColor(ST77XX_GREEN,BLACK);
  tft_89.setCursor(0, 60);
  if (XDLINE8 != DLINE8) {
   // tft_89.println("                   ");
    tft_89.setCursor(0, 60);
    tft_89.println(DLINE8);XDLINE8 = DLINE8;};
  tft_89.setCursor(0, 80);
 // if (XDLINE3 != DLINE3) {tft_89.println(DLINE3);XDLINE3 = DLINE3;};
  tft_89.setTextColor(GREEN,BLACK);
  tft_89.setCursor(50, 115);
  if (XDLINE2 != DLINE2) {
    tft_89.setTextSize(3);
    tft_89.println("          ");
    tft_89.setCursor(50, 115);
    tft_89.println(DLINE2);
    XDLINE2 = DLINE2;
    // tft_89.setTextSize(2);
  };
  tft_89.setCursor(0, 140);
  if (XDLINE5 != DLINE5) {tft_89.println(DLINE5);XDLINE5 = DLINE5;};
  tft_89.setCursor(0, 160);
 // if (XDLINE6 != DLINE6) {tft_89.println(DLINE6);XDLINE6 = DLINE6;};
  tft_89.setCursor(0, 180);
  // display.setTextColor(YELLOW, BLACK);
  tft_89.setTextSize(2);
  tft_89.println(DLINE7);
  DLINE7 = "                ";
  tft_89.setCursor(0, 200);
 // if (XDLINE8 != DLINE8) {tft_89.println(DLINE8);XDLINE8 = DLINE8;};
  tft_89.setCursor(0, 210);
  tft_89.setTextSize(1);
  
  if (ina_connected) {
    tft_89.println (" CURRENT DRAW");
    //TEMP");
    tft_89.setCursor(0, 220);
    tft_89.setTextSize(2);
    if (XDLINE3 != DLINE3) {tft_89.println(DLINE3);XDLINE3 = DLINE3;};
  };
  tft_89.setCursor(140, 210);
  tft_89.setTextSize(1);
  tft_89.println ("SYSTEM UPTIME");
  tft_89.setCursor(140, 220);
  tft_89.setTextSize(2);
  tft_89.println(DLINE6);
  // "Binary", "Door", "Window", "Switch", "Relay", "Light", "Relay3", "iBinary"
  switch (ICONLINE) {
    case '0':
      tft_89.drawBitmap(0, 100, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '1':
      tft_89.drawBitmap(0, 100, bitmapDoor, 48, 48, BLUE, BLACK);
    break;
    case '2':
      tft_89.drawBitmap(0, 100, bitmapWindow, 48, 48, BLUE, BLACK);
    break;
    case '3':
      tft_89.drawBitmap(0, 100, bitmapSwitch, 48, 48, BLUE, BLACK);
    break;
    case '4':
      tft_89.drawBitmap(0, 100, bitmapFlash, 48, 48, BLUE, BLACK);
    break;
    case '5':
      tft_89.drawBitmap(0, 100, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '6':
      tft_89.drawBitmap(0, 100, bitmapTimer, 48, 48, BLUE, BLACK);
    break;
    case '7':
      tft_89.drawBitmap(0, 100, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '8':
      tft_89.drawBitmap(0, 100, bitmapHarddisk, 48, 48, BLUE, BLACK);
    break;
  }
 // tft_89.drawBitmap(10, 100, bitmapFlash, 48, 48, BLUE);
//  tft_89.setTextSize(2);
//  tft_89.setCursor(0, 100);
//  tft_89.println (ICONLINE);
  
// tft_89.drawBitmap(80, 100, entity_bar, 111, 33, CYAN);
}
void display_status_tft_35 () {
  // tft_35.setRotation(1);

  tft_35.setCursor(40, 5);
  tft_35.setTextColor(ST77XX_CYAN);
  tft_35.setTextSize(1.5);
  tft_35.print("  LH");
  tft_35.println(CURR_VERS);
  tft_35.setCursor(0, 30);
  tft_35.setTextColor(ST77XX_WHITE,BLACK);
  tft_35.setTextSize(1);
  if (XDLINE1 != DLINE1) {tft_35.println(DLINE1);XDLINE1 = DLINE1;};
  tft_35.setTextSize(1);
  tft_35.setTextColor(ST77XX_GREEN,BLACK);
  tft_35.setCursor(0, 40);
  if (XDLINE8 != DLINE8) {
   // tft_35.println("                   ");
    tft_35.setCursor(0, 40);
    tft_35.println(DLINE8);XDLINE8 = DLINE8;};
  tft_35.setCursor(0, 60);
 // if (XDLINE3 != DLINE3) {tft_35.println(DLINE3);XDLINE3 = DLINE3;};
  tft_35.setTextColor(GREEN,BLACK);
 // tft_35.setCursor(50, 115);
  tft_35.setCursor(50, 50);
  if (XDLINE2 != DLINE2) {
    tft_35.setTextSize(1);
    tft_35.println("          ");
    tft_35.setCursor(50, 50);
    tft_35.println(DLINE2);
    XDLINE2 = DLINE2;
    tft_35.setTextSize(2);
  };
  tft_35.setCursor(0, 70);
  if (XDLINE5 != DLINE5) {tft_35.println(DLINE5);XDLINE5 = DLINE5;};
//  tft_35.setCursor(0, 80);
 // if (XDLINE6 != DLINE6) {tft_35.println(DLINE6);XDLINE6 = DLINE6;};
//  tft_35.setCursor(0, 90);
//  display.setTextColor(YELLOW, BLACK);
//  tft_35.setTextSize(1);
//  tft_35.println(DLINE7);
  
  DLINE7 = "                ";
  
  tft_35.setCursor(0, 100);
 // if (XDLINE8 != DLINE8) {tft_35.println(DLINE8);XDLINE8 = DLINE8;};
  tft_35.setCursor(0, 105);
  tft_35.setTextSize(1);
  
  if (ina_connected) {
    tft_35.println (" CURRENT DRAW");
    //TEMP");
    tft_35.setCursor(0, 110);
    tft_35.setTextSize(2);
    if (XDLINE3 != DLINE3) {tft_35.println(DLINE3);XDLINE3 = DLINE3;};
  };
  tft_35.setCursor(70, 105);
  tft_35.setTextSize(1);
  tft_35.println ("UPTIME");
  tft_35.setCursor(70, 115);
  tft_35.setTextSize(1);
  tft_35.println(DLINE6);
  
  // "Binary", "Door", "Window", "Switch", "Relay", "Light", "Relay3", "iBinary"
  switch (ICONLINE) {
    case '0':
      tft_35.drawBitmap(0, 50, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '1':
      tft_35.drawBitmap(0, 50, bitmapDoor, 48, 48, BLUE, BLACK);
    break;
    case '2':
      tft_35.drawBitmap(0, 50, bitmapWindow, 48, 48, BLUE, BLACK);
    break;
    case '3':
      tft_35.drawBitmap(0, 50, bitmapSwitch, 48, 48, BLUE, BLACK);
    break;
    case '4':
      tft_35.drawBitmap(0, 50, bitmapFlash, 48, 48, BLUE, BLACK);
    break;
    case '5':
      tft_35.drawBitmap(0, 50, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '6':
      tft_35.drawBitmap(0, 50, bitmapTimer, 48, 48, BLUE, BLACK);
    break;
    case '7':
      tft_35.drawBitmap(0, 50, bitmapBinary, 48, 48, BLUE, BLACK);
    break;
    case '8':
      tft_35.drawBitmap(0, 50, bitmapHarddisk, 48, 48, BLUE, BLACK);
    break;
  }
 // tft_35.drawBitmap(10, 50, bitmapFlash, 48, 48, BLUE);
//  tft_35.setTextSize(2);
//  tft_35.setCursor(0, 100);
//  tft_35.println (ICONLINE);
  
// tft_35.drawBitmap(80, 50, entity_bar, 111, 33, CYAN);
}

void display_status_oled () {
  display.clearDisplay();
  if (eth_connected == true) {showEthconnected();}; 
  if (wifi_connected == true){showWificonnected();};
  if (eth_connected == false && wifi_connected == false){showEthoff();};
  if (MQTT_connected == true) {showMQTTconnected();}; 
  if (MQTT_connected == false) { showMQTToff();};
 
 
  display.setTextColor(WHITE);
  display.setCursor(32, 6);
  display.print(" LH ");
  display.println(CURR_VERS);
  display.setCursor(0,20);
  display.setTextSize(1);
  display.print (DLINE1);
  display.setTextSize(2);
  display.setCursor(0,32);
  display.print (DLINE2);
  display.setTextSize(1);
  display.setCursor(0,56);
  display.print (DLINE3);
  display.setCursor(70,56);
  display.print (DLINE6);
  display.display(); 
}
void display_status () {
  if (eth_connected == true) {showEthconnected();}; 
  if (eth_connected == false) {showEthNot();}; 
  if (wifi_connected == true){showWificonnected();};
  if (eth_connected == false && wifi_connected == false){showEthoff();};
  if (MQTT_connected == true) {showMQTTconnected();}; 
  if (MQTT_connected == false) { showMQTToff();};
  if (oled_connected) {display_status_oled ();};  
  if (tft_89_connected) {display_status_tft_89 ();};
  if (tft_35_connected) {display_status_tft_35 ();};
}
