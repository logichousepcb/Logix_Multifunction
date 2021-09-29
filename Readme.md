#Multi Function Home Control Board

![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/mainpage.PNG)


![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/configpage.PNG)<br>
Configuration Page<br>
I2C GPIO Connection SDA/SCL - This is where your MCP23017 and other I2C devices are connected.<br>
MQTT Server - Enter your MQTT Server IP Address<r>
MQTT Username - Enter your MQTT userame<r>
MQTT Password - Enter your MQTT password<r>
  
This page allows general configuration of device hardware.  Make your own or try one of mine.<br>

![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/pinassignpage.PNG)<br>
MCP23017 Pin Assignment Page<br>
This page allows you to change the pin names to a more friendly name that will be passed to Home Assistant as a sub-topic.  It also allows you to select from 7 different device classes.<br>
{ "Binary", "Door", "Window", "Switch", "Relay", "Light", "Lock" }
