#include <WebServer.h>
#include <ESPmDNS.h>
// #include <SimpleTimer.h>    //https://github.com/marcelloromani/Arduino-SimpleTimer/tree/master/SimpleTimer
#include "SPIFFS.h"
#include <ETH.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <ArduinoOTA.h>     //https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA
#include <WebConfig.h>
#include "config.h"
#include <Adafruit_MCP23017.h>        // For MCP23017 I/O buffers
#include <Adafruit_GFX.h>
#include <ArduinoJson.h>
// #include <M:\Arduino\esp32-sh1106-oled-master\Adafruit_SH1106.h>
#include <Wire.h>                     // For I2C
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA260.h>          // for power monitoring
/*** DEFINE ETHERNET ETH01 ****/

#define CURR_VERS              "2.262"


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
// Each MCP23017 has 16 I/O pins
// #define MCP_PIN_COUNT   16
// Redefine the I2C bus - this will eventually be read from config file
// 17, 16 for esp32mx-e  or 4, 5 for Wemos
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
long lastReconnectAttempt = 0; // for MQTT
unsigned long INAlastMillis;
String DLINE1 = "Chip Line";
String DLINE2 = "PIN Line";
String DLINE3 = "ACT Line";
const int bouncedelay = 150;  // THIS IS A DELAY TO TRY AND PREVENT DOUBLE PRESS OR SENSOR BOUNCE - PROBABLY A BETTER WAY 
/*--------------------------- Global Variables ---------------------------*/
// Each bit corresponds to an MCP found on the IC2 bus
/* MCP23017 */
const String    MCP_CHIPNAME[8]     = { "020", "021", "022", "023", "024", "025", "026", "027" };
const String    PIN_CLASS[8]        = { "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock", "iBinary"};     
const String    PIN_BINARY[16]       = { "0", "1", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15" };
const char*     UNIQUE_ADD_ON       = "5689";
// const uint8_t MCP_COUNT             = sizeof(MCP_ADDRESS);
// I/O buffers
// Adafruit_MCP23017 mcp23017[MCP_COUNT];
Adafruit_MCP23017 mcp[8];
Adafruit_INA260 ina260 = Adafruit_INA260();

StaticJsonDocument<640> mcpdoc[8]; // Array of 8 Json documents to store MCP23017 values 

WebServer server;
WebConfig conf;
WiFiClient ethClient;   
PubSubClient client(ethClient);

bool eth_connected = false;
bool wifi_connected = false;

/*********** MQTT STUFF ************/
bool MQTT_connected = false;
bool boot = true;
bool freshboot = true;

byte willQoS = 0;
const char* willTopic = "/checkIn";
const char* willMessage = "Offline";
boolean willRetain = true;
/***************************** for recieved msg ***************************/
char* mainTopic;
char* stateTopic = "/stat";
char* reportTopic = "/tele";
char* cmndTopic = "/cmnd"; 
String mainTopicS;
int maxTopicLength = 10;
char c[20];

void setup() {
  Serial.begin(115200);
  conf.setDescription(params);
  conf.readConfig(); // THIS NEEDS TO BE FIRST SO setup_mcp knows what chips to setup
  mainTopicS = conf.getValue("mqtt-topic");           //load main topic from config file
 
  mainTopic ="esp1013";
  Serial.print ("MAIN TOPIC IS ----->");
  Serial.println (mainTopicS);
//  char c[20];
  mainTopicS.toCharArray(c, sizeof(c));
  mainTopic = c;

  setupSPIFF();
  setup_i2c(); 
  setup_ina260();
  setup_display();
  mcprenewAllJson(); // place fresh Json doc in memory for all 8 chips - will be updated by read
  Serial.println("checking for files and create missing ones");
  mcpfileCheck(); // Check for all 0*0.json files and create missing ones
 // Serial.println("setup mcp chips");
  readDataFromAll(); 
  initEth();
//  initWiFi();       // ONCE IMPLIMENTED ONLY DO THIS WHEN ETH not connected
  setupMQTT(); 
  setup_mcp ();
  
//  Serial.println("Display whats in json doc after reading into memory");
//  writeJsonToSerial(0);
//  writeJsonToSerial(1);
//  writeJsonToSerial(2);
//  writeJsonToSerial(3);
//  writeJsonToSerial(4);
//  writeJsonToSerial(5);
//  writeJsonToSerial(6);
//  writeJsonToSerial(7); 

   scanI2CBus();
  char dns[30];
  sprintf(dns,"%s.local",conf.getApName());
  if (MDNS.begin(dns)) {
    Serial.println("MDNS responder gestartet");
  }
  ArduinoOTA.setHostname("esp32mx-e");   // CHANGE THIS TO THE NAME FROM WEBCONFIG
  ArduinoOTA.begin(); 
 // delay (1000);
//  server.on("/",handleConfig);
  server.on("/",handleRoot);
  server.on("/config",handleConfig);
  server.on("/hmcp",handleActiveChipAssignPage);
//  server.on("/example",handleExample);
  server.on("/mcp",handleMCP);
  server.on("/contact",handleContact);
  server.on("/test",handleTestRoot);
  server.on("/test2",handleSingleLine);
  server.on("/reset",handleReset);
  server.on("/save",handleSave);  // SAVE PIN ASSIGNMENTS FROM WEB PAGE
  server.on("/info",handleInfo);
  server.begin(80);
//  delay (3000);
}

static const unsigned long REFRESH_INTERVAL = 3000; // ms to refresh amp meter
static unsigned long lastRefreshTime = 0;
    
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  

  if(millis() - lastRefreshTime >= REFRESH_INTERVAL)
  {
  lastRefreshTime += REFRESH_INTERVAL;
   DLINE3 = ina260.readCurrent();
   DLINE3 = DLINE3 + "mA";
  }
//  DLINE1 = 
  display_status();
  MCPReadAllActive ();  //stuck in a loop in here
//  server.handleClient(); // THIS IS WHERE RECIEVED MQTT REQUEST GET PROCESSED
  ArduinoOTA.handle();
// THIS CONNECTS TO MQTT WITHOUT BLOCKING MAIN LOOP - START  
  if (!client.connected()) {
    long now = millis();
    freshboot = true;
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
 //   if (freshboot) {AD_all_entities ();freshboot = false;};  // on a fresh boot auto discover 
    
  }
  if (client.connected()) {
    
  }
  
// THIS CONNECTS TO MQTT WITHOUT BLOCKING MAIN LOOP - END
//  MDNS.update();
}
