//------------------------------inicio do programa---------------------------------
//André Kuhn - Automação
//Email: andrekuhn.automacao@gmail.com
//Código para utilizar o novo Dimmer Shield para ser controlado pelos botões.

//Pino digital responsável pelo chaveamento do TRIAC, o novo Dimmer Shield
//pode utilizar os pinos digitais 3, 5 e 6, é necessário alterar o jumper na
//placa. Para utilizar no antigo Dimmer Shield, o pino é o 3.
int load = 3;

//Porcentagem inicial em 0%, variável com valor da 0 a 100.
volatile int power = 0; /// inicia desligado 

//Declarando os pinos de leitura dos botões B0 e B1 do novo Dimmer Shield, o
//botão B0 podem ser A0,A1 e A2, e o botão B1 as entradas A3, A4 e A5. Lembrar
//da alteração dos jumpers na placa. No antigo Dimmer Shield os pinos dos botões
//são fixos, pino 4 e 5.
int botao_0 = A0, botao_1 = A3;
/// A0 = B0 e A3 = B1 

//Inicializando a função de configuração das portas digitais e analógicas
void setup()
{
  //Declarando o pino digital load (digital 3) como saída
  pinMode(load, OUTPUT);

  //Inicializa interrupção. O número zero indica a porta 2 do Arduino,
  //zero_cross_int é a função que será chamada toda vez que pino 2 do Arduino,
  //"subir" (RISING) de valor de 0 para 1.
  attachInterrupt(0, zero_cross_int, RISING);

  //Declarando o pino do botão 0 como entrada
  pinMode(botao_0, INPUT);
  //Declarando o pino do botão 1 como entrada
  pinMode(botao_1, INPUT);

  //Colocando o pino do botão 0 em nível baixo (0 volt)
  digitalWrite(botao_0, LOW);

  //Colocando o pino do botão 1 em nível baixo (0 volt)
  digitalWrite(botao_1, LOW);
  Serial.begin(9600); //init Serial rate
}

//Função responsável por executar a lógica de programação
void loop()
{
  power=5;
  delay(200);
  //Verificando se o botão 0 foi pressionado
  /*
  if (digitalRead(botao_0) == HIGH)
  {
    //Se power (porcentagem) for maior que 0, executa
    if (power > 0)
    {
      //Faz a subtração do power anterior com 10 (decremento de 10)
      power = power - 10;
    }
    delay(200); //Espera de 200 milisegundos
  }

  //Verificando se o botão 1 foi pressionado
  if (digitalRead(botao_1) == HIGH)
  {
    //Se power (porcentagem) for menor que 100, executa
    if (power < 90)
    {
      //Faz a soma do power anterior com 10 (incremento de 10)
      power = power + 10;
      Serial.println("Power");
      Serial.println(power);
      if (power==90)
        power=0;
    }
    
    

    delay(500); //Espera de 200 milisegundos
  }
  */
  
}

//Função executada quando o Dimmer Shield detecta a passagem por zero da tensão
//alternada (senóide)
void zero_cross_int()
{
  //Cálculo do ângulo de disparo: 60Hz -> 8,33ms (1/2 ciclo)
  //(8333us - 8,33us) / 100 = 83 (aproximadamente)

  //O powertime é o tempo que o TRIAC permanescerá desligado quando é detectado
  //o ponto 0 da senóide e varia de 0 a 8300 microsegundos
  int powertime = (82 * (100 - power));

  //Se o powertime for menor ou igual a 820 microsegundos, dar o comando de
  //ligar a lâmpada (carga) - potência total fornecida
  if (powertime <= 820)
  {
    //Liga o pulso do sinal ao TRIAC para que ele passe a conduzir, coloca o
    //pino digital "load" em nível alto
    digitalWrite(load, HIGH);
  }

  //Se o powertime for menor ou igual a 8000 microsegundos, dar o comando de
  //desligar a lâmpada (carga) - potência zero fornecida
  else if (powertime >= 8000)
  {
    //Desliga o pulso do sinal ao TRIAC para que ele não conduza, coloca o pino
    //digital "load" em nível baixo
    digitalWrite(load, LOW);
  }

  //Se o powertime estiver entre 820 microsegundos a 8000 microsegundos
  else if ((powertime > 820) && (powertime < 8000))
  {
    //Mantém o circuito desligado por powertime microssegundos (espera powertime
    //microssegundos)
    delayMicroseconds(powertime);
  
    //Envia sinal ao TRIAC para que ele passe a conduzir, coloca o pino digital
    //"load" em nível alto
    digitalWrite(load, HIGH);
  
    //Espera 8 microssegundos para que o TRIAC perceba o pulso
    delayMicroseconds(8);

    //Desliga o pulso do TRIAC, coloca o pino digital "load" em nível baixo
    digitalWrite(load, LOW);
  }
}
