    /**
 * 
 * @todo
 *  - move strings to flash (less RAM consumption)
 *  - fix deprecated convertation form string to char* startAsTag
 *  - give example description
 */
#include <SPI.h>
#include "DW1000Ranging.h"
#include <SoftwareSerial.h>
#define RX 3
#define TX 4

const int ledPin1 = 5;
const int ledPin2 = 6;
const int ledPin3 = 7;
float dis1;
float dis2;
float dis3;
float lastx, lasty;

float x1 = 0.00, y1 = 0.00,x2 = 0.00 ,y2 = 15.00,x3 = 10.00, y3 = 15.00;

String receivedData;

SoftwareSerial hc12(RX,TX);
// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

void setup() {
  Serial.begin(115200);
hc12.begin(9600);
  delay(1000);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  //init the configuration
  DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  DW1000Ranging.attachNewDevice(newDevice);
  DW1000Ranging.attachInactiveDevice(inactiveDevice);
  //Enable the filter to smooth the distance
  //DW1000Ranging.useRangeFilter(true);
  
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY, false);

}

void loop() {
  
  DW1000Ranging.loop();
  
} 

void newRange() {
 // Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress());
  //Serial.print(" "); Serial.println(DW1000Ranging.getDistantDevice()->getRange());
 // Serial.print(" RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
 if (DW1000Ranging.getDistantDevice()->getShortAddress()== 6022)
 {
  dis1 = DW1000Ranging.getDistantDevice()->getRange();
  Serial.print("A1: "); Serial.println(dis1);
  digitalWrite(ledPin1, HIGH);
  }
else if (DW1000Ranging.getDistantDevice()->getShortAddress()== 6018)
 {
  dis2 = DW1000Ranging.getDistantDevice()->getRange();
  Serial.print("A2: "); Serial.println(dis2);
  digitalWrite(ledPin2, HIGH);
  }
else if (DW1000Ranging.getDistantDevice()->getShortAddress()== 6032)
 {
  dis3 = DW1000Ranging.getDistantDevice()->getRange();
  Serial.print("A3: "); Serial.println(dis3);
  digitalWrite(ledPin3, HIGH);
  }
float x = ((dis1 * dis1)-(dis3 * dis3) + (x3 * x3) + (y3 * y3) - (2 * y1 * y3))/(2 * x3);
float y = ((dis1 * dis1) - (dis2 * dis2) + (y2 * y2))/(2 * y2);

/*
if (x > lastx) {
    // Print the letter 'A' when the variable increases
    hc12.print('A');
    
    // Update lastVariable to the current value of variable
    lastx = x;
    //delay(100);
//Serial.print(x); Serial.print(","); Serial.println(y);
}
if (x < lastx) {
    // Print the letter 'A' when the variable increases
    hc12.print('B');
    
    // Update lastVariable to the current value of variable
    lastx = x;
    //delay(100);
//Serial.print(x); Serial.print(","); Serial.println(y);
}
if (y > lasty) {
    // Print the letter 'A' when the variable increases
    hc12.print('C');
    
    // Update lastVariable to the current value of variable
    lasty = y;
    //delay(100);
//Serial.print(x); Serial.print(","); Serial.println(y);
}
if (y < lasty) {
    // Print the letter 'A' when the variable increases
    hc12.print('D');
    
    // Update lastVariable to the current value of variable
    lasty = y;
   // delay(100);
//Serial.print(x); Serial.print(","); Serial.println(y); 
}*/
  hc12.print("X,"); hc12.println(x);
  hc12.print("Y,"); hc12.println(y);
}

void newDevice(DW1000Device* device) {
  Serial.print("ranging init; 1 device added ! -> ");
  Serial.print(" short:");
  Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device* device) {
  Serial.print("delete inactive device: ");
  Serial.println(device->getShortAddress(), HEX);
}
  
