// INA 260 voltage monitor **************************************************

void setup_ina260() {
  // Serial.println("Adafruit INA260 Test");
  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    delay (100);
  }
}

void read_ina260() {
  Serial.print("Current: ");
  Serial.print(ina260.readCurrent());
  Serial.println(" mA");

  Serial.print("Bus Voltage: ");
  Serial.print(ina260.readBusVoltage());
  Serial.println(" mV");

  Serial.print("Power: ");
  Serial.print(ina260.readPower());
  Serial.println(" mW");

  Serial.println();
 // delay(1000);
}

// AHT10 temperature/humidity sensor **************************************************


// BME 280 temperature/humidity sensor **************************************************
void setup_bme(){
  delay(2000);
  if (!bme.begin(0x76)) {
    Serial.println("Could not setup a valid BME280 sensor, check wiring!");
    bme_connected = false;
    // optional have this define whether BME present or not    
 // while (1);
  }    
}

// long lastMsgb = 0;


void BME_temp() {
    char temptopicb[50];
    // Temperature in Celsius
    // temperature = bme.readTemperature();   
    // Uncomment the next line to set temperature in Fahrenheit 
    // (and comment the previous temperature line)
    temperature = 1.8 * bme.readTemperature() + 32; // Temperature in Fahrenheit
    // Convert the value to a char array
    char tempString[8];
    dtostrf(temperature, 1, 2, tempString);
    Serial.print("Temperature: ");
    Serial.println(tempString);
 //   strcpy(temptopicb,USER_MQTT_DISCOVERY_PREFIX);
 //   strcat(temptopicb,"/sensor/");
 //   strcat(temptopicb,USER_MQTT_CLIENT_NAME);
 //   strcat(temptopicb,"/temperature");
 //   client.publish(temptopicb,tempString);
    
    humidity = bme.readHumidity();
    // Convert the value to a char array
    char humString[8];
    dtostrf(humidity, 1, 2, humString);
    Serial.print("Humidity: ");
    Serial.println(humString);
 //   strcpy(temptopicb,USER_MQTT_DISCOVERY_PREFIX);
 //   strcat(temptopicb,"/sensor/");
 //   strcat(temptopicb,USER_MQTT_CLIENT_NAME);
 //   strcat(temptopicb,"/humidity");
 //   client.publish(temptopicb, humString);
   
}
