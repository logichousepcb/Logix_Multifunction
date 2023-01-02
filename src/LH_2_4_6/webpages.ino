

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
  }
}

//-----------------------------ROOT--------------------

void handleRoot () {
static const char PROGMEM ROOT_HTML[] = R"rawliteral( 
<!DOCTYPE html><html lang="en"class=""><head><meta charset='utf-8'>
  <meta name="viewport"content="width=device-width,initial-scale=1,user-scalable=no"/>
  <title>Multi-GPIO Controller</title>
  <script>var x=null,lt,to,tp,pc='';function eb(s){return document.getElementById(s)}function qs(s){return document.querySelector(s)}function sp(i){eb(i).type=(eb(i).type==='text'?'password':'text')}function wl(f){window.addEventListener('load',f)}var ft;function la(p){a=p||'';clearTimeout(ft);clearTimeout(lt);if(x!=null){x.abort()}x=new XMLHttpRequest();x.onreadystatechange=function(){if(x.readyState==4&&x.status==200){var s=x.responseText.replace(/{t}/g,"<table style='width:100%'>").replace(/{s}/g,"<tr><th>").replace(/{m}/g,"</th><td style='width:20px;white-space:nowrap'>").replace(/{e}/g,"</td></tr>");eb('l1').innerHTML=s;clearTimeout(ft);clearTimeout(lt);lt=setTimeout(la,2345)}};x.open('GET','.?m=1'+a,true);x.send();ft=setTimeout(la,20000)}function lc(v,i,p){if(eb('s')){if(v=='h'||v=='d'){var sl=eb('sl4').value;eb('s').style.background='linear-gradient(to right,rgb('+sl+'%,'+sl+'%,'+sl+'%),hsl('+eb('sl2').value+',100%,50%))'}}la('&'+v+i+'='+p)}wl(la);function jd(){var t=0,i=document.querySelectorAll('input,button,textarea,select');while(i.length>=t){if(i[t]){i[t]['name']=(i[t].hasAttribute('id')&&(!i[t].hasAttribute('name')))?i[t]['id']:i[t]['name']}t++}}wl(jd);</script><style>div,fieldset,input,select{padding:5px;font-size:1em}fieldset{background:#4f4f4f}p{margin:0.5em 0}input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;background:#dddddd;color:#000000}input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px}input[type=range]{width:99%}select{width:100%;background:#dddddd;color:#000000}textarea{resize:vertical;width:98%;height:318px;padding:5px;overflow:auto;background:#1f1f1f;color:#65c115}body{text-align:center;font-family:verdana,sans-serif;background:#252525}td{padding:0px}button{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer}button:hover{background:#0e70a4}.bred{background:#d43535}.bred:hover{background:#931f1f}.bgrn{background:#47c266}.bgrn:hover{background:#5aaf6f}a{color:#1fa3ec;text-decoration:none}.p{float:left;text-align:left}.q{float:right;text-align:right}.r{border-radius:0.3em;padding:2px;margin:6px 2px}</style></head><body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'><div style='text-align:center;color:#eaeaea;'>

<h3>Multi-GPIO Controller</h3>
<body>
  <p>
    <form id=but2 style="display: block;"action='iocontrol'method='get'>
      <button>Control</button>
    </form>
  </p>
  <p>
    <form id=but1 style="display: block;"action='info'method='get'>
      <button>Information</button>
    </form>
  </p>
  <p>
    <form id=but2 style="display: block;"action='config'method='get'>
      <button>Configuration</button>
    </form>
  </p>
  <p>
    <form id=but3 style="display: block;"action='hmcp'method='get'>
      <button>Assign I/O Pins</button>
    </form>
  </p>
  <p>
    <form id=but4 style="display: block;"action='reset'method='get'onsubmit='return confirm("Confirm Reset IO");'>
      <button name='rst'class='button bred'>Reset I/O Assignments</button>
    </form>
  </p>
  <p>
    <form id=but6 style="display: block;"action='firmware'method='get'>
      <button>Firmware Update</button>
    </form>
  </p>
  <p>
    <form id=but6 style="display: block;"action='http://192.168.1.130:5050/Office'method='get'>
      <button>DASHBAORD</button>
    </form>
  </p>
  <p>
    <form id=but4 style="display: block;"action='restart'method='get'onsubmit='return confirm("Confirm Restart");'>
      <button name='rst'class='button bred'>Restart</button>
    </form>
  </p>

<div style='text-align:right;font-size:11px;'><hr/>Logix PCB Multi-GPIO - Open Source Software by Mike Degenaars logixpcb@gmail.com <br>
https://github.com/logichousepcb/Logix_Multifunction <br>
)rawliteral";
String html_new ="<p style=\"text-align:center\"><span style=\"font-family:Arial,Helvetica,sans-serif\"><span style=\"font-size:20px\">";
String html_outline = ROOT_HTML;
html_outline += html_new; 
html_outline += "Firmware version: ";
html_outline += CURR_VERS;
html_outline += "</div></div></body></html>";
server.send(200, "text/html", html_outline);
}
//-----------------------------IO Control--------------------
void handleIOControl () {
static const char PROGMEM IOCONTROL_START_HTML[] = R"rawliteral( 
<!DOCTYPE html><html lang="en"class=""><head><meta charset='utf-8'>
  <meta name="viewport"content="width=device-width,initial-scale=1,user-scalable=no"/>
  <title>MY DEVICE</title>
  <script>var x=null,lt,to,tp,pc='';function eb(s){return document.getElementById(s)}function qs(s){return document.querySelector(s)}function sp(i){eb(i).type=(eb(i).type==='text'?'password':'text')}function wl(f){window.addEventListener('load',f)}var ft;function la(p){a=p||'';clearTimeout(ft);clearTimeout(lt);if(x!=null){x.abort()}x=new XMLHttpRequest();x.onreadystatechange=function(){if(x.readyState==4&&x.status==200){var s=x.responseText.replace(/{t}/g,"<table style='width:100%'>").replace(/{s}/g,"<tr><th>").replace(/{m}/g,"</th><td style='width:20px;white-space:nowrap'>").replace(/{e}/g,"</td></tr>");eb('l1').innerHTML=s;clearTimeout(ft);clearTimeout(lt);lt=setTimeout(la,2345)}};x.open('GET','.?m=1'+a,true);x.send();ft=setTimeout(la,20000)}function lc(v,i,p){if(eb('s')){if(v=='h'||v=='d'){var sl=eb('sl4').value;eb('s').style.background='linear-gradient(to right,rgb('+sl+'%,'+sl+'%,'+sl+'%),hsl('+eb('sl2').value+',100%,50%))'}}la('&'+v+i+'='+p)}wl(la);function jd(){var t=0,i=document.querySelectorAll('input,button,textarea,select');while(i.length>=t){if(i[t]){i[t]['name']=(i[t].hasAttribute('id')&&(!i[t].hasAttribute('name')))?i[t]['id']:i[t]['name']}t++}}wl(jd);</script><style>div,fieldset,input,select{padding:5px;font-size:1em}fieldset{background:#4f4f4f}p{margin:0.5em 0}input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;background:#dddddd;color:#000000}input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px}input[type=range]{width:99%}select{width:100%;background:#dddddd;color:#000000}textarea{resize:vertical;width:98%;height:318px;padding:5px;overflow:auto;background:#1f1f1f;color:#65c115}body{text-align:center;font-family:verdana,sans-serif;background:#252525}td{padding:0px}button{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer}button:hover{background:#0e70a4}.bred{background:#d43535}.bred:hover{background:#931f1f}.bgrn{background:#47c266}.bgrn:hover{background:#5aaf6f}a{color:#1fa3ec;text-decoration:none}.p{float:left;text-align:left}.q{float:right;text-align:right}.r{border-radius:0.3em;padding:2px;margin:6px 2px}</style></head><body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'><div style='text-align:center;color:#eaeaea;'><noscript>Please enable JavaScript<br></noscript>
<h3>Multi-GPIO Controller</h3>
<body>)rawliteral";
static const char PROGMEM IOCONTROL_Action_HTML[] = R"rawliteral(<p><form id=but2 style="display: block;"action=')rawliteral";
static const char PROGMEM IOCONTROL_Name_HTML[] = R"rawliteral('method='get'><button>)rawliteral";
static const char PROGMEM IOCONTROL_Final_HTML[] = R"rawliteral(</button></form></p>)rawliteral";
static const char PROGMEM IOCONTROL_END_HTML[] = R"rawliteral(<p><form id=but3 style="display: block;"action='.'method='get'><button>Main Menu</button></form></p>
<div style='text-align:right;font-size:11px;'><hr/>Logix PCB Multi-GPIO - Open Source Software by Mike Degenaars logixpcb@gmail.com <br>
https://github.com/logichousepcb/Logix_Multifunction <br>
)rawliteral";

