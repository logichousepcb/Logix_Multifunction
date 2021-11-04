#Multi Function Home Control Board

The main purpose of the software is to set up, modify and deploy a mcp23017 based multifunction board.  My board started out as a 64 port adapter to adapt the security system wiring built into my house to home assistant.  This wiring mostly consisted of reed switches but I found alarm wiring going to all corners of my house including my attic and basement.  I was eager to find uses for it all.  ESP Home is a great piece of software to connect to home assistant but I found it did not suite my needs and did not seem to handle that many i/o ports.  I set out to design my own.  I started with a simple piece of firmware I wrote that used a config file and adapted the sensors to Home Assitant quite well and it worked for over a year without issue. <br>

Well, as all projects go you want more.  I found others who had a similar board and in adapting my code to fit their needs, I too found some options I wanted.
1 - Ethernet support (a must for me) 
2 - A Web user interface to make changes and add on easily
3 - A simple way to identify the reed switches built into my walls.  

This piece of firmware is just that.  It runs on an ESP32 with WIfi but was built with the WT32-ETH01 ethernet board in mind.  I can't take credit for every piece of this code.  I explore the web when I come across a problem I can't solve on my own and adapt ideas or code from other open source projects to reach my goals.  

So I started with what you see bellow.  A mess of wires coming out of the wall in my front closet.  The wonderful MCP23017 is an i2c port expander that will give you 16 additional binary sensors or output control.  With this each chip can handle basically 16 zones in my house.  I have about 24.  <br>

![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/ADT_Mess.PNG)<br>

I started by wiring each binary sensor (reed switch) to a twisted pair on an RJ45 plug.  Since each plug had 4 pairs, it took 6 plugs to adapt the 24 wires to RJ45.  I then ran 6 cables to my rack mounted server station in the basement where I connected to the board I created.  I designed it to fit in my rack.
 
![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/LH2_0_Rack_Mount.PNG)<br>

On to the software!  Included is a .bin file you can burn to you ESP32 or you can compile yourself.  I used the Arduino IDE and tried to reference the proper libraries I used in the header.

Wifi is supported if you don't want to run ethernet to your closet.  I also have a board that uses terminal blocks to remove the need for any RJ45 wiring. When the board has a fresh install it will generate an access point.  Follow these steps <br>
1- connect to it on your phone - it will generate an odd access point named something like A8032A625CBC<br>
2- navigate to 192.168.4.1 <br>
3- select the Main Configuration page <br>
4- input your SSID and password (careful it is case sensitive) <br>
5- enter your i2c SDA and SCL pins if they differ from the default <br>
5- click save at bottom <br>
6- click restart at bottom <br>
7- if you have an i2c 0.96 oled connected the ip should display on the LCD screen otherwise you may have to check with you router or look at the serail debuger. <br>
8- you can now navigate to that ip from a web browser anywhere on your network (pages sometime load slow due to the speed of the ESP)  I do hope to be able to speed up the code in the future. <br>


You will be greated with this main page when you navigate to the devices ip.  (be patient the first few times) <br>
![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/mainpage.PNG)<br>


Here is the device configuration page where.  
**You can enter/change your wifi information here. <br>
**Change the i2c GPIO ports used for you device but it defaults to mine. <br>
**Enter your MQTT server information. Dont forget your main topic for the devices to publich in.  And yes, if you want to auto discover in home assistant it can be selected. <br>
**If you want a richer display, I built in support for a 240x240 SPI TFT display including rottion in case you mount it sideways or upside down.
*** YOU DO NEED TO SAVE AND RESTART FOR ALL CHANGES TO TAKE EFFECT

![GitHub Logo](https://github.com/logichousepcb/Logix_Multifunction/blob/main/configpage.PNG)<br>

Connected Devices Menu <br>

The firmware will identify certain i2c devices.  If you have one you want to see added tot he list, let me know.  Right now it identifies an 0.96 oled, MCP23017 chips, an INA260 voltage monitor, and a BME280 temperature/humidity sensor.  (I plan to add support for the Serial Wombat and PCF8574 when I get around to playing with them more)  


GPIO Assignment Page<br>

The firmware will identify the the expander chips and assign unique names to them based on portions of the mac address, the chip address and the pin assignment to prevent duplicates.  From this page you can change the name to a more friendly name up to 8 charasters.  Use an underscore in place of spaces.  You can also change the device class.  <br>
** DON'T FORGET TO SAVE WHEN COMPLETE. <br>

Here are the device classes and their function. <br>

Binary
Door
Window
Switch
Relay
iBinary
Relay3
intRelay     


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
