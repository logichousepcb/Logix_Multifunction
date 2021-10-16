


void mcprenewJson(int j) {
// BUILD NEW CHAR ARRAY TO Json DOC
    mcpdoc[j]["chip"] = MCP_CHIPNAME[j];
    mcpdoc[j]["IO"] = "0000000000000000";  // 1-7 for device class
    mcpdoc[j]["0"] =MCP_CHIPNAME[j]+"-A0";            // store friendly name of IO for HA
    mcpdoc[j]["1"] =MCP_CHIPNAME[j]+"-A1";
    mcpdoc[j]["2"] =MCP_CHIPNAME[j]+"-A2";
    mcpdoc[j]["3"] =MCP_CHIPNAME[j]+"-A3";
    mcpdoc[j]["4"] =MCP_CHIPNAME[j]+"-A4";
    mcpdoc[j]["5"] =MCP_CHIPNAME[j]+"-A5";
    mcpdoc[j]["6"] =MCP_CHIPNAME[j]+"-A6";
    mcpdoc[j]["7"] =MCP_CHIPNAME[j]+"-A7";
    mcpdoc[j]["8"] =MCP_CHIPNAME[j]+"-B0";
    mcpdoc[j]["9"] =MCP_CHIPNAME[j]+"-B1";
    mcpdoc[j]["10"] =MCP_CHIPNAME[j]+"-B2";
    mcpdoc[j]["11"] =MCP_CHIPNAME[j]+"-B3";
    mcpdoc[j]["12"] =MCP_CHIPNAME[j]+"-B4";
    mcpdoc[j]["13"] =MCP_CHIPNAME[j]+"-B5";
    mcpdoc[j]["14"] =MCP_CHIPNAME[j]+"-B6";
    mcpdoc[j]["15"] =MCP_CHIPNAME[j]+"-B7";
}

void mcprenewAllJson () {
     for (int j = 0; j <= 7; j++) {
       mcprenewJson(j);
      }
}
