float p = 3.1415926;
int tft_rotation = 1;
void setup_TFT(void) {
 display_connected = true;
 //uint16_t time = millis();
 tft_rotation = atoi(conf.getValue("tft-rotation"));
 if (tft_89_connected) {tft_89.init(240, 240);// Init ST7789 240x240
   tft_89.setSPISpeed(40000000);
  
   tft_89.fillScreen(ST77XX_BLACK);
   tft_89.setRotation(tft_rotation);
 //  time = millis() - time;
 //  Serial.print ("Not sure --> ");
 //  Serial.println(time, DEC);
 }; 
 if (tft_35_connected)  {tft_35.initR(INITR_144GREENTAB); // Init ST7735R chip, green tab
   tft_35.setSPISpeed(40000000);
  
   tft_35.fillScreen(ST77XX_BLACK);
   tft_35.setRotation(tft_rotation);
 
 };
  // SPI speed defaults to SPI_DEFAULT_FREQ defined in the library, you can override it here
  // Note that speed allowable depends on chip and quality of wiring, if you go too fast, you
  // may end up with a black screen some times, or all the time.

  //  time = millis() - time;
 //  Serial.print ("Not sure --> ");
 //  Serial.println(time, DEC);
  
 
}
