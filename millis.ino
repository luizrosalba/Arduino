/* 
    Blink without Delay, example here: arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

// constants won't change. Used here to set a pin number :
const int ledPin =  13;      // the number of the LED pin

// Variables will change :
//int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 3000;           // interval at which to blink (milliseconds)
 unsigned long currentMillis;
 
void setup() {
  // set the digital pin as output:
 // pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
   Serial.println("inicio");
  
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
 
  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  
  currentMillis = millis();
  
  Serial.println(currentMillis - previousMillis);
   
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

  
  }


  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

   Serial.println(previousMillis);
   Serial.println(currentMillis);
  }
  
  
}
