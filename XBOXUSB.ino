/*
  Example sketch for the Xbox 360 USB library - developed by Kristian Lauszus
  For more information visit my blog: http://blog.tkjelectronics.dk/ or
  send me an e-mail:  kristianl@tkjelectronics.com
*/

#include <XBOXUSB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXUSB Xbox(&Usb);

void setup() {
  Serial.begin(9600);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(("\r\nXBOX USB Library Started"));

  
  pinMode(2, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
  pinMode(3, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
  pinMode(4, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
  pinMode(5, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...

  
}
void loop() {

   
  Usb.Task();


if (Xbox.getButtonClick(RIGHT)) {
    
    Serial.println(F("Right"));
    digitalWrite(2, HIGH);  // Diz que o pino 12 do arduino está Ligado. Logo LED ON
    ;
}

if (Xbox.getButtonClick(UP)) {
    
    Serial.println(F("UP"));
    digitalWrite(2, LOW);  // Diz que o pino 12 do arduino está Ligado. Logo LED ON
    }


if (Xbox.getButtonClick(LEFT)) {
    
    Serial.println(F("Left"));
    digitalWrite(3, HIGH);  // Diz que o pino 12 do arduino está Ligado. Logo LED ON
    }

    if (Xbox.getButtonClick(DOWN)) {
    
    Serial.println(F("DOWN"));
    digitalWrite(3, LOW);  // Diz que o pino 12 do arduino está Ligado. Logo LED ON
    }



delay(1);
}





/*
  if (Xbox.Xbox360Connected) {
  if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
    Serial.print("L2: ");
    Serial.print(Xbox.getButtonPress(L2));
    Serial.print("\tR2: ");
    Serial.println(Xbox.getButtonPress(R2));
    Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
  } else
    Xbox.setRumbleOn(0, 0);

  if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
      Serial.print(F("LeftHatX: "));
      Serial.print(Xbox.getAnalogHat(LeftHatX));
      Serial.print("\t");
    }
    if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
      Serial.print(F("LeftHatY: "));
      Serial.print(Xbox.getAnalogHat(LeftHatY));
      Serial.print("\t");
    }
    if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
      Serial.print(F("RightHatX: "));
      Serial.print(Xbox.getAnalogHat(RightHatX));
      Serial.print("\t");
    }
    if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      Serial.print(F("RightHatY: "));
      Serial.print(Xbox.getAnalogHat(RightHatY));
    }
    Serial.println();
  }

  if (Xbox.getButtonClick(UP)) {
    Xbox.setLedOn(LED1);
    Serial.println(F("Up"));
  }
  if (Xbox.getButtonClick(DOWN)) {
    Xbox.setLedOn(LED4);
    Serial.println(F("Down"));
  }
  if (Xbox.getButtonClick(LEFT)) {
    Xbox.setLedOn(LED3);
    Serial.println(F("Left"));
  }
  if (Xbox.getButtonClick(RIGHT)) {
    Xbox.setLedOn(LED2);
    Serial.println(F("Right"));
  }

  if (Xbox.getButtonClick(START)) {
    Xbox.setLedMode(ALTERNATING);
    Serial.println(F("Start"));
  }
  if (Xbox.getButtonClick(BACK)) {
    Xbox.setLedBlink(ALL);
    Serial.println(F("Back"));
  }
  if (Xbox.getButtonClick(L3))
    Serial.println(F("L3"));
  if (Xbox.getButtonClick(R3))
    Serial.println(F("R3"));

  if (Xbox.getButtonClick(L1))
    Serial.println(F("L1"));
  if (Xbox.getButtonClick(R1))
    Serial.println(F("R1"));
  if (Xbox.getButtonClick(XBOX)) {
    Xbox.setLedMode(ROTATING);
    Serial.println(F("Xbox"));
  }

  if (Xbox.getButtonClick(A))
    Serial.println(F("A"));
  if (Xbox.getButtonClick(B))
    Serial.println(F("B"));
  if (Xbox.getButtonClick(X))
    Serial.println(F("X"));
  if (Xbox.getButtonClick(Y))
    Serial.println(F("Y"));
*/
