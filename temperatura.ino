void setup() {

pinMode(12, OUTPUT); //Declara que o pino 12 do arduino é de Saída. Vai mandar dados, energia...
}

void loop() {

digitalWrite(12, HIGH);  // Diz que o pino 12 do arduino está Ligado. Logo LED ON
delay(1000); // Espera por 1s
println("nada") ; 
digitalWrite(12, LOW); //  Diz que o pino 12 do arduino está Desligado. Logo: LED OFF
delay(1000); // Espera por 1s
}