String html_new ="<p style=\"text-align:center\"><span style=\"font-family:Arial,Helvetica,sans-serif\"><span style=\"font-size:20px\">";
String html_outline = IOCONTROL_START_HTML;
String action = "OBRelay";
String buttonname = "Onboard Relay - ";
String SwitchName = "";
String SwitchValue = "";
// Main Relay Button
html_outline += IOCONTROL_Action_HTML;
html_outline += action;
html_outline += IOCONTROL_Name_HTML;
html_outline += buttonname;
html_outline += ON_OFF[obiobuff[0]];
html_outline += IOCONTROL_Final_HTML;
// Add reply button loop here
//html_outline += IOCONTROL_Action_HTML;
//html_outline += action;
//html_outline += IOCONTROL_Name_HTML;
//html_outline += buttonname;
//html_outline += ON_OFF[obiobuff[0]];
//html_outline += IOCONTROL_Final_HTML;
//
html_outline += IOCONTROL_END_HTML;
html_outline += "</div></div></body></html>";
server.send(200, "text/html", html_outline);

}

//-----------------------------RESET--------------------
void handleReset() {   // NEED TO ADD ARE YOU SURE?
     mcpfileClear(); // Remove 0*0.json files so a new one is created next reboot
     handleRoot();
}
//-----------------------------RESTART--------------------
void handleRestart() {   // NEED TO ADD ARE YOU SURE?
     ESP.restart();
}

