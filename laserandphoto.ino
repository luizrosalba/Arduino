/*       Project: Laser Tripwire Tutorial      
 *       Written by: Chris Marella                 
 *       Date: January 24, 2018
 *       Version: 1.0   
 *       
  */

//Pin Definitions
const int saida = 8;
const int entrada = 7;


void setup() {
  //Pin Configurations
  //Outputs
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
   pinMode(A1, INPUT);

  //Inputs
  
Serial.begin(9600);
}

void loop() {
  
digitalWrite(7, LOW);
digitalWrite(8,HIGH);

  
  //if/else loop checks if photoresistor is high or low
  //Serial.println(digitalRead(photo));
  /*if(digitalRead(photo)==LOW){
    saida
  }else{
    digitalWrite(LED, LOW);
  }
*/
}
