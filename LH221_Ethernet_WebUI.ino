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
#include <M:\Arduino\esp32-sh1106-oled-master\Adafruit_SH1106.h>
#include <Wire.h>                     // For I2C
#include <Adafruit_SSD1306.h>
/*** DEFINE ETHERNET ETH01 ****/
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

/****** BUFFERS TO HOLD MCP States ********/
int mcp0buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp1buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp2buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp3buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp4buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp5buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp6buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int mcp7buff[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


#define CURR_VERS              "2.0"
String DLINE1 = "Chip Line";
String DLINE2 = "PIN Line";
String DLINE3 = "ACT Line";
const int bouncedelay = 150;  // THIS IS A DELAY TO TRY AND PREVENT DOUBLE PRESS OR SENSOR BOUNCE - PROBABLY A BETTER WAY 
/*--------------------------- Global Variables ---------------------------*/
// Each bit corresponds to an MCP found on the IC2 bus
/* MCP23017 */
const String    MCP_FILENAME[8]     = { "data0x20.json", "data0x21.json", "data0x22.json", "data0x23.json", "data0x24.json", "data0x25.json", "data0x26.json", "data0x27.json" };
const String    MCP_CHIPNAME[8]     = { "020", "021", "022", "023", "024", "025", "026", "027" };
 
// const uint8_t MCP_COUNT             = sizeof(MCP_ADDRESS);
// I/O buffers
// Adafruit_MCP23017 mcp23017[MCP_COUNT];
Adafruit_MCP23017 mcp0;
Adafruit_MCP23017 mcp1;
Adafruit_MCP23017 mcp2;
Adafruit_MCP23017 mcp3;
Adafruit_MCP23017 mcp4;
Adafruit_MCP23017 mcp5;
Adafruit_MCP23017 mcp6;
Adafruit_MCP23017 mcp7;
StaticJsonDocument<450> mcpdoc[8]; // Array of 8 Json documents to store MCP23017 values 

WebServer server;
WebConfig conf;
WiFiClient ethClient;   
PubSubClient client(ethClient);

bool eth_connected = false;

/*********** MQTT STUFF ************/
bool MQTT_connected = false;
bool boot = true;
// const char* mqtt_server = conf.getValue("mqtt-address");
//const int mqtt_port = atoi(conf.getValue("mqtt-port"));
//const char *mqtt_user = conf.getValue("mqtt-username");
//const char *mqtt_pass = conf.getValue("mqtt-pw");
//const char *mqtt_client_name = conf.getValue("mqtt-topic"); 
byte willQoS = 0;
const char* willTopic = "/checkIn";
const char* willMessage = "Offline";
boolean willRetain = true;
/***************************** for recieved msg ***************************/
char* reportTopic = "/lastcmnd";
char* reedTopic = "/cmnd"; 


void setup() {
  
  Serial.begin(115200);
//  Serial.println(params);
  conf.setDescription(params);
  conf.readConfig();
  setupSPIFF();
  setup_i2c(); 
  mcprenewAllJson(); // remove this and put in only if first boot
//  mcprenewJson();  // JUST FOR TESTING __ REMOVE THIS
  mcpfileCheck(); // Check for mcp23017.cfg and create if not exists
//  mcpfileRenew(); // Remove mcp23017.cfg so a new one is created next reboot
//  mcpfileWrite(0); // writes mcpjsondoc to file -- PUKES
//  mcpfileRead();
//
  const char* filename = "/data.json";
//  createDataFile (0);
  writeDataToFile(filename);
  readDataFromFile("/chip020.json");



//
  
  
  
  
  setup_display();
//  scanI2CBus();
  initEth();
 // initWiFi();
  DLINE2 = conf.getValue("mqtt-address");
  DLINE3 = conf.getValue("mqtt-port");
 // client.setServer(mqtt_server,mqtt_port);
    Serial.print("MQTT---->");
    Serial.println(conf.getValue("mqtt-address"));
    client.setServer(conf.getValue("mqtt-address"),atoi(conf.getValue("mqtt-port")));
    client.setCallback(callback);
//    reconnect();
//  if (!client.connected()) 
//  {
//    reconnect();
//  }
 
  char dns[30];
//  sprintf(dns,"%s.local",conf.getApName());
  if (MDNS.begin(dns)) {
//    Serial.println("MDNS responder gestartet");
  }
  ArduinoOTA.setHostname("esp32mx-e");
  ArduinoOTA.begin(); 
  delay (1000);
  server.on("/",handleRoot);
  server.on("/config",handleConfig);
  server.on("/hmcp",handleMCPConfig);
  server.on("/hello",handleHello);
  server.on("/example",handleExample);
  server.on("/mcp",handleMCPCheck);
  server.begin(80);
  delay (3000);
}

void loop() {
  // put your main code here, to run repeatedly:
 // scanI2CBus();
  display_status();
  server.handleClient();
  ArduinoOTA.handle();
//  MDNS.update();
}
