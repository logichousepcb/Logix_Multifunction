void listFilesInDir(File dir, int numTabs = 1);

void setupSPIFF() {
    Serial.println(F("Inizializing FS..."));
    if (SPIFFS.begin()){
        Serial.println(F("SPIFFS mounted correctly."));
    }else{
        Serial.println(F("!An error occurred during SPIFFS mounting"));
    }

    // Get all information of SPIFFS
 
    unsigned int totalBytes = SPIFFS.totalBytes();
    unsigned int usedBytes = SPIFFS.usedBytes();
 
    Serial.println("===== File system info =====");
 
    Serial.print("Total space:      ");
    Serial.print(totalBytes);
    Serial.println("byte");
 
    Serial.print("Total space used: ");
    Serial.print(usedBytes);
    Serial.println("byte");
 
    Serial.println();
 
    // Open dir folder
    File dir = SPIFFS.open("/");
    // List file at root
    listFilesInDir(dir);
}

void listFilesInDir(File dir, int numTabs) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files in the folder
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      listFilesInDir(entry, numTabs + 1);
    } else {
      // display zise for file, nothing for directory
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void mcpfileRenew() {
  SPIFFS.remove("/mcp23017.cfg");
}

void mcpfileCheck() {
  File file = SPIFFS.open("/mcp23017.cfg", "w");
  if (!SPIFFS.exists("/mcp23017.cfg")) {     // if there is no mcp23017.cfg file make a fresh one
    
  }
  if (!file) {
    Serial.println("Error opening file for writing");
    DLINE1 = "FILEOPENERROR";
    return;
  }
 // mcprenewJson(0);  // JUST FOR TESTING __ REMOVE THIS
  
  char filebuffer[450];
  serializeJson(mcpdoc[0], filebuffer);
  
  int bytesWritten = file.print(filebuffer);
  if (bytesWritten > 0) {
    Serial.println("File was written");
    Serial.println(bytesWritten);
    DLINE1 = "FILEWRITTEN";
 
  } else {
    Serial.println("File write failed");
     DLINE1 = "FILEWRITEERROR";
  }
 
  file.close();
}
   
  
void readDataFromFile(const char* filename) {
  File file = SPIFFS.open(filename);
  if(file) {
    StaticJsonDocument<600> doc;
    DeserializationError error = deserializeJson(doc, file);
    String chip = doc["chip"].as<String>();
    String io = doc["IO"].as<String>();
    String state = doc["state"].as<String>();
    String ao = doc["A0"].as<String>();
    Serial.println (chip);
    Serial.println(io);
    Serial.println (state);
    Serial.println(ao);
  }
  file.close();
}

void writeDataToFile(const char* filename) {
  File outfile = SPIFFS.open(filename,"w");
  StaticJsonDocument<600> doc;
  doc["data"] = "michael";
  if(serializeJson(doc, outfile)==0) {
    Serial.println("Failed to write to SPIFFS file");
  } else {
    Serial.println("Success!");
  }
  outfile.close();
}

void createDataFile(int m) {
  File outfile = SPIFFS.open(MCP_FILENAME[m],"w");
  StaticJsonDocument<600> doc;
  doc["chip"] = MCP_FILENAME[m];
  doc["IO"] = "0000000000000000";   // 0 for output, 1 for input
  doc["state"] = "0000000000000000";  // 0 for off, 1 for on
  doc["A0"] ="A0********";            // store friendly name of IO for HA
  doc["A1"] ="A1********";
  doc["A2"] ="A2********";
  doc["A3"] ="A3********";
  doc["A4"] ="A4********";
  doc["A5"] ="A5********";
  doc["A6"] ="A6********";
  doc["A7"] ="A7********";
  doc["B0"] ="B0********";
  doc["B1"] ="B1********";
  doc["B2"] ="B2********";
  doc["B3"] ="B3********";
  doc["B4"] ="B4********";
  doc["B5"] ="B5********";
  doc["B6"] ="B6********";
  doc["B7"] ="B7********";

  
  if(serializeJson(doc, outfile)==0) {
    Serial.println("Failed to write to SPIFFS file");
  } else {
    Serial.println("Success!");
  }
  outfile.close();
} 
