String params = "["
  "{"
  "'name':'ssid',"
  "'label':'Name of WLAN',"
  "'type':"+String(INPUTTEXT)+","
  "'default':''"
  "},"
  "{"
  "'name':'pwd',"
  "'label':'WLAN Password',"
  "'type':"+String(INPUTPASSWORD)+","
  "'default':''"
  "},"
  "{"
  "'name':'sda',"
  "'label':'I2C-SDA',"
  "'type':"+String(INPUTNUMBER)+","
  "'min':4,'max':34,"
  "'default':'14'"
  "},"
  "{"
  "'name':'scl',"
  "'label':'I2C-SCL',"
  "'type':"+String(INPUTNUMBER)+","
  "'min':4,'max':34,"
  "'default':'15'"
  "},"
  "{"
  "'name':'mqtt-address',"
  "'label':'MQTT IP ADDRESS',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'192.168.1.179'"
  "},"
  "{"
  "'name':'mqtt-username',"
  "'label':'MQTT User Name',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'esp'"
  "}," 
  "{"
  "'name':'mqtt-pw',"
  "'label':'MQTT Password',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'password'"
  "},"
  "{"
  "'name':'mqtt-topic',"
  "'label':'MQTT Topic',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'LH-Multi'"
  "}," 
  "{"
  "'name':'mqtt-port',"
  "'label':'MQTT Port',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'1883'"
  "}," 
  "{"
  "'name':'mqtt-ad',"
  "'label':'MQTT Auto Discovery',"
  "'type':"+String(INPUTCHECKBOX)+","
  "'default':'0'"
  "},"
  "{"
  "'name':'dash-bt',"
  "'label':'Dashboard Button',"
  "'type':"+String(INPUTCHECKBOX)+","
  "'default':'1'"
  "},"
  "{"
  "'name':'dash-link',"
  "'label':'Dashboard Address',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'192.168.1.130:5050/Office'"
  "},"
  "{"
  "'name':'button-1',"
  "'label':'Button 1 Name',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'Button-1'"
  "},"
  "{"
  "'name':'button-2',"
  "'label':'Button 2 Name',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'Button-2'"
  "},"
  "{"
  "'name':'button-3',"
  "'label':'Button 3 Name',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'Button-3'"
  "},"
  "{"
  "'name':'relay-1',"
  "'label':'Relay 1 Name',"
  "'type':"+String(INPUTTEXT)+","
  "'default':'OBRelay'"
  "},"
  "{"
  "'name':'spi-type',"
  "'label':'Display Type',"
  "'type':"+String(INPUTRADIO)+","
  "'options':["
  "{'v':'a','l':'240x240 SPI ST7789(1.54)'},"
  "{'v':'b','l':'128x128 SPI ST7735(1.44)'},"
  "{'v':'n','l':'none'}],"
  "'default':'b'"
  "},"
  "{"
  "'name':'tft-rotation',"
  "'label':'TFT Rotation (0-3)',"
  "'type':"+String(INPUTNUMBER)+","
  "'min':0,'max':3,"
  "'default':'1'"
  "}"
  "]";
