//Programa: Arduino Painel De Led WS2812
//Alteracoes E Adaptacoes: Arduino E Cia
//Baseado No Programa Exemplo Da Biblioeca Neopixel

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <Avr/Power.H>
#endif

//Pino De Dados Da Matriz De Led
#define PIN 7

//Parametros: Numero De Leds, Pino De Ligacao
Adafruit_NeoPixel Strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);
  Serial.print("Inicio");
  Strip.begin();
  Strip.show();
  //Define O Brilho Dos Leds
  Strip.setBrightness(10);
}

void loop()
{
  /*
    //Acende Os Leds Na Cor Vermelha
    ColorWipe(Strip.Color(255, 0, 0), 20);

    //Acende Os Leds Na Cor Verde
    ColorWipe(Strip.Color(0, 255, 0), 20);

    //Acende Os Leds Na Cor Azul
    ColorWipe(Strip.Color(0, 0, 255), 20);
  */
  //Pisca Os Leds Alternadamente
  // TheaterChase(Strip.Color(127, 127, 127), 50); // White
  // TheaterChase(Strip.Color(127, 0, 0), 50); // Red
  // TheaterChase(Strip.Color(0, 0, 127), 50); // Blue
  //Efeito Arco-Iris

  /*
     for (int I = 0; I < Strip.numPixels(); I++)
     {
        Strip.setPixelColor(I, Strip.Color(127, 127, 0));
        Strip.show();
        delay(50);
    }
  */

  Rainbow(20);
 // desliga_tudo();
}

void liga (int pos , uint32_t cor)
{
  Strip.setPixelColor(pos, cor);
  Strip.show();
}

void desliga (int pos , uint32_t cor)
{
  Strip.setPixelColor(pos, Strip.Color(0, 0, 0));
  Strip.show();
}

void desliga_tudo ()
{
  for (int I = 0; I < Strip.numPixels(); I++)
  {
    Strip.setPixelColor(I, Strip.Color(0, 0, 0));
    Strip.show();
    delay(50);
  }
}



void ColorWipe(uint32_t C, uint8_t Wait)
{
  for (uint16_t I = 0; I < Strip.numPixels(); I++)
  {
    Strip.setPixelColor(I, C);
    Strip.show();
    delay(Wait);
  }
}

void Rainbow(uint8_t Wait)
{
  uint16_t I, J;
  for (J = 0; J < 256; J++) {
    for (I = 0; I < Strip.numPixels(); I++) {
      Strip.setPixelColor(I, Wheel((I + J) & 255));
    }
    Strip.show();
    delay(Wait);
  }
}

void TheaterChase(uint32_t C, uint8_t Wait)
{
  for (int J = 0; J < 10; J++) { //Do 10 Cycles Of Chasing
    for (int Q = 0; Q < 3; Q++) {
      for (int I = 0; I < Strip.numPixels(); I = I + 3) {
        Strip.setPixelColor(I + Q, C);  //Turn Every Third Pixel On
      }
      Strip.show();
      delay(Wait);
      for (int I = 0; I < Strip.numPixels(); I = I + 3)
      {
        Strip.setPixelColor(I + Q, 0);      //Turn Every Third Pixel Off
      }
    }
  }
}

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return Strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return Strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
