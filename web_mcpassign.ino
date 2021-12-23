
String html_cleanheader ="<p style=\"text-align: center;\"><span style=\"font-family: Arial,Helvetica,sans-serif;\"><span style=\"font-size: 36px;\">MPC23017 Pin Assignments</span></span></p> <p style=\"text-align: center;\"><span style=\"font-family: Arial, Helvetica, sans-serif; color: #008000;\"><em><span style=\"font-size: 20px;\">Use a friendly name up to 10 characters long.&nbsp; </span></em></span></p> <p style=\"text-align: center;\"><span style=\"font-family: Arial, Helvetica, sans-serif; color: #008000;\"><em><span style=\"font-size: 20px;\">Home assistant will use this for Auto Discovery and MQTT sub-topic.</span></em></span></p>";
String html_header ="<p style=\"text-align: center;\"><span style=\"font-family: Arial,Helvetica,sans-serif;\"><span style=\"font-size: 36px;\">MPC23017 Pin Assignments</span></span></p> <p style=\"text-align: center;\"><span style=\"font-family: Arial, Helvetica, sans-serif; color: #008000;\"><em><span style=\"font-size: 20px;\">Use a friendly name up to 10 characters long.&nbsp; </span></em></span></p> <p style=\"text-align: center;\"><span style=\"font-family: Arial, Helvetica, sans-serif; color: #008000;\"><em><span style=\"font-size: 20px;\">Home assistant will use this for Auto Discovery and MQTT sub-topic.</span></em></span></p>";

//String html_cleanheader = "<html><head> <title>Chip Input Form</title><p style=\"text-align: center;\"><strong>MCP23017 Chip Pin</strong></p> <p style=\"text-align: center;\"><strong>Assignments&nbsp;</strong></p> <p style=\"text-align: center;\"><em>Use a friendly name and </em></p> <p style=\"text-align: center;\"><em>device class which</em></p> <p style=\"text-align: center;\"><em>Home Assistant will receive via MQTT</em></p> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> </head><body>";
//String html_header      = "<html><head> <title>Chip Input Form</title><p style=\"text-align: center;\"><strong>MCP23017 Chip Pin</strong></p> <p style=\"text-align: center;\"><strong>Assignments&nbsp;</strong></p> <p style=\"text-align: center;\"><em>Use a friendly name and </em></p> <p style=\"text-align: center;\"><em>device class which</em></p> <p style=\"text-align: center;\"><em>Home Assistant will receive via MQTT</em></p> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> </head><body>";
String html_footer = "<input type=\"submit\" name=\"clk_action\" value=\"SAVE\"></body></html>";
String html_chipname_front = "<p style=\"text-align: center;\"><strong><span style=\"color: #000080;\">MCP232017 0x";
String html_chipname_rear  ="&nbsp;</span></strong></p>";
String html_pinname_front = "<span style=\"font-size: 28px;\"><form style=\"text-align: center;\" action=\"save\"/\" autocomplete=\"off\"> ";
String html_pinlabel_reara = ": <input type=\"text\" name=\"name"; // PUT PIN NUMBER HERE FOR input# as argument label
String html_pinlabel_rearb = "\" value=";
String html_pinname_rear  = " maxlength=\"10\" size=\"10\">";
String html_chip_inactive = "<p style=\"text-align: center;\"><span style=\"background-color: #ffff00; color: #ff0000;\"><strong>INACTIVE</strong></span></p>";
String html_class_selecta  = "<select name=\"clas";
String html_class_select0  = "\" id=\"class\"> <option value=\"Binary\"";
String html_class_select1  = ">Binary</option> <option value=\"Door\"";
String html_class_select2  = ">Door </option> <option value=\"Window\"";
String html_class_select3  = ">Window</option> <option value=\"Switch\"";
String html_class_select4  = ">Switch</option> <option value=\"Relay\"";
String html_class_select5  = ">Relay </option> <option value=\"iBinary\"";
String html_class_select6  = ">iBinary</option> <option value=\"Relay3\"";
String html_class_select7  = ">Relay3</option> <option value=\"INACTIVE\"";
String html_class_selectc  = ">INACTIVE</option> </select><br>";
String html_class_selected  =" selected";

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

