//Programa: Temperatura, Pressao e Altitude com BMP280
//Autor: Arduino e Cia

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 sensor_bmp;


void draw()
{
  //Comandos graficos para o display devem ser colocados aqui
   Serial.println("temp");
  Serial.print(sensor_bmp.readTemperature(), 1);
  //Mostra a pressao (em hPa)
   Serial.println("pressao");
  Serial.print(sensor_bmp.readPressure(), 1);
  //Mostra a altitude
  Serial.println("altitude");
  Serial.print(sensor_bmp.readAltitude(1013.25));
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Teste modulo BMP280");
 // delay(3000);

 

  
}

void loop()
{
  //Verifica a conexão do sensor BMP280
  if (!sensor_bmp.begin())
  {
    Serial.println("Sensor não encontrado. Verifique as conexoes!");
    while (1);
  }
    draw();
 
  delay(1000);
}
