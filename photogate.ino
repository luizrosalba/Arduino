
int i;
int moi = 0;  
int laser=7; 
bool inicio = false; 
  uint32_t ts1;
  uint32_t ts2;
void setup()
{
  Serial.begin(9600);
  Serial.println("Leitura : ");
  pinMode(laser, OUTPUT);
  
}

void loop()
{
  digitalWrite(laser, HIGH);
  
  moi = analogRead(0); 
  
  //Serial.println(moi);  // Print an integer  
  
  if (moi < 100 && inicio==false) 
  {
      inicio=true; /// inicializa o cronometro 
      ts1 = micros();
  } 
  if (moi > 100 && inicio==true) /// se tirou o dedo da frente e cronometro inicializou 
  {
      ts2 = micros(); /// para o cronometro 
      Serial.println((ts2-ts1)); /// imprime intervalo 
      inicio = false; /// reseta cronometro 
  }
  
  // print the time interval in microseconds
  
  

  delay(50);
}
