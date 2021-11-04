#include <WebServer.h>
//#include <AsyncTCP.h>
//#include <ESPAsyncWebServer.h>
//#include <AsyncElegantOTA.h>
#include <Update.h>
#include <ESPmDNS.h>
// #include <SimpleTimer.h>    //https://github.com/marcelloromani/Arduino-SimpleTimer/tree/master/SimpleTimer
#include "SPIFFS.h"
#include <ETH.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <ArduinoOTA.h>     //https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA
#include <WebConfig.h>
#include "config.h"
#include "TFTsplash.h"
#include "icons.h"
#include <Adafruit_MCP23017.h>        // For MCP23017 I/O buffers
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <ArduinoJson.h>
// #include <M:\Arduino\esp32-sh1106-oled-master\Adafruit_SH1106.h>
#include <Wire.h>                     // For I2C
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA260.h>          // for power monitoring
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>



#define CURR_VERS              "2.34"
//**************** DEFINITIONS FOR spi lcd
 
#define TFT_CS         5 // USE SOMETHING DIFFERENT for v2.6 of board
#define TFT_RST        2 //15                                            
#define TFT_DC         4 //13
// For 1.14", 1.3", 1.54", 1.69", and 2.0" TFT with ST7789:
//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
#define TFT_MOSI 17 //23  // Data out
#define TFT_SCLK 33 //18  // Clock out

//**************** DEFINITIONS FOR RGB LED
#include <Adafruit_NeoPixel.h>

