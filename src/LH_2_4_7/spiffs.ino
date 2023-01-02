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

void mcpfileClear() {
  int i;
  Serial.print("Deleting Files");
  Serial.println("/"+MCP_CHIPNAME[i]+".json");
  DLINE1 = "  FILES";
  DLINE2 = " DELETED";
  DLINE3 = "";
  DLINE7 = " FILES DELETING! ";
  ICONLINE = '8';
  for (i = 0; i<8; i++) {
      SPIFFS.remove("/"+MCP_CHIPNAME[i]+".json");
    }
}


void writeDataToFile(int chipnum) {
  File outfile = SPIFFS.open("/"+MCP_CHIPNAME[chipnum]+".json","w");
  serializeJson(mcpdoc[chipnum], outfile);
 // Serial.println(outfile);
  DLINE1 = "FILE WRITE";
  DLINE2 = "/"+MCP_CHIPNAME[chipnum]+"json";
  DLINE3 = SPIFFS.usedBytes();
  DLINE7 = "WRITTING FILES";
  ICONLINE = '8';
  display_status ();
  delay (100);
  outfile.close();
}

void writeJsonToSerial(int chipnum) {
  serializeJson(mcpdoc[chipnum], Serial);
  Serial.println(); 
}

void mcpfileCheck() {
   int i;
   for (i = 0; i < 8; i++) {
     if (!SPIFFS.exists("/"+MCP_CHIPNAME[i]+".json")) {     // if there is no .json make a fresh one
       Serial.print("Need to create ");
       writeDataToFile(i);
       Serial.println("/"+MCP_CHIPNAME[i]+".json");
 
     }
//     if (!file) {
//     Serial.println("Error opening file for writing");
//     DLINE1 = "FILE OPEN";
//     DLINE2 = "  ERROR";
//     return;
//     }
//     file.close();
  }
}

void printFile(int chipnum) {
  // Open file for reading
  File file = SPIFFS.open("/"+MCP_CHIPNAME[chipnum]+".json");
//  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }
 
  // Extract each characters by one by one
  Serial.println("/"+MCP_CHIPNAME[chipnum]+".json");
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();
 
  // Close the file
  file.close();
}

  
void readDataFromFile(int chipnum) {
  
  File file = SPIFFS.open("/"+MCP_CHIPNAME[chipnum]+".json");
//  Serial.println ("Reading from /"+MCP_CHIPNAME[chipnum]+".json");
  if(file) {
    DeserializationError error = deserializeJson(mcpdoc[chipnum], file);
  }
  
//  if (file) { 
//    Serial.println ("READING FILE CONTENTS");
//    while (file.available()) { //execute while file is available
//    char letter = file.read(); //read next character from file
//    Serial.print(letter); //display character
//    }  
//  }
//  Serial.println (" -END");
  file.close();
}

void readDataFromAll () {
  for (int i = 0; i < 8; i++) {
    readDataFromFile(i);
 //   Serial.println ("Reading from /"+MCP_CHIPNAME[i]+".json");
  } 
}
