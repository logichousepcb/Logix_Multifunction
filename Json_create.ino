

void mcprenewJson(int j)

// BUILD NEW CHAR ARRAY TO Json DOC

{
//  for (int j = 0; j <= 7; j++) {
    mcpdoc[j]["chip"] = MCP_CHIPNAME[j];
    mcpdoc[j]["IO"] = "0000000000000000";   // 0 for output, 1 for input
    mcpdoc[j]["state"] = "0000000000000000";  // 0 for off, 1 for on
    mcpdoc[j]["A0"] ="A0********";            // store friendly name of IO for HA
    mcpdoc[j]["A1"] ="A1********";
    mcpdoc[j]["A2"] ="A2********";
    mcpdoc[j]["A3"] ="A3********";
    mcpdoc[j]["A4"] ="A4********";
    mcpdoc[j]["A5"] ="A5********";
    mcpdoc[j]["A6"] ="A6********";
    mcpdoc[j]["A7"] ="A7********";
    mcpdoc[j]["B0"] ="B0********";
    mcpdoc[j]["B1"] ="B1********";
    mcpdoc[j]["B2"] ="B2********";
    mcpdoc[j]["B3"] ="B3********";
    mcpdoc[j]["B4"] ="B4********";
    mcpdoc[j]["B5"] ="B5********";
    mcpdoc[j]["B6"] ="B6********";
    mcpdoc[j]["B7"] ="B7********";
  //  char mybuffer[450];
  //  serializeJson(mcpdoc[j], mybuffer);
  //  Serial.println(mybuffer);  // THIS IS SHOW IN SERIAL THE SENSOR DATA
//  }

}

void mcprenewAllJson () {
     for (int j = 0; j <= 7; j++) {
       mcprenewJson(j);
     }
}
