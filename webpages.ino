void handleConfig() {
  conf.handleFormRequest(&server);
  if (server.hasArg("SAVE")) {
    uint8_t cnt = conf.getCount();
    Serial.println("*********** Configuration ************");
    for (uint8_t i = 0; i<cnt; i++) {
      Serial.print(conf.getName(i));
      Serial.print(" = ");
      Serial.println(conf.values[i]);
    }
  //  if (conf.getBool("switch")) Serial.printf("%s %s %i %5.2f \n",
  //                              conf.getValue("ssid"),
  //                              conf.getString("continent").c_str(), 
  //                              conf.getInt("amount"), 
  //                              conf.getFloat("float"));
  }
}

//-----------------------------ROOT--------------------
 

String Atesthtml ="<!DOCTYPE html> <html> <head> <style> .button { border: none; color: white; padding: 16px 32px; text-align: center; text-decoration: none; display: inline-block; font-size: 16px; margin: 4px 2px; transition-duration: 0.4s; cursor: pointer; } .button1 { background-color: white; color: black; border: 2px solid #4CAF50; } .button1:hover { background-color: #4CAF50; color: white; } .button2 { background-color: white; color: black; border: 2px solid #008CBA; } .button2:hover { background-color: #008CBA; color: white; } </style> </head> <body> <button class=\"button button1\">Main Config</button><a href=\"/config\"> <button class=\"button button2\">I/O Config</button><a href=\"/hmcp\"> </body> </html>";


static const char PROGMEM RUSure[] = R"rawliteral(  
<!DOCTYPE html>
<html>
<head>
<style>

.link_button {
    -webkit-border-radius: 4px;
    -moz-border-radius: 4px;
    border-radius: 4px;
    border: solid 1px #20538D;
    text-shadow: 0 -1px 0 rgba(0, 0, 0, 0.4);
    -webkit-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    -moz-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    background: #4479BA;
    color: #FFF;
    padding: 10px 12px;
    text-decoration: none;
    font-size: 36px;
    display: block;
    width: 50%;
    text-align: center
  
}

.button1 {
  background-color: white;
  color: black;
  border: 2px solid #8B0000;
}

.button1:hover {

  background-color: #8B0000;
  color: white;
}  
  
.button2 {
  background-color: white;
  color: black;
  border: 2px solid #006400;
}

.button2:hover {

  background-color: #006400;
  color: white;
}
  
</style>
</head>
 <h1 style="text-align: center; font-family: Helvetica;">ARE YOU SURE?</h1>
<body>

  <a href="/reset6969" style="display:block; margin: 0 auto;" class="link_button button2">YES</a>
  <a href="/" style="display:block; margin: 0 auto;" class="link_button button1">NO</a>
  
  <p style="text-align: center ; font-family: Helvetica;">This connot be undone!
</form>

</body>
</html>
)rawliteral";

void handleRoot () {
static const char PROGMEM ROOT_HTML[] = R"rawliteral( 
<!DOCTYPE html>
<html>
<head>
<style>
.link_button {
    -webkit-border-radius: 4px;
    -moz-border-radius: 4px;
    border-radius: 4px;
    border: solid 1px #20538D;
    text-shadow: 0 -1px 0 rgba(0, 0, 0, 0.4);
    -webkit-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    -moz-box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    box-shadow: inset 0 1px 0 rgba(255, 255, 255, 0.4), 0 1px 1px rgba(0, 0, 0, 0.2);
    background: #4479BA;
    color: #FFF;
    padding: 10px 12px;
    text-decoration: none;
    font-size: 36px;
    display: block;
    width: 25%;
    text-align: center
}
.button1 {
  background-color: red;
  color: black;
  border: 2px solid #8B0000;
}
.button1:hover {
  background-color: #8B0000;
  color: white;
}  
.button2 {
  background-color: green;
  color: black;
  border: 2px solid #008CBA;
}
.button2:hover {
  background-color: #008CBA;
  color: white;
}
</style>
</head>
<h1 style="text-align: center; font-family: Helvetica;">Multi-GPIO Controller</h1>
<body>
<a href="/info"  style="display:block; margin: 0 auto;" class="link_button button2">Device Info</a>
<a href="/config" style="display:block; margin: 0 auto;" class="link_button button2">Main Config</a>
<a href="/hmcp"  style="display:block; margin: 0 auto;"class="link_button button2">I/O Pins Config</a>
<a href="/reset" style="display:block; margin: 0 auto;" class="link_button button1">Reset I/O Assignments</a>
<a href="/serverIndex" style="display:block; margin: 0 auto;" class="link_button button2">Firmware Update</a>
<a href="/contact" style="display:block; margin: 0 auto;" class="link_button button2">Contact</a>
</body>
</html>)rawliteral";
server.send(200, "text/html", ROOT_HTML);
}
// <a href="/uploadspiff"  style="display:block; margin: 0 auto;" class="link_button button2">Device Control(inactive)</a>



