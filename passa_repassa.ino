const byte ledPinVerm = 9;
const byte ledPinAzul = 8;

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
int flag=0;
void setup() {

   Serial.begin(9600);
  Serial.println("Inicio : ");
  
  pinMode(EnergiaVerm, OUTPUT);
  pinMode(EnergiaAzul, OUTPUT);
  
   digitalWrite(EnergiaVerm, LOW);
   digitalWrite(EnergiaAzul, LOW);
  
  pinMode(ledPinVerm, OUTPUT);
  pinMode(ledPinAzul, OUTPUT);

  digitalWrite(ledPinVerm, LOW);
  digitalWrite(ledPinAzul, LOW);
  
  pinMode(interruptPinVer, INPUT_PULLUP);
  pinMode(interruptPinAzu, INPUT_PULLUP);
 
  attachInterrupt(digitalPinToInterrupt(interruptPinVer), LigarVerm, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPinAzu), LigarAzul, RISING);
}

void loop() {
  if( estado_verm==HIGH || estado_azul==HIGH)
  {
    noInterrupts();
    if (estado_verm==HIGH) Serial.println("Verm");
    if (estado_azul==HIGH) Serial.println("Azul");
    //digitalWrite(ledPin, estado_verm);
    
    estado_verm=LOW;
    estado_azul=LOW;
    interrupts();
  }
  delay(5);
}

void LigarVerm() 
{
  noInterrupts();  /// desativa a possibilidade do azul jogar 
  if (estado_verm==LOW && estado_azul==LOW)
  {
    estado_verm=HIGH;
    ledPin=ledPinVerm;
  }

  /*
  ///debounce
  int reading = digitalRead(interruptPinVer);
  
   // Verifica se houve alterações com o valor prévio da chave
  if (reading != lastButtonState) { // SE VALOR DIFERENTE INICIALIZA CRONOMETRO
    lastDebounceTime = millis();  // Reset na variável de temporização
  }
  
   if ((millis() - lastDebounceTime) > debounceDelay) { /// IGNORA VALORES ABAIXO DE 50 ms
     Serial.println("Valor acima de 100 ms ");
    // Verifica se o estado atual da chave mudou
     Serial.println(reading);
      Serial.println(buttonState);
    if (reading != buttonState) { /// tem que ser diferente do anterior high != low  ignora high high
      Serial.println("A chave mudou do valor anterior ");
      buttonState = reading; /// torna buttonstate = high
      // Troca o estado para ser atribuido para o valor do led
      // Só altera se o novo estado for HIGH
      if (buttonState == HIGH) 
      {
        Serial.println(" Executando ");
        
        Serial.println("Verm");
        delay(2000);
        Serial.println("Verm2");
        interrupts();/// reativa a possibilidade do azul jogar 
      }
    }
  }
 
  // Atualiza a variável com o valor lido na chave
  lastButtonState = LOW; // RETORNA O VALOR PARA LOW 
   
   
  
 // digitalWrite(ledPinVerm, LOW);
 */
}

void LigarAzul() {
  noInterrupts();  /// desativa a possibilidade do azul jogar 
  if (estado_verm==LOW && estado_azul==LOW)
  {
    estado_azul=HIGH;
    ledPin=ledPinAzul;
  }
}
