#include "DHT.h"
 
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
 
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
Serial.begin(9600);
Serial.println("EADuino - teste DHT22");
dht.begin();
}
 
void loop() {
delay(2000);
float umidade         = dht.readHumidity();
float temperatura     = dht.readTemperature();
float temperaturaF    = dht.readTemperature(true);
float sensacaoTermica = 0;
 
sensacaoTermica = dht.computeHeatIndex(temperaturaF, umidade);
sensacaoTermica = dht.convertFtoC(sensacaoTermica);
 
Serial.print("Umidade: ");
Serial.print(umidade);
Serial.print("%\t");
Serial.print("Temperatura: ");
Serial.print(temperatura);
Serial.print("C\t");
Serial.print("Sensacao termica: ");
Serial.print(sensacaoTermica);
Serial.println("C");
}
