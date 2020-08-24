const byte ledPinVerm = 9; /// rele verm 
const byte ledPinAzul = 8; /// rele azul 

const byte EnergiaVerm = 5;
const byte EnergiaAzul = 6;
volatile byte ledPin;

const byte interruptPinVer = 2;
const byte interruptPinAzu = 3;

volatile byte estado_verm = LOW;
volatile byte estado_azul = LOW;

int buttonState;             // O valor atual da chave no circuito
int lastButtonState = HIGH;   // O valor prévio da chave no circuito
long lastDebounceTime = 0;   // Variável utilizada na temporização
long debounceDelay = 100;     // tempo para estabilizar e minimizar o efeito bouncing
bool flag=true;

volatile long VermTime = millis() ; 
volatile long AzulTime = millis() ; 

void setup() {

  Serial.begin(9600);
  Serial.println("Inicio : ");
  
  pinMode(EnergiaVerm, OUTPUT);
  pinMode(EnergiaAzul, OUTPUT);
  
  //digitalWrite(EnergiaVerm, LOW);
  //digitalWrite(EnergiaAzul, LOW);
  
  pinMode(ledPinVerm, OUTPUT);
  pinMode(ledPinAzul, OUTPUT);

  digitalWrite(ledPinVerm, HIGH);
  digitalWrite(ledPinAzul, HIGH);
  
  pinMode(interruptPinVer, INPUT_PULLUP);
  pinMode(interruptPinAzu, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(interruptPinVer), LigarVerm, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPinAzu), LigarAzul, CHANGE);
}

void loop() {
   //Serial.println(VermTime);
    
  if( (abs(VermTime - AzulTime) > 50) && flag==true )
  {
    flag=false; 
    if (VermTime>AzulTime) 
    {
      Serial.println(AzulTime);
      Serial.println(VermTime);
      Serial.println("Azul vence");
      digitalWrite(ledPinAzul, LOW); /// LIGA RELE AZUL 
      delay(5000);
      digitalWrite(ledPinVerm, HIGH); /// LIGA RELE VERM
      digitalWrite(ledPinAzul, HIGH); /// LIGA RELE VERM

    }
    else 
    {
      Serial.println(AzulTime);
      Serial.println(VermTime);
      Serial.println("Vermelho vence");
      digitalWrite(ledPinVerm, LOW); /// LIGA RELE VERM
      delay(5000);
      digitalWrite(ledPinVerm, HIGH); /// LIGA RELE VERM
      digitalWrite(ledPinAzul, HIGH); /// LIGA RELE VERM
    }
    //digitalWrite(ledPin, estado_verm);
    VermTime=millis();
    AzulTime=millis();
    //interrupts();
    flag=true;
  }
    
  delay(5);
}

void LigarVerm() 
{
  VermTime = millis();  // Reset na variável de temporização
}

void LigarAzul() 
{
  AzulTime = millis();
}
