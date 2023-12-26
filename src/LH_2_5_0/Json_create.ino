


void mcprenewJson(int j) {
// BUILD NEW CHAR ARRAY TO Json DOC
    mcpdoc[j]["chip"] = MCP_CHIPNAME[j];
    mcpdoc[j]["IO"] = "7777777777777777";  // 1-7 for device class
    mcpdoc[j]["0"] =unique_id+MCP_CHIPNAME[j]+"-A0";            // store friendly name of IO for HA
    mcpdoc[j]["1"] =unique_id+MCP_CHIPNAME[j]+"-A1";
    mcpdoc[j]["2"] =unique_id+MCP_CHIPNAME[j]+"-A2";
    mcpdoc[j]["3"] =unique_id+MCP_CHIPNAME[j]+"-A3";
    mcpdoc[j]["4"] =unique_id+MCP_CHIPNAME[j]+"-A4";
    mcpdoc[j]["5"] =unique_id+MCP_CHIPNAME[j]+"-A5";
    mcpdoc[j]["6"] =unique_id+MCP_CHIPNAME[j]+"-A6";
    mcpdoc[j]["7"] =unique_id+MCP_CHIPNAME[j]+"-A7";
    mcpdoc[j]["8"] =unique_id+MCP_CHIPNAME[j]+"-B0";
    mcpdoc[j]["9"] =unique_id+MCP_CHIPNAME[j]+"-B1";
    mcpdoc[j]["10"] =unique_id+MCP_CHIPNAME[j]+"-B2";
    mcpdoc[j]["11"] =unique_id+MCP_CHIPNAME[j]+"-B3";
    mcpdoc[j]["12"] =unique_id+MCP_CHIPNAME[j]+"-B4";
    mcpdoc[j]["13"] =unique_id+MCP_CHIPNAME[j]+"-B5";
    mcpdoc[j]["14"] =unique_id+MCP_CHIPNAME[j]+"-B6";
    mcpdoc[j]["15"] =unique_id+MCP_CHIPNAME[j]+"-B7";
}

void mcprenewAllJson () {
     for (int j = 0; j <= 7; j++) {
       mcprenewJson(j);
      }
}