//**************** DEFINITIONS ON-BOARD I/O
#define PIXEL_PIN      32 // NEOPIXEL PIN
#define NUMPIXELS 1
#define RELAY_PIN      12 
#define BTN1_PIN       35
#define BTN2_PIN       36  
#define BTN3_PIN       39
Adafruit_NeoPixel pixels(NUMPIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
//**************** DEFINITIONS FOR ethernet
#define ETH_ADDR      1     
#define ETH_POWER_PIN 16    // There is no power pin, use -1 to disable the code
#define ETH_MDC_PIN   23
#define ETH_MDIO_PIN  18
#define ETH_TYPE      ETH_PHY_LAN8720
#ifdef ETH_CLK_MODE
#undef ETH_CLK_MODE
#endif
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
/*** DEFINE DISPLAY ****/
// LCD
// LiquidCrystal_I2C lcd(0x3F, 16, 2);
/******initial i2c settings changed by config file ******/
int I2C_SDA = 14;
int I2C_SCL = 15;
// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
//Adafruit_SH1106 display(I2C_SDA,I2C_SCL);
/*--------------------------- Constants ----------------------------------*/
// 17, 16 for esp32mx-e  or 4, 5 for Wemos or 
//#define I2C_SDA 14
//#define I2C_SCL 15

/****** BUFFERS TO HOLD MCP States ******* REPLACED BY STATE IN CHIP JSON ******/

int mcpbuff[8][16] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int obiobuff [4] = {0, 0, 0 ,0};
bool breturn = false;
int mcpactivebuff[8] = {0, 0, 0, 0, 0, 0, 0, 0};
long lastReconnectAttempt = 0; // for MQTT
unsigned long INAlastMillis;
String DLINE1 = "IP Line";
String DLINE2 = "INFO Line";
String DLINE3 = "AMP Line";
String DLINE4 = "D LINE 4";
String DLINE5 = "D LINE 5";
String DLINE6 = "D LINE 6";
String DLINE7 = "D LINE 7";
String DLINE8 = "D LINE 8";
String DLINE9 = "D LINE 9";
char ICONLINE = '9';
char XICONLINE = ICONLINE;
String XDLINE1 = DLINE1;
String XDLINE2 = DLINE2;
String XDLINE3 = DLINE3;
String XDLINE4 = DLINE4;
String XDLINE5 = DLINE5;
String XDLINE6 = DLINE6;
String XDLINE7 = DLINE7;
String XDLINE8 = DLINE8;
String XDLINE9 = DLINE9;

String ipString;

const int bouncedelay = 10;  // THIS IS A DELAY TO TRY AND PREVENT DOUBLE PRESS OR SENSOR BOUNCE - PROBABLY A BETTER WAY 
/*--------------------------- Global Variables ---------------------------*/
// Each bit corresponds to an MCP found on the IC2 bus
/* MCP23017 */
const String    MCP_CHIPNAME[8]     = { "020", "021", "022", "023", "024", "025", "026", "027" };
const String    PIN_CLASS[8]        = { "Binary", "Door", "Window", "Switch", "Relay", "iBinary", "Relay3", "intRelay"};     
const String    PIN_BINARY[16]       = { "0", "1", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
char*           UNIQUE_ADD_ON;   // this is to keep from getting duplicate HA auto discovery names
// const uint8_t MCP_COUNT             = sizeof(MCP_ADDRESS);
// I/O buffers
// Adafruit_MCP23017 mcp23017[MCP_COUNT];
Adafruit_MCP23017 mcp[8];
Adafruit_INA260 ina260 = Adafruit_INA260();
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
// temperature sensor
Adafruit_BME280 bme; // BME Sensor support
float temperature = 0;
float humidity = 0;
// AHT10


//
StaticJsonDocument<640> mcpdoc[8]; // Array of 8 Json documents to store MCP23017 values 
//AsyncWebServer server(80);
WebServer server;
WebConfig conf;
WiFiClient ethClient;   
PubSubClient client(ethClient);

bool eth_connected = false;
bool wifi_connected = false;
bool tft_connected = false;
bool oled_connected = false;
bool bme_connected = false;
bool ina_connected = false;
bool aht_connected = false;
bool display_connected = false;
bool ob_controls = true; // should the onboard controls be active
/*********** MQTT STUFF ************/
bool MQTT_connected = false;
bool boot = true;
bool freshboot = true;

byte willQoS = 0;
//const char* willTopic = "/checkIn";
const char* willMessage = "Offline";
boolean willRetain = true;
/***************************** for recieved msg ***************************/
char* mainTopic;
char* willTopic;
char* stateTopic = "/stat";
char* reportTopic = "/tele";
char* cmndTopic = "/cmnd"; 
String mainTopicS;
int maxTopicLength = 10;
char c[20];
String unique_id = "";;
char unique_char;


void setup() {
  Serial.begin(115200);
 
  if (ob_controls) {setup_onboard_io();};
  setup_onboard_io();
  freshboot = true;
  conf.setDescription(params);
  conf.readConfig(); // THIS NEEDS TO BE FIRST SO setup_mcp knows what chips to setup
  mainTopicS = conf.getValue("mqtt-topic");           //load main topic from config file
// setup Ethernet and or Wifi
  initEth(); 
   char dns[30];
  // sprintf(dns,"%s.local",conf.getApName());
  if (MDNS.begin(dns)) {
    Serial.println("MDNS Started");
  }
// make a unique add on out of first and third mac adress
  Serial.print("ESP Board Wifi MAC Address:  ");
  Serial.println(WiFi.macAddress());
  unique_id = String(WiFi.macAddress().charAt(0));
  unique_id += String(WiFi.macAddress().charAt(1));
  unique_id += String(WiFi.macAddress().charAt(6));
  unique_id += String(WiFi.macAddress().charAt(7));
  Serial.println(unique_id);
//mainTopic ="esp1013";
  Serial.print ("MAIN TOPIC IS ----->");
  Serial.println (mainTopicS);

// set up mqtt topic to pub and sub to the same as the config file  
  mainTopicS.toCharArray(c, sizeof(c));
  mainTopic = c;
  willTopic = mainTopic;
// setup file system to stop config files  
  setupSPIFF();
// read tft status from setup file and set that flag  
  if (atoi(conf.getValue("spi-tft")) == 1) {setup_TFT();tft_connected = true;display_connected = true;};
// setup i2c and find connected i2c devices
  setup_i2c(); 
  if (ina_connected) {setup_ina260();}; 
  if (oled_connected) {setup_oled();display_connected = true;};
  if (bme_connected) {setup_bme();};
  if (display_connected) {showBitmap();};
  
// place fresh Json doc in memory for all 8 chips - will be updated by read
  mcprenewAllJson(); 
// Check for all 0*0.json files and create missing ones
  mcpfileCheck(); 
// read data from all old config files of mcp23017 into memory
  readDataFromAll(); 
// setup MQTT - thing about ability to turn off in future
  setupMQTT(); 
// initialize each pin of the mcp23017 that are active based on the config values
  setup_mcp ();
  
 


 
// OTA for Arduino IDE 
  ArduinoOTA.setHostname(conf.getValue("mqtt-topic"));
  ArduinoOTA.begin(); 


// WEB UI page assignments
  server.on("/",handleRoot);
  server.on("/config",handleConfig);
  server.on("/hmcp",handleActiveChipAssignPage);
  server.on("/mcp",handleMCP);
  server.on("/contact",handleContact);
  server.on("/reset",handleReset);
  server.on("/reset6969",handleCompleteReset);
  server.on("/save",handleSave);  // SAVE PIN ASSIGNMENTS FROM WEB PAGE
  server.on("/info",handleInfo);

 
   
// START Web UI server
  server.begin(80);

}

static const unsigned long REFRESH_INTERVAL = 5000; // ms to refresh amp meter
static unsigned long lastRefreshTime = 0;
static const unsigned long Will_REFRESH_INTERVAL = 60000; // ms to refresh amp meter
static unsigned long lastWillRefreshTime = 0;
    
void loop() {
// put your main code here, to run repeatedly:
  
  server.handleClient();
// refresh screen data
  DLINE3 = ""; 
  if(millis() - lastWillRefreshTime >= Will_REFRESH_INTERVAL)
  {
      lastWillRefreshTime += Will_REFRESH_INTERVAL;
      if (MQTT_connected) {client.publish(willTopic,"online");Serial.print("!");};
  
  };
  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
  lastRefreshTime += REFRESH_INTERVAL;
   
   if (bme_connected) {BME_temp ();};
//   if (aht_connected) {get_aht();};
   if (ina_connected) {DLINE3 = ina260.readCurrent();DLINE3 = DLINE3 + "mA";};
  
   if (wifi_connected == true) {
     DLINE1 = "WIFI:";
     ipString = WiFi.localIP().toString().c_str();
     DLINE1 = DLINE1 + ipString + "  ";
   };
   if (eth_connected == true)  {
     DLINE8 = DLINE1;
     DLINE1 = "ETH: ";
     ipString = ETH.localIP().toString().c_str();
     DLINE1 = DLINE1 + ipString + "  ";
   };
     
  }
  if (display_connected) {display_status();};
  if (ob_controls) {onboard_io_compare();};
  MCPReadAllActive ();  

//  server.handleClient(); // THIS IS WHERE RECIEVED MQTT REQUEST GET PROCESSED
  ArduinoOTA.handle();

// THIS CONNECTS TO MQTT WITHOUT BLOCKING MAIN LOOP - START  
  if (!client.connected()) {
    long now = millis();
    
    MQTT_connected = false;
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected
    client.loop();
    if (freshboot && (atoi(conf.getValue("mqtt-ad"))== 1)) {AD_all_entities ();freshboot = false;};  // on a fresh boot auto discover 
    
  }
  if (client.connected()) {
    
  }
  
// THIS CONNECTS TO MQTT WITHOUT BLOCKING MAIN LOOP - END
//  MDNS.update();
}
