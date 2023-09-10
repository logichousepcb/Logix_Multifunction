


String html_body = "";
String html_header = "";
// String html_original_cleanhead = Conf_Head_HTML;
String html_footer = "</table><input type=\"submit\" class='button basic' name=\"clk_action\" onclick=\"return confirm('Changed pins will generate new ENTITY is Home Assistant. You will need to remove the old ENTITY manually. Update I/O Pins?')\" value=\"SAVE\"></fieldset></body></html>";
//String html_main_menu = "<p><form id=but1 style=\"display: block;\"action='/'method='get'><button>Main Menu</button></form></p>";
String html_pinname_front = "<tr><td style='width:100px'><b><font color='#eaeaea'><form action=\"save\"/\" autocomplete=\"off\"> ";
String html_pinlabel_reara = " <input type=\"text\" name=\"name"; // PUT PIN NUMBER HERE FOR input# as argument label
String html_pinlabel_rearb = "\" value=";
String html_pinname_rear  = " maxlength=\"10\" size=\"12\"> </td><td style='width:100px'>";
String html_chip_inactive = "<b>INACTIVE</b></td>";
String html_class_selecta  = "<select name=\"clas";
String html_class_select0  = "\" id=\"class\"> <option value=\"Binary\"";
String html_class_select1  = ">Binary</option> <option value=\"Door\"";
String html_class_select2  = ">Door </option> <option value=\"Window\"";
String html_class_select3  = ">Window</option> <option value=\"Switch\"";
String html_class_select4  = ">Switch</option> <option value=\"Relay\"";
String html_class_select5  = ">Relay </option> <option value=\"iBinary\"";
String html_class_select6  = ">iBinary</option> <option value=\"Relay3\"";
String html_class_select7  = ">Relay3</option> <option value=\"INACTIVE\"";
String html_class_selectc  = ">INACTIVE</option> </select>";
String html_class_selected  =" selected";

const char* serverIndex = "<form id=but1 style=\"display: block;\"action='update'method='POST' enctype='multipart/form-data'> <input type='file' name='Update'><button>Update</button></form>";


void handlePINAssign (int mcpchip) {    // This routine checks all pins for input/output from Json definition
  
  String pin_val;

  char activepin;
  String pin_io = mcpdoc[mcpchip]["IO"].as<String>();
  String myVariable;
  String html_newline = "";
  
  for (int i = 0; i<16; i++) {
    activepin = pin_io.charAt(i); // This is the pin assignment class
    myVariable = mcpdoc[mcpchip][String(i)].as<String>();    // This if where to loop 16 times for pins followed by 2 lines below 
    // CREATE A FORM WITH SELECTIONS PREFILLED FROM JSON ASSIGNMENT FILE    
    
    html_newline += html_pinname_front;  // Start with head plus front of string paragraph
   
    html_newline += mcpdoc[mcpchip]["chip"].as<String>();
    html_newline += " PIN ";
    html_newline += String(i);
    html_newline += ":</font> </b></td><td style='width:120px'>";
    html_newline += html_pinlabel_reara; // add the end of the line before arg label
    html_newline += mcpdoc[mcpchip]["chip"].as<String>();
    html_newline += String(i);  
    html_newline += html_pinlabel_rearb; // add the end of the line after arg label  
    html_newline += myVariable;  // add the default value
    html_newline += html_pinname_rear; // add the end of the line   
    html_newline += html_class_selecta; // chip class selection pre label
    html_newline += mcpdoc[mcpchip]["chip"].as<String>();
    html_newline += String(i); 
    html_newline += html_class_select0; // chip class selection post label
    if (activepin == '0') {myVariable = PIN_CLASS[0];html_newline += html_class_selected;};  
    html_newline += html_class_select1;
    if (activepin == '1') {myVariable = PIN_CLASS[1];html_newline += html_class_selected;};
    html_newline += html_class_select2;
    if (activepin == '2') {myVariable = PIN_CLASS[2];html_newline += html_class_selected;};
    html_newline += html_class_select3;
    if (activepin == '3') {myVariable = PIN_CLASS[3];html_newline += html_class_selected;};
    html_newline += html_class_select4;
    if (activepin == '4') {myVariable = PIN_CLASS[4];html_newline += html_class_selected;};
    html_newline += html_class_select5;
    if (activepin == '5') {myVariable = PIN_CLASS[5];html_newline += html_class_selected;};
    html_newline += html_class_select6;
    if (activepin == '6') {myVariable = PIN_CLASS[6];html_newline += html_class_selected;};
    html_newline += html_class_select7;
    if (activepin == '7') {myVariable = PIN_CLASS[7];html_newline += html_class_selected;};
    html_newline += html_class_selectc; // chip class selection post class default
    
    html_newline += "</td></tr>";
    html_body += html_newline;
    html_newline = "";
  } 
}
void handleActiveChipAssignPage() {
int j;
  html_body = "";
  html_body = Conf_Head_HTML;
  for (j=0;j<8;j++) {
  
    if (mcpactivebuff[j] == 1) {            // DO THIS IF CHIP IS ACTIVE
        handlePINAssign (j);
   //     html_header +=html_body;
        html_body += html_header;
    }
  }

  html_body += html_footer; 
//  html_header += html_main_menu; // finish the page with a footer
  server.send(200, "text/html", html_body);  // serve the page out
}


//-------------------SAVE FROM PIN ASSIGN PAGE-----------------------------
void handleSave() {
  int chipholder;
  char pinbuf[3];
  String chipfn;
  String pinfn;
  String argfn;
  char chipn;
  int pinholder;
  String ioholder[8] = {"0000000000000000","0000000000000000","0000000000000000","0000000000000000",
                        "0000000000000000","0000000000000000","0000000000000000","0000000000000000"};
  char pinassign;
  int i;                       
  Serial.print("number of arguments "); 
  Serial.println(server.args());                    // number of arguments
  chipholder = 0;
  pinassign = '0';
  if (server.args() > 0 ) {
    for ( int i = 0; i < server.args()-1; i++ ) {  // write new names to json for saving
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
       if (argfn == "Binary") {pinassign = '0';}; 
       if (argfn == "INACTIVE") {pinassign = '7';};
       ioholder[chipholder].setCharAt(pinholder, pinassign);      // place the current web page char value in the string on the proper place    
      }
     }
   }
 // put all placeholders to memory and save to file
  for (i = 0; i<8; i++) {
   mcpdoc[i]["IO"] = ioholder[i]; 
   writeDataToFile(i);
   //delay(1000);
  }
 
  handleRoot ();
  
} 
