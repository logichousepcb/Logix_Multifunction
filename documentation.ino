/* 
addr 0 = A2 low , A1 low , A0 low  000 0x20
addr 1 = A2 low , A1 low , A0 high 001 0x21
addr 2 = A2 low , A1 high , A0 low  010 0x22
addr 3 = A2 low , A1 high , A0 high  011 0x23
addr 4 = A2 high , A1 low , A0 low  100 0x24
addr 5 = A2 high , A1 low , A0 high  101 0x25
addr 6 = A2 high , A1 high , A0 low  110 0x26
addr 7 = A2 high, A1 high, A0 high 111 0x27

https://davidjwatts.com/youtube/esp8266/esp-convertHTM.html#
*/

// 9/21/2021 - started documenting changes
//             LH22 created to add SPIFF support  
// 9/26/2021 - The start of better Json read and write
// 9/27/2021 - Created Maine HTML page, Contact Page, work started on GPIO naming page and IFO Page
//             pin reading working....need to compare and write to buffer next
// 9/28/2021 - Working file check and create, file save, file read        
//             Basic 16 port pin assignment web page figured out       
// 9/29/2021 - Added better labels and pretty up page including class selection drop down
// 10/4/2021 - worked on pin compare....works against the old buffer format....need to make functiosn to work agaunst new json format
// 10/5/2021 - Pin compare works, pin assign IO type works, created a buffer not part of json file, loks like I fixed read/write json file and increased its size to 640
//             Working modify and save discription field 
// 10/6/2021 - Device class save working and tested to all MCP present (had to change counter from unit8 to int)
//             Cleaned up MQTT, working connect and reconnect without blocking the mainloop
// 10/14/2021 - MQTT works and so does Auto Discovery at the simplest form
// 10/15/2021 - MQTT works for Door/Window and added Binary inverted but not in the WEBUI yet
//              MQTT in works, triggers relays (might be a bug with counting in that function)
//              added ina_260 basic support
// 10/16/2021 - Enable Wifi support, added IP and connection icon to main screen
// 10/21/2021 - Enable relay control working with auto discovery
//              text sensor for finding sensors works with auto discovery
//              COLOR tft display basics
// 10/22/2021 - Added icons and made SPI display pretty
// 10/23/2021 - Pretty main page
//              verify reset gpio assignments
//              added MQTT auto discovery flag, removed display options, started on auto config for i2c  
// 10/28/2021 - Change mcp active status to auto detect and remove varial from config page
// 10/29/2021 - Auto discover for all mcp devices works
// 10/30/2021 - added SPI TFTto config menu cleanned up code (2.33)
// 10/31/2021 - added TFT reotation to config
// 11/4/2021  - fixed retain flag for config topics

/* TO DO LIST
 
MQTT FOR POWER MONITORING

CLEAN UP MQTT PUBLISH 
CLEAN UP MQTT RECEIVE

TEMPERATURE SUPPORT
 
Beeper for fault
fan control


** HOME ASSISTANT API OTHER THAN MQTT AUTO DOSCOVERY **
*/
