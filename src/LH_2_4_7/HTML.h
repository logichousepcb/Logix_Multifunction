// LETS BUILD A UNIVERSAL HEAD TYPE
static const char PROGMEM Conf_Head_HTML[] = R"rawliteral( 
<!DOCTYPE html><html lang="en"class=""><head><meta charset='utf-8'>
  <meta name="viewport"content="width=device-width,initial-scale=1,user-scalable=no"/>
  <title>Multi-GPIO Controller</title>
  <style>
    div,fieldset,input,select{padding:5px;font-size:1em;}fieldset{background:#4f4f4f;}p{margin:0.5em 0;}input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;background:#dddddd;color:#000000;}input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px;}input[type=range]{width:99%;}select{width:100%;background:#dddddd;color:#000000;}textarea{resize:vertical;width:98%;height:318px;padding:5px;overflow:auto;background:#1f1f1f;color:#65c115;}body{text-align:center;font-family:verdana,sans-serif;background:#252525;}td{padding:0px;}button{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}button:hover{background:#0e70a4;}.basic{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}
    .bred{background:#d43535;}.bred:hover{background:#931f1f;}.bgrn{background:#47c266;}.bgrn:hover{background:#5aaf6f;}a{color:#1fa3ec;text-decoration:none;}.p{float:left;text-align:left;}.q{float:right;text-align:right;}.r{border-radius:0.3em;padding:2px;margin:6px 2px;}
  </style>
  </head><body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'>

<div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'>
  <div style='text-align:center;color:#eaeaea;'>
<body>
<h3>MPC23017 Pin Assignments</h3>
<h4>Use a friendly name up to 10 characters long. <br> Home assistant will use this for <br>Auto Discovery and MQTT sub-topic.</h4>
</div><fieldset>
            <legend><b>&nbsp;MPC23017 Pin Assignments&nbsp;</b></legend>
            <table style='width:100%'> )rawliteral";

// LETS BUILD A UNIVERSAL HEAD TYPE
static const char PROGMEM Conf_Front_HTML[] = R"rawliteral( 
<!DOCTYPE html><html lang="en"class=""><head><meta charset='utf-8'>
  <meta name="viewport"content="width=device-width,initial-scale=1,user-scalable=no"/>
  <title>Multi-GPIO Controller</title>
  <style>
    div,fieldset,input,select{padding:5px;font-size:1em;}fieldset{background:#4f4f4f;}p{margin:0.5em 0;}input{width:100%;box-sizing:border-box;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;background:#dddddd;color:#000000;}input[type=checkbox],input[type=radio]{width:1em;margin-right:6px;vertical-align:-1px;}input[type=range]{width:99%;}select{width:100%;background:#dddddd;color:#000000;}textarea{resize:vertical;width:98%;height:318px;padding:5px;overflow:auto;background:#1f1f1f;color:#65c115;}body{text-align:center;font-family:verdana,sans-serif;background:#252525;}td{padding:0px;}button{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}button:hover{background:#0e70a4;}.basic{border:0;border-radius:0.3rem;background:#1fa3ec;color:#faffff;line-height:2.4rem;font-size:1.2rem;width:100%;-webkit-transition-duration:0.4s;transition-duration:0.4s;cursor:pointer;}
    .bred{background:#d43535;}.bred:hover{background:#931f1f;}.bgrn{background:#47c266;}.bgrn:hover{background:#5aaf6f;}a{color:#1fa3ec;text-decoration:none;}.p{float:left;text-align:left;}.q{float:right;text-align:right;}.r{border-radius:0.3em;padding:2px;margin:6px 2px;}
  </style>
  </head><body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'>

<div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'>
  <div style='text-align:center;color:#eaeaea;'> )rawliteral";
  
// LETS BUILD A UNIVERSAL BODY TYPE
static const char PROGMEM Conf_Body_HTML[] = R"rawliteral(
<body>
</style></head><body><div style='text-align:left;display:inline-block;color:#eaeaea;min-width:340px;'><div style='text-align:center;color:#eaeaea;'>  
<fieldset><legend><b>&nbsp;Firmware Update</b>&nbsp;</b></legend>
<table style='width:340px'>)rawliteral";

// LETS BUILD A UNIVERSAL FOOTER TYPE
static const char PROGMEM Conf_Rear_HTML[] = R"rawliteral(
</fieldset>
</form><form id="but2" style="display: block;" action="." method="get"><button>Main Menu</button>
</form></div>
</div>
<div style='text-align:right;font-size:11px;'><hr/>Logix PCB Multi-GPIO - Open Source Software by Mike Degenaars logixpcb@gmail.com <br>https://github.com/logichousepcb/Logix_Multifunction <br> 

)rawliteral";
// LETS BUILD A UNIVERSAL MAIN MENU TYPE
static const char PROGMEM Main_Menu_Button_HTML[] = R"rawliteral(<p><form id=but2 style="display: block;"action=')rawliteral";
// LETS BUILD A UPDATE LINE TYPE
const char* UpdateserverIndex = "<form method='POST' action='/update' enctype='multipart/form-data'><input type='file' name='update'><input class='bgrn' type='submit' value='Update'></form>";