void handlePINAssign (int mcpchip) {    // This routine checks all pins for input/output from Json definition
  
  String pin_val;
  // pin_val = mcpdoc[mcpchip]["chip"].as<String>() + mcpdoc[mcpchip]["state"].as<String>();
 // int a;
  char activepin;
  String pin_io = mcpdoc[mcpchip]["IO"].as<String>();
  String myVariable;

  for (int i = 0; i<16; i++) {
    
    activepin = pin_io.charAt(i); // This is the pin assignment class
    myVariable = mcpdoc[mcpchip][String(i)].as<String>();    // This if where to loop 16 times for pins followed by 2 lines bellow 
/* CREATE A FORM WITH SELECTIONS PREFILLED FROM JSON ASSIGNMENT FILE */   
    html_header += html_pinname_front;  // Start with head plus front of string paragraph
    html_header += mcpdoc[mcpchip]["chip"].as<String>();
    html_header += " PIN ";
    html_header += String(i);
    html_header += html_pinlabel_reara; // add the end of the line before arg label
    html_header += mcpdoc[mcpchip]["chip"].as<String>();
    html_header += String(i);  
    html_header += html_pinlabel_rearb; // add the end of the line after arg label  
    html_header += myVariable;  // add the default value
    html_header += html_pinname_rear; // add the end of the line   
    html_header += html_class_selecta; // chip class selection pre label
    html_header += mcpdoc[mcpchip]["chip"].as<String>();
    html_header += String(i); 
    html_header += html_class_select0; // chip class selection post label
    if (activepin == '0') {myVariable = PIN_CLASS[0];html_header += html_class_selected;};  
    html_header += html_class_select1;
    if (activepin == '1') {myVariable = PIN_CLASS[1];html_header += html_class_selected;};
    html_header += html_class_select2;
    if (activepin == '2') {myVariable = PIN_CLASS[2];html_header += html_class_selected;};
    html_header += html_class_select3;
    if (activepin == '3') {myVariable = PIN_CLASS[3];html_header += html_class_selected;};
    html_header += html_class_select4;
    if (activepin == '4') {myVariable = PIN_CLASS[4];html_header += html_class_selected;};
    html_header += html_class_select5;
    if (activepin == '5') {myVariable = PIN_CLASS[5];html_header += html_class_selected;};
    html_header += html_class_select6;
    if (activepin == '6') {myVariable = PIN_CLASS[6];html_header += html_class_selected;};
    html_header += html_class_select7;
    if (activepin == '7') {myVariable = PIN_CLASS[7];html_header += html_class_selected;};
    html_header += html_class_selectc; // chip class selection post class default
  } 
}



void handleActiveChipAssignPage() {
  
 
  html_header = html_cleanheader; // STart with fresh page each reload
  for (int i = 0; i<8; i++) {
  //  html_header += html_chipname_front;
  //  html_header += MCP_CHIPNAME[i];
//    html_header += html_chipname_rear; 
    if (mcpactivebuff[i] == 1) {            // DO THIS IF CHIP IS ACTIVE
        handlePINAssign (i);
    }
  }
  html_header += html_footer; // finish the page with a footer
  server.send(200, "text/html", html_header);  // serve the page out
}


//-------------------SAVE FROM PIN ASSIGN PAGE-----------------------------
void handleSave() {
  int chipholder;
  String str = "Settings Saved ...\r\n";
  char pinbuf[3];
  String chipfn;
  String pinfn;
  String argfn;
 // String ioholder;
  char chipn;
  int pinholder;
  String ioholder[8] = {"0000000000000000","0000000000000000","0000000000000000","0000000000000000",
                        "0000000000000000","0000000000000000","0000000000000000","0000000000000000"};
  char pinassign;
  int i;                       
 // char* newStates[16];
  Serial.print("number of arguments "); 
  Serial.println(server.args());                    // number of arguments
  chipholder = 0;
  pinassign = '0';
  if (server.args() > 0 ) {
    for ( int i = 0; i < server.args()-1; i++ ) {  // write new names to json for saving
      str += server.argName(i) + " = " + server.arg(i) + "\r\n";
      chipfn = server.argName(i);
      pinfn = server.argName(i);
      chipn = chipfn.charAt(0);
      pinfn.remove(0,7); //Remove 7 characters starting from position 0 to get pin number
// if its a name field do this      
      if (chipn == 'n') { 
       
       chipfn.remove(0,6); // Remove name+02(6) characters starting from position 0 to get chip number and pin numner
       chipfn.remove(1,2); // Remove 2 characters starting from position 1 to get chip number minus pin number
       chipholder = chipfn.toInt(); // convert the text to an int identifying the chip number by a single digit
       pinholder = pinfn.toInt(); // convert the text to an int identifying the pin number
       mcpdoc[chipholder][pinfn] = server.arg(i); // ONLY DO THIS FOR A PIN NAME
      }
// if its a class field do this     
      if (chipn == 'c') {  
       //      if (wantedval == ary[i]) {   // a start for reverse array look up
       argfn = server.arg(i); // get the current argument from the web page
       chipfn.remove(0,6); // Remove name+02(6) characters starting from position 0 to get chip number and pin numner
       chipfn.remove(1,2); // Remove 2 characters starting from position 1 to get chip number minus pin number
       chipholder = chipfn.toInt(); // convert the text to an int identifying the chip number by a single digit
       pinholder=pinfn.toInt();
       // { "Binary", "Door", "Window", "Switch", "Relay", "iBinary", "Relay3", "intRelay"};     
       if (argfn == "Door") {pinassign = '1';}; 
       if (argfn == "Window") {pinassign = '2';}; 
       if (argfn == "Switch") {pinassign = '3';}; 
       if (argfn == "Relay") {pinassign = '4';}; 
       if (argfn == "iBinary") {pinassign = '5';}; 
       if (argfn == "Relay3") {pinassign = '6';}; 
       if (argfn == "INACTIVE") {pinassign = '7';};
       if (argfn == "Binary") {pinassign = '0';}; 
       ioholder[chipholder].setCharAt(pinholder, pinassign);      // place the current web page char value in the string on the proper place    
      }
     //    Serial.println("Arg "+ String(i)+"="+ server.arg(i));
      
    }
   }
 // put all placeholders to memory and save to file
  for (i = 0; i<8; i++) {
   mcpdoc[i]["IO"] = ioholder[i]; 
   writeDataToFile(i);
  }
  handleSavedAssignments ();
  server.send(200, "text/plain", str.c_str());   // this is how you send text to a web page alone
} 
