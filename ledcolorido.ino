// AUTOR: Ângelo Meneguini
// SITE: https://eletronicagaragem.blogspot.com.br
 
#define red 0 // pino conectado ao LED vermelho
#define green 1 // pino conectado ao LED verde
#define blue 9 // pino conectado ao LED azul
 

 
void setup() {
 
pinMode(red, OUTPUT); // define o pino 9 como saída
pinMode(green, OUTPUT); // define o pino 10 como saída
pinMode(blue, OUTPUT); // define o pino 11 como saída
}
 
void loop() {
 

 

digitalWrite(red, 255); // aciona a saída pwm com o valor de v1
digitalWrite(blue, 0); // aciona a saída pwm com o valor de v2
digitalWrite(green, 0); // aciona a saída pwm com o valor de v3
delay(600);
digitalWrite(red, 0); // aciona a saída pwm com o valor de v1
digitalWrite(blue, 255); // aciona a saída pwm com o valor de v2
digitalWrite(green, 0); // aciona a saída pwm com o valor de v3
delay(600);

digitalWrite(red, 0); // aciona a saída pwm com o valor de v1
digitalWrite(blue, 0); // aciona a saída pwm com o valor de v2
digitalWrite(green, 255); // aciona a saída pwm com o valor de v3
delay(600);

}