//-----------------------------RESET--------------------
void handleReset() {   // NEED TO ADD ARE YOU SURE?
     server.send(200, "text/html", RUSure);
  //    mcpfileClear(); // Remove 0*0.json files so a new one is created next reboot
 //    handleRoot();
}

void handleCompleteReset() {   // NEED TO ADD ARE YOU SURE?
   
     mcpfileClear(); // Remove 0*0.json files so a new one is created next reboot
     handleRoot();
}

//-----------------------------UPDATE--------------------

void handleUpdate() {   // NEED TO ADD ARE YOU SURE?
   
     mcpfileClear(); // Remove 0*0.json files so a new one is created next reboot
     handleRoot();
}
//-----------------------------SAVED ASSIGNMENTS--------------------
void handleSavedAssignments () {
String SAVED_ASSIGNMENTS_HTML ="<form method=\"get\" action=\"/\"> <button style=\"text-align: center;\" type=\"submit\">Continue</button> </form>";
server.send(200, "text/html", SAVED_ASSIGNMENTS_HTML);
}

//-----------------------------INFO--------------------
void handleInfo () {
static const char PROGMEM INFO_HTML[] = R"rawliteral( 
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><span style="font-size:36px">Connected Devices</span></span></p>
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">This page identifies what devices are recognized.&nbsp; </span></em></span></p>
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">If no i2c devices are found check the i2c pin assignments.</span></em></span></p>
<p style="text-align:center">&nbsp;</p>
)rawliteral";

//String html_outline = "<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">";
String html_outline;
String html_newline ="<p style=\"text-align:center\"><span style=\"font-family:Trebuchet MS,Helvetica,sans-serif\"><span style=\"font-size:28px\">";

//Found oled at 0x03C</span></span></p>";
  html_outline = INFO_HTML;
  html_outline += html_newline;
  // html_outline += "<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">";
  if (tft_connected) {html_outline += "SPI TFT Selected (does not detect)";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (eth_connected) {html_outline += "Ethernet Connected";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (wifi_connected) {html_outline += "Wifi Connected";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (oled_connected) {html_outline += "Found oled at 0x03C";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (ina_connected) {html_outline += "INA260 power sensor at address 0x040";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (aht_connected) {html_outline += "AHT10 Temperature & Humidity sensor";html_outline += "</span></span></p>";html_outline += html_newline;};
  if (bme_connected) {html_outline += "BME280 Temperature & Humidity sensor";html_outline += "</span></span></p>";html_outline += html_newline;};
  for (int i = 0; i<8; i++) {if (mcpactivebuff[i]==1) {html_outline += "MCP23017 Connected at 0x02";
    html_outline += i;
    html_outline += "</span></span></p>";
    html_outline += html_newline;};
  }
 // html_outline += "</span></em></span></p>";


  server.send(200, "text/html", html_outline);
}



//---------------------------------------------------------



//------------------------------------------------
static const char PROGMEM singleLine[] = R"rawliteral(  
<!DOCTYPE html>
<html>
<head>
<title>Single Line Input</title>
</head>
<body>
<form method="post" action="/save" >
<label for='name'>Serial Printer (Put Text here: ): </label>
<br><br>
<input type='text' id='name' name='name' required minlength='0' maxlength='10' size='10'>
<input type="submit" name="clk_action" value="accept">
</form>
</body>
</html>
)rawliteral";

//------------------------------------------------


void handleMCP() { 
     server.send(200, "text/html", singleLine);
}
/*
//------------------------------------------------
void handleSingleLine() {
  server.send(200, "text/html", singleLine);
}
*/
void handleContact () {
static const char PROGMEM CONTACT_HTML[] = R"rawliteral( 
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><span style="font-size:36px">Logix PCB Multi-GPIO</span></span></p>
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">Open Source Software by</span></em></span></p>
<p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><em><span style="font-size:20px">Mike Degenaars</span></em></span></p>
<p style="text-align: center;"><span style="font-size:20px"><a href="mailto:logixpcb@gmail.com">logixpcb@gmail.com</a></p>
<p style="text-align: center;"><span style="font-size:20px"><a href="https://github.com/logichousepcb/Logix_Multifunction">https://github.com/logichousepcb/Logix_Multifunction</a></p>
<p style="text-align: center;">&nbsp;</p>
<p>&nbsp;</p>
)rawliteral";
String html_new ="<p style=\"text-align:center\"><span style=\"font-family:Arial,Helvetica,sans-serif\"><span style=\"font-size:20px\">";
String html_outline = CONTACT_HTML;
html_outline += html_new; 
html_outline += "Firmware version: ";
html_outline += CURR_VERS;
html_outline += "</span></span></p>";
server.send(200, "text/html", html_outline);
} 
