void handleConfig() {
  conf.handleFormRequest(&server);
  if (server.hasArg("SAVE")) {
    uint8_t cnt = conf.getCount();
 //   Serial.println("*********** Configuration ************");
    for (uint8_t i = 0; i<cnt; i++) {
//      Serial.print(conf.getName(i));
//      Serial.print(" = ");
//      Serial.println(conf.values[i]);
    }
    if (conf.getBool("switch")) Serial.printf("%s %s %i %5.2f \n",
                                conf.getValue("ssid"),
                                conf.getString("continent").c_str(), 
                                conf.getInt("amount"), 
                                conf.getFloat("float"));
  }
}

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input2: <input type="text" name="input2">
    <input type="submit" value="Submit">
  </form><br>
  <form action="/get">
    input3: <input type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
</body></html>)rawliteral";

void handleHello() {
 server.send(200, "text/plain", "hello from esp32!");
}

const char* serverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input type='submit' value='Update'></form>";

void handleMCPConfig() {
     server.send(200, "text/html", index_html);
     
}


//---------------------------------------------------------
static const char PROGMEM EXAMPLE_HTML[] = R"rawliteral(
<!DOCTYPE html>
<html>
    <head>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
            body {
                color: #434343;
                font-family: "Helvetica Neue",Helvetica,Arial,sans-serif;
                font-size: 14px;
                line-height: 1.42857142857143;
                padding: 20px;
            }

            .container {
                margin: 0 auto;
                max-width: 400px;
            }

            form .field-group {
                box-sizing: border-box;
                clear: both;
                padding: 4px 0;
                position: relative;
                margin: 1px 0;
                width: 100%;
            }

            form .field-group > label {
                color: #757575;
                display: block;
                margin: 0 0 5px 0;
                padding: 5px 0 0;
                position: relative;
                word-wrap: break-word;
            }

            input[type=text] {
                background: #fff;
                border: 1px solid #d0d0d0;
                border-radius: 2px;
                box-sizing: border-box;
                color: #434343;
                font-family: inherit;
                font-size: inherit;
                height: 2.14285714em;
                line-height: 1.4285714285714;
                padding: 4px 5px;
                margin: 0;
                width: 100%;
            }

            input[type=text]:focus {
                border-color: #4C669F;
                outline: 0;
            }

            .button-container {
                box-sizing: border-box;
                clear: both;
                margin: 1px 0 0;
                padding: 4px 0;
                position: relative;
                width: 100%;
            }

            button[type=submit] {
                box-sizing: border-box;
                background: #f5f5f5;
                border: 1px solid #bdbdbd;
                border-radius: 2px;
                color: #434343;
                cursor: pointer;
                display: inline-block;
                font-family: inherit;
                font-size: 14px;
                font-variant: normal;
                font-weight: 400;
                height: 2.14285714em;
                line-height: 1.42857143;
                margin: 0;
                padding: 4px 10px;
                text-decoration: none;
                vertical-align: baseline;
                white-space: nowrap;
            }
        </style>
    </head>
    <body>
        <div class="container">
            <h1 style="text-align: center;">Wifi Details</h1>
            <form method="post" action="/">
                <div class="field-group">
                    <label>SSID</label>
                    <input name="ssid" type="text" length=32>
                </div>
                <div class="field-group">
                    <label>Password</label>
                    <input name="password" type="text" length=64>
                </div>
                <div class="button-container">
                    <button type="submit">Save</button
                </div>
            </form>
        </div>
    </body>
</html>
)rawliteral";

//---------------------------------------------------------
void handleMCPCheck() {
   
  String pin_val;
  pin_val = mcpdoc[0]["chip"].as<String>() + mcpdoc[0]["state"].as<String>();
  pin_val = "<html><head><meta http-equiv=\"refresh\" content=\"2\"> <body bgcolor=\"#ass8e6\">"
            + pin_val + "</body></html>";
            
//  mcpdoc[j]["chip"] 
//  mcpdoc[j]["IO"] = "0000000000000000";   // 0 for output, 1 for input
//    mcpdoc[j]["state"] = "0000000000000000";  // 0 for off, 1 for on
//    mcpdoc[j]["A0"] ="A0********";            // store friendly name of IO for HA
//    mcpdoc[j]["B7"] ="B7********";
  
  server.send(200, "text/html",pin_val);
  server.send(200, "text/html", EXAMPLE_HTML);
}

void handleRoot () {
static const char PROGMEM ROOT_HTML[] = R"rawliteral( 
<h1 style="text-align: center;">Logix PCB Multi-GPIO</h1>
<p style="text-align: center;"><a href="/config">Main Configuration</a></p>
<p style="text-align: center;"><a href="/mcp">Input/Output Assignments</a></p>
<p style="text-align: center;"><a href="/info">Information</a></p>
<p style="text-align: center;"><a href="/reset">Reset All Assignments</a></p>
<p style="text-align: center;"><a href="/contact">Contact/Links</a></p>
<p>&nbsp;</p>
)rawliteral";
server.send(200, "text/html", ROOT_HTML);
}

//---------------------------------------------------------
void handleExample() {
  server.send(200, "text/html", EXAMPLE_HTML);
}
