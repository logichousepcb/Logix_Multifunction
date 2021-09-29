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
