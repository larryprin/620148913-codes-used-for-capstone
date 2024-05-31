#include <SoftwareSerial.h>
#include <Servo.h>
#define RX 2 
#define TX 3 

Servo myservo;
Servo myservo2;

SoftwareSerial hc12(RX, TX);

int pos=0;
int pos2=0;

String numberString, numberString2, numberString3;
String receivedData;
void setup() {
  myservo.attach(8);
  myservo2.attach(9);
Serial.begin(9600);
hc12.begin(9600);
myservo.write(0);delay(15);
  
myservo2.write(20);delay(15);
}

void loop() {
  // Read data from the HC-12
  if (hc12.available()) {
    String receivedData = "";

    // Read until a newline character
    while (hc12.available()) {
      char incomingByte = hc12.read();
      receivedData += incomingByte;
      if (incomingByte == '\n') 
      
      break;parsedata(receivedData);
    }

    // Print the received data to the Serial Monito
  }
}


void parsedata(String Data)
{
  String part1;
  String part2;
  
  part1 = Data.substring(0, Data.indexOf(" "));
  part2 = Data.substring(Data.indexOf(" ") + 1, Data.indexOf("\n"));
 if(part1.equalsIgnoreCase("X"))
  {
    float given = part2.toFloat();
    int intValue = round(given);
    myservo.write(intValue);
    delay(500);
   Serial.print(intValue);
   Serial.println(" a");
   } 
 else if(part1.equalsIgnoreCase("Y")) 
   {
   float given2 = part2.toFloat();
int intValue2 = round(given2);
    myservo.write(intValue2);
    delay(500);
    if (intValue2 > 20){
      intValue2 = 20;
    }
   Serial.print(intValue2); 
    Serial.println(" b");
    }
    }
