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
    if (conf.getBool("switch")) Serial.printf("%s %s %i %5.2f \n",
                                conf.getValue("ssid"),
                                conf.getString("continent").c_str(), 
                                conf.getInt("amount"), 
                                conf.getFloat("float"));
  }
}

//-----------------------------ROOT--------------------
 
void handleRoot () {
static const char PROGMEM ROOT_HTML[] = R"rawliteral( 
<h1 style="text-align: center;">Logix PCB Multi-GPIO</h1>
<p style="text-align: center;"><a href="/config">Main Configuration</a></p>
<p style="text-align: center;"><a href="/hmcp">Input/Output Assignments</a></p>
<p style="text-align: center;"><a href="/info">Information</a></p>
<p style="text-align: center;"><a href="/reset">Reset All Assignments</a></p>
<p style="text-align: center;"><a href="/contact">Contact/Links</a></p>
<p>&nbsp;</p>
)rawliteral";
server.send(200, "text/html", ROOT_HTML);
}

//-----------------------------RESET--------------------
void handleReset() {   // NEED TO ADD ARE YOU SURE?
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
<p><span style="background-color: #000000; color: #ffcc00;"># LH 2.0&nbsp; @</span></p>
<p><span style="color: #00ffff; background-color: #000000;">FILEWRITTE</span></p>
<p><span style="background-color: #000000; color: #00ffff;">192.168.1.&nbsp;&nbsp;</span></p>
<p><span style="background-color: #000000; color: #00ffff;">1883&nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;</span></p>
<p>&nbsp;</p>
)rawliteral";
server.send(200, "text/html", INFO_HTML);
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
static const char PROGMEM INDEX_HTML[] = R"rawliteral(  
<!DOCTYPE html>
<html>
<head>
<title>MCP Settings</title>
</head>
<p><strong>MCP23017 Friendly Pin Names </strong></p>
<body>
<form method="post" action="/save" >

GPIO 0(A0):<br><input name="A0" type="text" size="16" value="123456" ><br><br>
GPIO 1(A1):<br><input name="A1" type="text" size="16" value="" ><br><br> 
GPIO 2(A2):<br><input name="A2" type="text" size="16" value="" ><br><br>
GPIO 3(A3):<br><input name="A3" type="text" size="16" value="" ><br><br> 
GPIO 4(A4):<br><input name="A4" type="text" size="16" value="" ><br><br>
GPIO 5(A5):<br><input name="A5" type="text" size="16" value="" ><br><br> 
GPIO 6(A6):<br><input name="A6" type="text" size="16" value="" ><br><br>
GPIO 7(A7):<br><input name="A7" type="text" size="16" value="" ><br><br> 
GPIO 8(B0):<br><input name="B0" type="text" size="16" value="" ><br><br>
GPIO 9(B1):<br><input name="B1" type="text" size="16" value="" ><br><br> 
GPIO 10(B2):<br><input name="B2" type="text" size="16" value="" ><br><br>
GPIO 11(B3):<br><input name="B3" type="text" size="16" value="" ><br><br> 
GPIO 12(B4):<br><input name="B4" type="text" size="16" value="" ><br><br>
GPIO 13(B5):<br><input name="B5" type="text" size="16" value="" ><br><br> 
GPIO 14(B6):<br><input name="B6" type="text" size="16" value="" ><br><br>
GPIO 15(B7):<br><input name="B7" type="text" size="16" value="" ><br><br> 
<input type="submit" name="clk_action" value="SAVE">
</form>
</body>
</html>
)rawliteral";

void handleTestRoot() {
  server.send(200, "text/html", INDEX_HTML);
}

void handleMCP() { 
     server.send(200, "text/html", singleLine);
}
//-------------------SAVE FROM PIN ASSIGN PAGE-----------------------------
/*
void handleSave() {
  int chipholder;
  String str = "Settings Saved ...\r\n";
  char pinbuf[3];
  Serial.print("number of arguments "); 
  Serial.println(server.args());                    // number of arguments

  chipholder = 1;
  if (server.args() > 0 ) {
    for ( uint8_t i = 0; i < server.args()-1; i++ ) {
      str += server.argName(i) + " = " + server.arg(i) + "\r\n";
      itoa(i,pinbuf,10);
      Serial.println(mcpdoc[chipholder][pinbuf].as<String>());
    //  mcpdoc[chipholder][pinbuf] = server.arg(i)+"\n";
      mcpdoc[chipholder][pinbuf] = server.arg(i); 
  //    Serial.println("Arg "+ String(i)+"="+ server.argName(i));     
      Serial.println(mcpdoc[chipholder][pinbuf].as<String>());
      Serial.println("Arg "+ String(i)+"="+ server.arg(i));
      
      
    }
  }
  writeDataToFile(chipholder);
  server.send(200, "text/plain", str.c_str());
}
*/
//------------------------------------------------
void handleSingleLine() {
  server.send(200, "text/html", singleLine);
}


void handleContact () {
static const char PROGMEM CONTACT_HTML[] = R"rawliteral( 
<h1 style="text-align: center;">Logix PCB Multi-GPIO</h1>
<p style="text-align: center;">Open Source Software by</p>
<p style="text-align: center;">Mike Degenaars</p>
<p style="text-align: center;"><a href="mailto:logixpcb@gmail.com">logixpcb@gmail.com</a></p>
<p style="text-align: center;"><a href="https://github.com/logichousepcb/Logix_Multifunction">https://github.com/logichousepcb/Logix_Multifunction</a></p>
<p style="text-align: center;">&nbsp;</p>
<p>&nbsp;</p>
)rawliteral";
server.send(200, "text/html", CONTACT_HTML);
}
