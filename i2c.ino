/************ I2C ROUTINES ******************************/
 


void setup_i2c() { 
  // Read SDA/SCL assignments from config file
  I2C_SDA = atoi(conf.getValue("sda"));
  I2C_SCL = atoi(conf.getValue("scl"));
  Wire.begin(I2C_SDA,I2C_SCL);    
  scanI2CBus();
}
void scanI2CBus()
{
  byte error, address;
  int nDevices;
 
  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {      
      if (address<16) Serial.print("0"); 
      switch (address) {    // set the specific details for each entiry class
      case 32:mcpactivebuff[0] = 1; 
        Serial.print("<--MCP23017---> found");         
      break;
      case 33:mcpactivebuff[1] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 34:mcpactivebuff[2] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 35:mcpactivebuff[3] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 36:mcpactivebuff[4] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 37:mcpactivebuff[5] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 38:mcpactivebuff[6] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 39:mcpactivebuff[7] = 1; 
        Serial.print("<--MCP23017---> found");  
      break;
      case 60:
        Serial.print("<--OLED---> found");
        oled_connected = true;
        display_connected = true;
      break;
      case 64:
        Serial.print("<--INA260---> found");
        ina_connected = true;
      break;
      case 118:
      case 119:
        Serial.print("<--BME280---> found");
        bme_connected = true;
      break;
      case 56:
      case 57:
        Serial.print("<--AHT10---> found");
        aht_connected = true;
      break;
      default:
      // statements
      break;
      }
      Serial.println(address,HEX);
     
    //  Serial.print(address);
    //  Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.print(nDevices);
    Serial.println(" i2c devices found\n");
  //  Serial.println(mcpactivebuff[0],mcpactivebuff[1],mcpactivebuff[2],mcpactivebuff[3],mcpactivebuff[4],mcpactivebuff[5],mcpactivebuff[6],mcpactivebuff[7]);

 // delay(5000);           // wait 5 seconds for next scan

}
