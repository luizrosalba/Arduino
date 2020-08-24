#include <SoftwareSerial.h>
#define LED_PIN 3

/// use um resistor de 100 ohms ou não vai funcionar 
/// mude a saida da serial para 9600 senao nao vai funcinar 
SoftwareSerial mySerial(7, 8); // RX, TX  
// Connect HM10      Arduino Uno
//     Pin 1/TXD          Pin 7
//     Pin 2/RXD          Pin 8

void setup() {  
  pinMode(LED_PIN, OUTPUT);    /// 23 vermelho 
  Serial.begin(9600);
  // If the baudrate of the HM-10 module has been updated,
  // you may need to change 9600 by another value
  // Once you have found the correct baudrate,
  // you can update it using AT+BAUDx command 
  // e.g. AT+BAUD0 for 9600 bauds
  mySerial.begin(9600);
}

void loop() {  


   
  int c;
  

  
  if (mySerial.available()) {
    c = mySerial.read();  
    Serial.println("Got input:");
    if (c != 0)
    {
      // Non-zero input means "turn on LED".
      Serial.println("  on");
      digitalWrite(LED_PIN, HIGH);
    }
    else
    {
      // Input value zero means "turn off LED".
      Serial.println("off");
      digitalWrite(LED_PIN, LOW);
    }  
  }
 
}
