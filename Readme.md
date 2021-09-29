#Multi Function Home Control Board

![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/mainpage.PNG)


![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/configpage.PNG)<br>
Configuration Page<br>

This page allows general configuration of device hardware.  Make your own or try one of mine.<br>
I2C GPIO Connection SDA/SCL - This is where your MCP23017 and other I2C devices are connected.<br>
MQTT Server - Enter your MQTT Server IP Address<r>
MQTT Username - Enter your MQTT userame<r>
MQTT Password - Enter your MQTT password<r>
MQTT Topic - Enter your MQTT topic.  MQTT will publish to \Topic\subtopic  (the subtopic is defined in pin assignemnt naming page<r>
MQTT Port - Enter your MQTT Port (default:1883)<r>
Active Expanders - Select all the active expanders on your device (the info screen will eventaully show you which are detected)
Connected Displays - This allows you to select which displays are connected to the device.  As I add support I will add the display here.
  


![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/pinassignpage.PNG)<br>
MCP23017 Pin Assignment Page<br>
This page allows you to change the pin names to a more friendly name that will be passed to Home Assistant as a sub-topic.  It also allows you to select from 7 different device classes.<br>
{ "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock" }

  
  // 9/21/2021 - started documenting changes
//             LH22 created to add SPIFF support  
// 9/26/2021 - The start of better Json read and write
// 9/27/2021 - Created Maine HTML page, Contact Page, work started on GPIO naming page and IFO Page
//             pin reading working....need to compare and write to buffer next
// 9/28/2021 - Working file check and create, file save, file read        
//             Basic 16 port pin assignment web page figured out       
// 9/29/2021 - Added better labels and pretty up page including class selection drop down

/* TO DO LIST
FIX READING JSON FROM A FILE 
FIX WRITE FROM THE ASSIGNMENTS WEB PAGE
NEED TO COMPARE READ PIN TO BUFFER 
FAILED PULL HIGH INITIALIZATION
ADD SPI 240X240 COLOR DISPLAY SUPPORT
MQTT CONNECT
MQTT PUBLISH
MQTT RECEIVE
MQTT AUTO DISCOVERY
TEMPERATURE SUPPORT
RGB LED status light 
** HOME ASSISTANT API OTHER THAN MQTT AUTO DOSCOVERY **