//-----------------------------OBRelay--------------------

void handleOBRelay() {                          // If a POST request is made to URI /LED
  obrelay_control (!obiobuff[0]);    // Change the state of the RELAY
  server.sendHeader("Location","/iocontrol");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

//-----------------------------INFO--------------------
void handleInfo () {

static const char PROGMEM INFO_HTML[] = R"rawliteral( <!DOCTYPE html><html lang="en" class=""><head><meta charset='utf-8'><meta name="viewport" content="width=device-width,initial-scale=1,user-scalable=no" /> <title>)rawliteral";

String html_outline;
html_outline = INFO_HTML;

// Insert title / device name here
html_outline += mainTopicS;

static const char PROGMEM INFO_HTML1[] = R"rawliteral(</title>
    <style>
        div,fieldset,input,select{padding:5px;font-size:1em;}fieldset{background:#4f4f4f;}p{margin:0.5em 0;}input{width:100%;box-sizing:border-box;-webkit-box-sizing:
          border-box;-moz-box-sizing:border-box;background:#dddddd;color:#000000;}input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px;}
          input[type=range]{width:99%;}select{width:100%;background:#dddddd;color:#000000;}textarea{resize:vertical;width:98%;height:318px;padding:5px;overflow:auto;
            background:#1f1f1f;color:#65c115;}body{text-align:center;font-family:verdana,sans-serif;background:#252525;}td{padding:0px;}button{border:0;border-radius:
              0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:
              pointer;}button:hover{background:#0e70a4;}.bred{background:#d43535;}.bred:hover{background:#931f1f;}.bgrn{background:#47c266;}.bgrn:hover{background:#5aaf6f;
                }a{color:#1fa3ec;text-decoration:none;}.p{float:left;text-align:left;}.q{float:right;text-align:right;}.r{border-radius:0.3em;padding:2px;margin:6px 2px;}
    </style>
</head>

<body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'><div style='text-align:center;color:#eaeaea;'<h3>)rawliteral";

  html_outline += INFO_HTML1;
  html_outline += html_outline;
  html_outline += mainTopicS;
  html_outline += "</h3><h4>(";
  html_outline += ipString;
  html_outline += ")";
  static const char PROGMEM INFO_HTML3[] = R"rawliteral(</h4></div><style>td{padding:0px 5px;}</style><div id='i' name='i'></div><div id=but2d style="display: block;"></div><p>
  <table style='width:100%'>)rawliteral";
  String html_footer;
  html_footer = INFO_HTML3;
  html_outline += html_footer;
  String html_newline;

  // LOOP INFO HERE
  html_newline = "<tr><td>SPI ST7735 TFT Selected (does not detect)</td>";
  if (tft_35_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
  html_newline += "</tr><tr><td>SPI ST7789 TFT Selected (does not detect)</td>";
  if (tft_89_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
  html_newline += "</tr><tr><td>Ethernet (does not detect)</td>";
  if (eth_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
  html_newline += "</tr><tr><td>WIFI</td>";
  if (wifi_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
  html_newline += "</tr><tr><td>OLED</td>";
  if (oled_connected){html_newline+= "<td>Found oled at 0x03C</td>";}else{html_newline+= "<td>NOT FOUND</td>";}
 html_newline += "</tr><tr><td>INA260 power sensor at address 0x040</td>";
  if (ina_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
 html_newline += "</tr><tr><td>AHT10 Temperature & Humidity sensor</td>";
  if (aht_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
 html_newline += "</tr><tr><td>ME280 Temperature & Humidity sensor</td>";
  if (bme_connected){html_newline+= "<td>CONNECTED</td>";}else{html_newline+= "<td>NOT CONNECTED</td>";}
  html_outline += html_newline;
  for (int i = 0; i<8; i++) {if (mcpactivebuff[i]==1) {html_newline = "<tr><td>MCP23017 Connected at</td><td>0x02";
    html_newline += i;
    html_newline += "</td></tr>";
    html_outline += html_newline;};
  }
  html_outline += "<tr><td>Firmware version:</td><td>";
  html_outline += CURR_VERS;
  html_outline += "</td></tr>";
  html_outline += "<tr><td>ESP32 Chip Model: </td><td>";
  html_outline += ESP.getChipModel();
  html_outline += "</td></tr>";
  html_outline += "<tr><td>ESP32 Chip Revision: </td><td>";
  html_outline += ESP.getChipRevision();
  html_outline += "</td></tr>";
  html_outline += "<tr><td>ESP32 WiFi MAC: </td><td>";
  html_outline += String(WiFi.macAddress());
  html_outline += "</td></tr>";
  html_outline += "<tr><td>ESP32 Ethernet MAC: </td><td>";
  html_outline += String(ETH.macAddress());
  html_outline += "</td></tr>";
  html_outline += "<tr><td>WIFI SSID: </td><td>";
  html_outline += String(conf.values[0]);
  html_outline += "</td></tr>";


static const char PROGMEM INFO_HTML4[] = R"rawliteral(
  </table><form id=but2 style="display: block;" action='.' method='get'><button>Main Menu</button></form></p>
  <div style='text-align:right;font-size:11px;'><hr/>
  <div style='text-align:right;font-size:11px;'><hr/>Logix PCB Multi-GPIO - Open Source Software by Mike Degenaars logixpcb@gmail.com <br>https://github.com/logichousepcb/Logix_Multifunction <br> 
  <p style="text-align:center"><span style="font-family:Arial,Helvetica,sans-serif"><span style="font-size:11px"> Firmware version:)rawliteral";

  html_footer = INFO_HTML4; 
  html_outline += html_footer;
  html_outline += CURR_VERS;
  html_outline += "</div></div></body></html>";
  server.send(200, "text/html", html_outline);
}
