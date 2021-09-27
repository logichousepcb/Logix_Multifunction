void setup_mcp() { 
  mcp0.begin();
  mcp1.begin(1);
  mcp2.begin(2);
  mcp3.begin(3); 
  mcp4.begin(4);
  mcp5.begin(5);
  mcp6.begin(6);
  mcp7.begin(7); 
}

/*
void mcp_pin_assign() {
   for (i = 0; i<16; i++) {
    mcp0.pinMode(i, INPUT);
    mcp0.pullUp(i, HIGH);    
    mcp1.pinMode(i, INPUT);
    mcp1.pullUp(i, HIGH);   
 
  }
   for (pina=0;pina<16; pina++) {    // FILL BUFFER WITH CURRENT VALUES OF PINS
    mcp0buff[pina] = mcp0.digitalRead(pina);
    mcp1buff[pina] = mcp1.digitalRead(pina);
    
   }  
} */

int pini;
int pinread[16];

void pincompare() {
//  Serial.println("Reading pins.");
  for (pini=0;pini<16; pini++) {
    pinread[pini] = mcp0.digitalRead(pini);
    if(pinread[pini] != mcp0buff[pini]){
     delay (bouncedelay);
     pinread[pini] = mcp0.digitalRead(pini);
       if(pinread[pini] != mcp0buff[pini]){
         mcp0buff[pini] = pinread[pini];
  //       sensorPub ("0x21",pini,mcp0buff[pini],1);
       }
    }
    pinread[pini] = mcp1.digitalRead(pini);
    if(pinread[pini] != mcp1buff[pini]){
     delay (bouncedelay);
     pinread[pini] = mcp1.digitalRead(pini);
       if(pinread[pini] != mcp1buff[pini]){
         mcp1buff[pini] = pinread[pini];
  //       sensorPub ("0x24",pini,mcp1buff[pini],1);
       }      
    }
  }
  delay (10);
}
