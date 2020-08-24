#include <SPI.h>
#include <Wire.h>


#define PIN_RESET 255
#define DC_JUMPER 0

int i;
int moi = 0;  


void setup()
{
  Serial.begin(9600);


}

void loop()
{
  
  moi = analogRead(0); 
  
  
  Serial.print("Moisture: ");
  Serial.print(moi);  // Print an integer  
  
  delay(1000);
}
