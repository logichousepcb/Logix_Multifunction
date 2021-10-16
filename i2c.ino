/**
  I2C bus
 */


void setup_i2c() { 
  // Read SDA/SCL assignments from config file
//  I2C_SDA = atoi(conf.getValue("sda"));
//  I2C_SCL = atoi(conf.getValue("scl"));
  Wire.begin(I2C_SDA,I2C_SCL);    
}
void scanI2CBus()
{
  byte error, address;
  int nDevices;

 // DLINE1="Found..";

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
     
      Serial.print(address,HEX);
      Serial.println("  !");

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
    Serial.println("done\n");

 // delay(5000);           // wait 5 seconds for next scan

}
