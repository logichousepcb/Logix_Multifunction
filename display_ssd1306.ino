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


#define bitmap_height   128
#define bitmap_width    64
static const unsigned char PROGMEM bitmap[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xE1, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC0, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xC0, 0x00, 0x00, 0x07, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xE0, 0xFF, 0x00, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7F, 0xE0, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFE, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x70, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
0x01, 0xF0, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x01, 0xF0, 0x0C, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00,
0x03, 0xE0, 0xFF, 0x03, 0xF8, 0xEF, 0xBC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00,
0x03, 0xC3, 0xCF, 0x8F, 0x79, 0xE3, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00,
0x07, 0x83, 0xC7, 0xBE, 0x79, 0xE1, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00,
0x07, 0x97, 0xC7, 0x3F, 0xFB, 0xC7, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00,
0x0F, 0xF3, 0xFE, 0x3F, 0x7B, 0xCF, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x0F, 0x83, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xF0, 0x7F, 0xEF, 0xFF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF1, 0xF3, 0xE7, 0xCF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x3C, 0xF3, 0xE7, 0x87, 0xBF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x7D, 0xF7, 0xCF, 0x8F, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC7, 0xCD, 0xFF, 0x0F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x00, 0xF0, 0x07, 0xFF, 0x9E, 0x0F, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x01, 0xFC, 0x1E, 0x3E, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x07, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x0F, 0xFF, 0xFF, 0xFE, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFE, 0x0F, 0xFF, 0xFE, 0x07, 0xF8,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x7E,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x01, 0xFC,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFE, 0x3F, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM bitmapEthOn [] =
{ 0x7F, 0xFE, 0xC0, 0x03, 0x80, 0x01, 0x80, 0x01, 0x83, 0xC1, 0x83, 0xC1, 0x9F, 0xF9, 0x9F, 0xF9,
0x9F, 0xF9, 0x9F, 0xF9, 0x9B, 0xD9, 0x9B, 0xD9, 0x80, 0x01, 0x80, 0x01, 0xC0, 0x03, 0x7F, 0xFE
};

static const unsigned char PROGMEM bitmapWifiOn [] =
{0x00, 0x00, 0x00, 0x00, 0x0F, 0xF0, 0x3F, 0xFC, 0x70, 0x0E, 0x67, 0xE6, 0x1F, 0xF8, 0x18, 0x18,
0x13, 0xC8, 0x07, 0xE0, 0x04, 0x20, 0x01, 0x80, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM bitmapMQTTOn [] = {
0x40, 0x0A, 0xFF, 0x07, 0x07, 0xC2, 0x01, 0xE1, 0x40, 0x70, 0xF8, 0x38, 0x7E, 0x1C, 0x0F, 0x0C,
0x03, 0x8E, 0xC1, 0xC6, 0xF0, 0xE7, 0xF8, 0xE2, 0xFC, 0x62, 0xFE, 0x72, 0xFE, 0x73, 0x7E, 0x30
};

static const unsigned char PROGMEM bitmapEthOff [] =
{ 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x07, 0xF8, 0x0F, 0xDF, 0xFD, 0xCF, 0xF9, 0xDF, 0xFD, 0xDF, 0xFD,
0xDF, 0xFD, 0xDF, 0xFD, 0xDF, 0xFD, 0xDF, 0xFD, 0xDF, 0xFD, 0xF8, 0x0F, 0xF0, 0x07, 0xFF, 0xFF
};

static const unsigned char PROGMEM bitmapMQTTOff [] = {
0x60, 0x0F, 0xFF, 0x8F, 0xFF, 0xEF, 0x07, 0xFF, 0x61, 0xFD, 0xFC, 0x7C, 0xFF, 0xFE, 0x7F, 0xFE,
0x0F, 0xCF, 0xE7, 0xEF, 0xFF, 0xF7, 0xFE, 0xF7, 0xFE, 0xF3, 0xFF, 0x7B, 0xFF, 0x7B, 0xFF, 0x7B
};

void showBitmap(void) {
  display.clearDisplay();
  display.drawBitmap(0, 0, bitmap, bitmap_height, bitmap_width, WHITE);
  display.display();
  delay(1500);
}

void showEthconnected() {
  display.drawBitmap(0, 0, bitmapEthOn, 16, 16, WHITE);
 // display.display();
}

void showWificonnected() {
  display.drawBitmap(0, 0, bitmapWifiOn, 16, 16, WHITE);
 // display.display();
}

void showMQTTconnected() {
  display.drawBitmap(112, 0, bitmapMQTTOn, 16, 16, WHITE);
//  display.display();
}

void showEthoff() {
  display.drawBitmap(0, 0, bitmapEthOff, 16, 16, WHITE);
//  display.display();
}

void showMQTToff() {
  display.drawBitmap(112, 0, bitmapMQTTOff, 16, 16, WHITE);
//  display.display();
}

void display_status () {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 0);
  display.print(" LH ");
  display.println(CURR_VERS);
  
  if (eth_connected == true) {showEthconnected();}; 
  if (wifi_connected == true){showWificonnected();};
  if (eth_connected == false && wifi_connected == false){showEthoff();};
  
   
  if (MQTT_connected == true) {showMQTTconnected();}; 
  if (MQTT_connected == false) { showMQTToff();};

  display.setCursor(0,20);
  display.setTextSize(1);
  display.print (DLINE1);
  display.setTextSize(2);
  display.setCursor(0,32);
  display.print (DLINE2);
   display.setCursor(0,48);
  display.print (DLINE3);
    
  display.display(); 
 // display.clearDisplay();
}
