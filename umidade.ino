///https://portal.vidadesilicio.com.br/sensor-de-umidade-do-solo-higrometro/ 
int sensor_pin = A0;

int output_value ;

void setup() {

   Serial.begin(9600);

   Serial.println("Reading From the Sensor ...");

   
   delay(2000);

   }

void loop() {
   //Serial.print("valor cru  : ");
   output_value= analogRead(sensor_pin);
   Serial.print(output_value);

   output_value = map(output_value,0,1023,0,100);

  //Serial.print(" valor normalizado  : ");
   Serial.print("  ");
   Serial.print(output_value);

   Serial.println("%");

   delay(5000);

   }
