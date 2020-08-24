  /*Projeto Plantação automatizada de Morango
  /// Universidade Estácio de Sá
  /// Autor : Prof. Dr. Luiz Fernando Rosalba
*/
/// TODO :
/// Ler as informações do dia para saber se a luz caiu
/// calcular o tempo necessario de luz de acordo com a luz recebida
/// e a estimada

/// parte de agua
///



#include <Wire.h> //BH1750 IIC Mode
#include <math.h>
#include <ThreeWire.h> //INCLUSÃO DA BIBLIOTECA
#include <RtcDS1302.h> //INCLUSÃO DA BIBLIOTECA
#include <dht11.h>

#include <SPI.h>
#include <SdFat.h>


dht11 DHT11;
#define DHTPIN 8 // o sensor dht11 foi conectado ao pino A2 
//#define DHTTYPE DHT11
//dht dht(DHTPIN, DHTTYPE);

bool imprime_serial = false ;
bool imprime_sensores = true ;

const int chipSelect = 6; /// cartao SD

int BH1750address = 0x23; //setting i2c address
byte buff[2];

ThreeWire myWire(4, 5, 7); //OBJETO DO TIPO ThreeWire
RtcDS1302<ThreeWire> Rtc(myWire); //OBJETO DO TIPO RtcDS1302
RtcDateTime compiled;

int tempo_atividade=0;
//Porta ligada ao pino IN1 do modulo
//int porta_rele1 = 2;

/// dimmer shield

//Pino digital responsável pelo chaveamento do TRIAC, o novo Dimmer Shield
//pode utilizar os pinos digitais 3, 5 e 6, é necessário alterar o jumper na
//placa. Para utilizar no antigo Dimmer Shield, o pino é o 3.
int load = 3;
//Porcentagem inicial em 0%, variável com valor da 0 a 100.
volatile int power = 5; /// inicia desligado
//Declarando os pinos de leitura dos botões B0 e B1 do novo Dimmer Shield, o
//botão B0 podem ser A0,A1 e A2, e o botão B1 as entradas A3, A4 e A5. Lembrar
//da alteração dos jumpers na placa. No antigo Dimmer Shield os pinos dos botões
//são fixos, pino 4 e 5.
int botao_0 = A0, botao_1 = A3;
/// A0 = B0 e A3 = B1

int status_manutencao=0;

/*
  /// Sensor de umidade do solo :
*/

//int sensor_umidade = A1; /// comentei para reduzir espaço variaveis globais 


int umidadeTerra = 0 ;
float temperatura = 0.0;
float umidadeAr = 0.0;
int luminosidade = 0;


static char nome_arquivo[13]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA

#define countof(a) (sizeof(a) / sizeof(a[0]))

void setup()
{
  
  
  int ciclo = 0;

  /// terminal
  Serial.begin(9600);

  /// temperatura
  Serial.println(F("Inicializando o sensor de Temperatura "));


  /// Umidade
  Serial.println(F("Inicializando o sensor de umidade  ..."));
  Wire.begin();  /// inicializando o sensor de iluminação

  /// luminosidade
  Serial.println(F("Inicializando o sensor de luminosidade  ..."));
  BH1750_Init(BH1750address);

  /// rele
  Serial.println(F("Inicializando o rele  ..."));
  // pinMode(porta_rele1, OUTPUT); problemas

  /// relogio
  Serial.println(F("Inicializando o relógio  ..."));
            Rtc.Begin(); //INICIALIZA O RTC   

            compiled = RtcDateTime(__DATE__, __TIME__); //VARIÁVEL RECEBE DATA E HORA DE COMPILAÇÃO
            
            if (Rtc.GetIsWriteProtected())
            { //SE O RTC ESTIVER PROTEGIDO CONTRA GRAVAÇÃO, FAZ
              Serial.println(F("RTC está protegido contra gravação. Habilitando a gravação agora...")); //IMPRIME O TEXTO NO MONITOR SERIAL
              Rtc.SetIsWriteProtected(false); //HABILITA GRAVAÇÃO NO RTC
            }
          
            if (!Rtc.GetIsRunning())
            { //SE RTC NÃO ESTIVER SENDO EXECUTADO, FAZ
              Serial.println(F("RTC não está funcionando de forma contínua. Iniciando agora...")); //IMPRIME O TEXTO NO MONITOR SERIAL
              Rtc.SetIsRunning(true); //INICIALIZA O RTC
            }

           
            RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
              if (now < compiled) { //SE A INFORMAÇÃO REGISTRADA FOR MENOR QUE A INFORMAÇÃO COMPILADA, FAZ
                  Serial.println(F("As informações atuais do RTC estão desatualizadas. Atualizando informações...")); //IMPRIME O TEXTO NO MONITOR SERIAL
                  Rtc.SetDateTime(compiled); //INFORMAÇÕES COMPILADAS SUBSTITUEM AS INFORMAÇÕES ANTERIORES
                  Serial.println(); //QUEBRA DE LINHA NA SERIAL
              }
              else if (now > compiled){ //SENÃO, SE A INFORMAÇÃO REGISTRADA FOR MAIOR QUE A INFORMAÇÃO COMPILADA, FAZ
                  Serial.println(F("As informações atuais do RTC são mais recentes que as de compilação. Isso é o esperado.")); //IMPRIME O TEXTO NO MONITOR SERIAL
                  Serial.println(); //QUEBRA DE LINHA NA SERIAL
              }
              else if (now == compiled) { //SENÃO, SE A INFORMAÇÃO REGISTRADA FOR IGUAL A INFORMAÇÃO COMPILADA, FAZ
                  Serial.println(F("As informações atuais do RTC são iguais as de compilação! Não é o esperado, mas está tudo OK.")); //IMPRIME O TEXTO NO MONITOR SERIAL
                  Serial.println(); //QUEBRA DE LINHA NA SERIAL
              }
  
            if (imprime_serial)
            {
               Serial.print(F("Compilado em: ")); //IMPRIME O TEXTO NO MONITOR SERIAL
               printDateTime(compiled); //PASSA OS PARÂMETROS PARA A FUNÇÃO printDateTime
            }

  ////dimmer

  //Declarando o pino digital load (digital 3) como saída
  pinMode(load, OUTPUT);

  //Inicializa interrupção. O número zero indica a porta 2 do Arduino,
  //zero_cross_int é a função que será chamada toda vez que pino 2 do Arduino,
  //"subir" (RISING) de valor de 0 para 1.

  // attachInterrupt(0, zero_cross_int, RISING);

  
  Serial.println(F("Iniciando Monitoramento"));

  
}




//SDListaArquivos();
//SDCriaArquivo();
//SDRemoveFile();
//SDListaArquivos();

bool Monitorar()
{
  RtcDateTime now = Rtc.GetDateTime();
  int hora = now.Hour();
  if ( hora >= 7 && hora < 18) return true;  /// monitorar até as 18 horas 
  if ( hora >=18 || hora <7) return false;  /// nao monitorar, rodar a rotina de manutenção
  return true; 
}

  
/// Iniciou manutencao 1 
/// Parou no rega 2 
/// parou na iluminacao 3
/// Terminou manutencao 

int VerificaStatusManutencao()
{

   SdFat sdCard;
   SdFile meuArquivo;
   char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   const size_t LINE_DIM = 50;
   char line[LINE_DIM]; 
   char line_ant[LINE_DIM]; 
   char digitos[1]; 

       char  s1[3];
  char  s2[6];
  char  s3[5];
  char  s4[6];
  
   int contador= 0 ; 
   //SDCriaArquivo(); /// cria o arquivo 
   RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
   Nome_Arquivo(now);
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sdCard.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sdCard.initErrorHalt();
  }
  
 
  // Abre o arquivo data.TXT
  
  if (!meuArquivo.open(nome_arquivo, O_RDWR )) /// nao acho que 
  {
    Serial.println(F("Erro na abertura do arquivo data.TXT!"));
    sdCard.errorHalt("Erro na abertura do arquivo data.TXT!"); /// nao pode travar o prog
  }
    while (meuArquivo.available()) 
    {
      if (line[0]=='#' && line[12]=='#' )/// pega as linhas validas de manutencao , so pega a linha se estiver finalizada 
      {
        meuArquivo.fgets(line, sizeof(line));
      }
      meuArquivo.close(); 
     
      sscanf(line," %s %s %s %s ",s1 , s2 ,s3 ,s4 ); //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
            //  PSTR("# %4u %3u #"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES 
      
      tempo_atividade=atoi(s3);
            
            if (line[2]=='1' && line[3]== '1') return 1;
            if (line[2]=='2' && line[3]== '2') return 2;
            if (line[2]=='3' && line[3]== '3') return 3;
            if (line[2]=='4' && line[3]== '4') {status_manutencao=4444; return 4;} ;
     
    }
  return 0 ; /// erro nao deve retornar zero 
}

void Escreve_Manutencao(int manutencao, int minutos )
{
 
   SdFat sdCard;
   SdFile meuArquivo;
   char dados_manutencao[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   
   RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
   Nome_Arquivo(now);
   
   //SDCriaArquivo(); /// cria o arquivo 
   
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sdCard.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sdCard.initErrorHalt();
  }
  
 
  // Abre o arquivo data.TXT
  
  if (!meuArquivo.open(nome_arquivo, O_RDWR | O_AT_END))
  {
    Serial.print(F("Erro na abertura do arquivo data.TXT!"));
    sdCard.errorHalt("Erro na abertura do arquivo data.TXT!"); /// nao pode travar o prog
  }
  
        /////////////////
        //   CArtão SD
        ////////////////////////
        // Grava dados do potenciometro em LER_POT.TXT

      snprintf_P(dados_manutencao,
             countof(dados_manutencao),
             PSTR("# %4u %3u #"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             status_manutencao, //status da manutencao
             minutos ); //tempo em minutos
             
             
        meuArquivo.print(dados_manutencao);                            
        meuArquivo.println();
        meuArquivo.close();  
   

}


  
void printDateTime(const RtcDateTime& dt) {
  char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             dt.Day(), //DIA
             dt.Month(), //MÊS
             dt.Year(), //ANO
             dt.Hour(), //HORA
             dt.Minute(), //MINUTOS
             dt.Second() ); //SEGUNDOS
  Serial.print(datestring); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
}

void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10); //1lx resolution 120ms
  Wire.endTransmission();
}
/*/////////////////
    Fim Sensor de Iluminação
*/////////////////////////

void Nome_Arquivo(const RtcDateTime& dt)
{
  
  snprintf_P(nome_arquivo,
             countof(nome_arquivo),
             PSTR("%02u%02u%04u%s"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             dt.Day(), //DIA
             dt.Month(), //MÊS
             dt.Year(), //ANO
             ".txt");
  }
  
void IniciaManutencao()
{
  int situacao = 0 ; 
  if (status_manutencao==0) /// nao fez a manutencao ainda 
  {
      /// inicia manutencao 
       Escreve_Manutencao(1111,0); /// manutencao foi iniciada escreve no arquivo o codigo a linha 1111  (inicio da manutencao)  
       VerificarUmidade(tempo_atividade);  /// 
       CalculaTempoSolDiario(tempo_atividade);
       Escreve_Manutencao(4444,0); /// manutencao foi terminada escreve no arquivo o codigo a linha 4444  (fim manutencao)  
  }
  else 
  {
    situacao = VerificaStatusManutencao();  
  }
  
  
  if (status_manutencao==4444) /// manutencao jah feita
    delay(10000); /// reverificar sera feita em em 10 minutos + tempo do loop
  
  if (situacao==3) /// manutencao parou na luz 
  {
      Serial.println(F("Manutencao interrompida na iluminacao , resumindo") ) ;   
      CalculaTempoSolDiario(tempo_atividade);
      
  }   

  if (situacao==2) /// manutencao parou na rega 
  {
    Serial.println(F("Manutencao interrompida na rega, resumindo") ) ; 
    VerificarUmidade(tempo_atividade);
    CalculaTempoSolDiario(tempo_atividade);
  }     
  
  if (situacao==1) /// manutencao iniciada mas nao terminada 
  {
    Serial.println(F("Manutencao interrompida no inicio, resumindo") ) ; 
  }
      /// passe para a situacao 2 
  
}

int Le_arquivo()
{
 
   SdFat sdCard;
   SdFile meuArquivo;
   char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   const size_t LINE_DIM = 50;
   char line[LINE_DIM]; 
   char line_ant[LINE_DIM]; 

   int contador= 0 ; 
   //SDCriaArquivo(); /// cria o arquivo 
   RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
   Nome_Arquivo(now);
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sdCard.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sdCard.initErrorHalt();
  }
  
 
  // Abre o arquivo data.TXT
  
  if (!meuArquivo.open(nome_arquivo, O_RDWR )) /// nao acho que 
  {
    Serial.println(F("Erro na abertura do arquivo data.TXT!"));
    sdCard.errorHalt("Erro na abertura do arquivo data.TXT!"); /// nao pode travar o prog
  }
    while (meuArquivo.available()) 
    {
      
      
      meuArquivo.fgets(line, sizeof(line));
             
      if (line[0]=='#')/// manutencao 
      {
        if (contador >0 ) for (int i=0;i<50;i++) line_ant[i]=line[i]; /// copia a linha atual para a anterior caso tenha truncado a ultima saida
        
        
      } 
       
       
       //
       // Serial.print(line);
      
      
      //if (saida=='#')
      contador ++;
    }

    
    meuArquivo.close();
}

void VerificarUmidade(int travou) /// melhorar 
{
  
  if ( umidadeTerra<60 && umidadeTerra>50)
  {
    if(travou!=0)
        Rele(2);/// acionar o rele por x minutos 
    else
        Rele(2);/// acionar o rele por x minutos 
  }  
    if ( umidadeTerra<=50 && umidadeTerra>30)
  {
    if(travou!=0)
        Rele(2);/// acionar o rele por x minutos 
    else
        Rele(2);/// acionar o rele por x minutos 
  }  
    if ( umidadeTerra<30 )
  {
    if(travou!=0)
        Rele(2);/// acionar o rele por x minutos 
    else
        Rele(2);/// acionar o rele por x minutos  
  }
}

void CalculaTempoSolDiario(int travou)
{
   int total = 0 ; 
    /// ler o total de leituras de sol do dia com mais de 1000 lumens 
    total= TotalLeituras();
    /// se for menor que 960 leituras 
    if(travou!=0)
        LigaLampada(travou);/// acionar o rele por x minutos 
    else
    {
      if (total<960)
        LigaLampada(960-total);/// acionar o rele por x minutos 
    }
    
}

//// retorna o total de leituras acima de 1000 lumens
int TotalLeituras ()
{ 
  
   SdFat sdCard;
   SdFile meuArquivo;
   char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   char dados[80]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   int total_leituras=0;

   
   RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
   Nome_Arquivo(now);
   
   //SDCriaArquivo(); /// cria o arquivo 
   
   
  
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sdCard.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sdCard.initErrorHalt();
  }
  
 
  // Abre o arquivo data.TXT
  
  if (!meuArquivo.open(nome_arquivo, O_RDWR ))
  {
    Serial.print(F("Erro na abertura do arquivo data.TXT!"));
    sdCard.errorHalt("Erro na abertura do arquivo data.TXT!"); /// nao pode travar o prog
  }

  char  s1[3];
  char  s2[6];
  char  s3[5];
  char  s4[6];
  char  s5[6];
  char  s6[3];
  char  s7[5];
  char  s8[8];
  
  //float ua=0.0;
  //float temp=0.0;
  //int uter=0.0;
  int lumi=0.0;
        
  
  
  while (meuArquivo.available()) 
    {
        meuArquivo.fgets(datestring, sizeof(datestring));     
        meuArquivo.fgets(dados, sizeof(dados));     
        dados[79]='\n'; 
        
        
         sscanf(dados," %s %s %s %s %s %s %s %s " ,s1 , s2 ,s3 ,s4 ,s5,s6,s7,s8 ); //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
            // (" UAR  %3.0f Temp  %3.0f UTerra  %4d Lumin    %5d"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
       

        
        //ua=atof(s2);
        //temp=atof(s4);
        //uter=atoi(s6);
        lumi=atoi(s8);
        if (lumi>=1000)
        {
          total_leituras++;
          }
            
        
       
        //Serial.print(ua); 
        //Serial.print(" " ); 
        //Serial.print(temp); 
        // Serial.print(" " );       
        //Serial.print(uter); 
        //Serial.print(" " ); 
       // Serial.print(lumi); 
        
        //Serial.println(); 

        //if (luminosidade>1000) total_leituras++;
       //total_leituras+=luminosidade;
       // Serial.println(luminosidade); 
        
    }
       
        meuArquivo.close();  
        return total_leituras;
}

void LeiaHorasDia()
{
  int leituras=0; 
  /// ler o arquivo 
  /// somar o numero de leituras acima de 1000 lum 

 // if (leituras )
  
}

void Inicializacao_dia()
{
  //le a data
//  RegistroAnteriorMesmoDia();
  // verifica se ha registro da mesma data
  // se tiver continua (queda de luz, tirou da tomada)
  // senao inicia um log novo



}

void LigaLampada(int tempo_min)
{
  attachInterrupt(0, zero_cross_int, RISING); /// fazer apenas uma vez
  Escreve_Manutencao(3333,tempo_min); // caso a luz caia , pode resumir posteriormente 
  delay(1000);
  /// continuar fazendo ate que cumpra o tempo necessario
  // eventualmente parar e monitorar as condicoes

}

void DesligaLampada(int tempo_min)
{
  ///if(tempo <) verificar quanto tempo ele vai ficar monitorando
  detachInterrupt(0);

  /// continuar fazendo ate que cumpra o tempo necessario
  // eventualmente parar e monitorar as condicoes

}

/*/////////////////
     Sensor de Iluminação
*/////////////////////////
int BH1750_Read(int address)
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available())
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();
  return i;
}

/*/////////////////
     RElógio
*/////////////////////////


/*/////////////////
    Fim RElógio
*/////////////////////////
void UmidadeAreTemperatura() {

  int chk = DHT11.read(DHTPIN);
  // TODO:  verificar o checksum para considerar a temp
   if (imprime_serial) Serial.print(F("Read sensor: "));
    switch (chk)
    {
     case DHTLIB_OK:
     {
      temperatura=(float)DHT11.temperature; 
      umidadeAr=(float)DHT11.humidity;
      if (imprime_serial)Serial.println(F("OK"));
     }
     break;
     case DHTLIB_ERROR_CHECKSUM: /// tratar
     {
      temperatura=(float)DHT11.temperature; 
      umidadeAr=(float)DHT11.humidity;
      
      if (imprime_serial)Serial.println(F("Checksum error"));
     }
     
     break;
     case DHTLIB_ERROR_TIMEOUT:
     if (imprime_serial)Serial.println(F("Time out error"));
     break;
     default:
     if (imprime_serial)Serial.println(F("Unknown error"));
     break;
    }
  
  
  
}

void AtualizaRelogio()
{
  /*/////////////////
    RElógio
  */////////////////////////
  
  RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
  //printDateTime(now); //PASSA OS PARÂMETROS PARA A FUNÇÃO printDateTime
  Nome_Arquivo(now);
    
 

  
  
  /*/////////////////
    Fim RElógio
  */////////////////////////
}

void UmidadeTerra()
{
  /*//////////////////////////////////
              ///  sensor de umidade da terra
  */////////////////////////////////
  umidadeTerra = analogRead(A1);
  umidadeTerra = map(umidadeTerra, 500, 0, 0, 100);
  //int umido = 400 ;
  //int ideal = 800 ;
   //int seco  = 1024 ;
}

void Iluminacao()
{

  if (2 == BH1750_Read(BH1750address))
  {
    luminosidade = ((buff[0] << 8) | buff[1]) / 1.2;
  
  }
  else {
    Serial.println( BH1750_Read(BH1750address));
    Serial.println(F("erro"));
  }

}



void Rele(int min)
{
  
  int tempo = (min * 60000) ; 
  /*/////////////////
             Rele
  */////////////////////////
  
  //digitalWrite(porta_rele1, LOW);  //Liga rele 1 verificar qual e a porta rele 
  
  for (int i = min ; i>0 ;i-- )
  {
     
     Escreve_Manutencao(2222,i);
     delay(60000); /// espera 1 minuto 
  }
 
 // digitalWrite(porta_rele1, HIGH); //Desliga rele 1     
   /*/////////////////
    Fim Rele
  */////////////////////////

}

/*/////////////////
   Dimmer
   //Função executada quando o Dimmer Shield detecta a passagem por zero da tensão
//alternada (senóide)
*/////////////////////////

void zero_cross_int()
{




  //Cálculo do ângulo de disparo: 60Hz -> 8,33ms (1/2 ciclo)
  //(8333us - 8,33us) / 100 = 83 (aproximadamente)

  //O powertime é o tempo que o TRIAC permanescerá desligado quando é detectado
  //o ponto 0 da senóide e varia de 0 a 8300 microsegundos
  int powertime = (82 * (100 - power)); /// usa o power para calcular o powertime

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

/*/////////////////
   Fim Dimmer
*/////////////////////////

void SDCriaArquivo()
{
  SdFat sd;
 
  SdFile file;
  
 // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sd.initErrorHalt();
  }
  
  /// Verifica se o arquivo existe 
   if (sd.exists(nome_arquivo)) 
   {  
       if(imprime_serial) {Serial.println(F("Data já existe, continuando o registro"));} // se existe continua escrevendo nele
       // nao faz nada 
        if (!file.open(nome_arquivo, FILE_WRITE )) {
            Serial.println(F("Erro na abertura/criacao do arquivo"));
          }
          file.close();
         
    }
    
   else    /// senao cria 
      {
          // Create a file in  using a path.
          if (!file.open(nome_arquivo, FILE_WRITE | O_CREAT)) {
            Serial.println(F("Erro na criação do arquivo"));
          }
          file.close();
          Serial.println(F("Arquivo criado\n"));
       }
  
  
  
}

void SalvaTudo( )
{
 
   SdFat sdCard;
   SdFile meuArquivo;
   char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   char dados[80]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   
   RtcDateTime now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
   Nome_Arquivo(now);
   
   //SDCriaArquivo(); /// cria o arquivo 
   
   //printDateTime(now);
   //Serial.print(F(" Monitorando "));
   //Serial.print((nome_arquivo));
  // Serial.println();
   
   
  
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sdCard.begin(chipSelect, SD_SCK_MHZ(50))) {
     Serial.println(F("Erro na inicializacao do cartao"));
    sdCard.initErrorHalt();
  }
  
 
  // Abre o arquivo data.TXT
  
  if (!meuArquivo.open(nome_arquivo, O_RDWR | O_CREAT | O_AT_END))
  {
    Serial.print(F("Erro na abertura do arquivo data.TXT!"));
    sdCard.errorHalt("Erro na abertura do arquivo data.TXT!"); /// nao pode travar o prog
  }
  
        /////////////////
        //   CArtão SD
        ////////////////////////
        // Grava dados do potenciometro em LER_POT.TXT
                    
        now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
        snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             now.Day(), //DIA
             now.Month(), //MÊS
             now.Year(), //ANO
             now.Hour(), //HORA
             now.Minute(), //MINUTOS
             now.Second() ); //SEGUNDOS
        
         char umidadeArt[6];
         dtostrf(umidadeAr, 4, 2, umidadeArt);
         
         char tempt[6];
         dtostrf(temperatura, 4, 2, tempt);
         
         snprintf_P(dados,
             countof(dados),
             PSTR(" UAR %s Temp %s UTerra %3u Lumin %5d"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             umidadeArt, //Umidade Ar
             tempt, /// temperatura
             umidadeTerra, //Umidade Terra 
             luminosidade );//Lumin 
             
        meuArquivo.print(datestring); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
        meuArquivo.print(dados); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
        meuArquivo.println(); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
        meuArquivo.close();  
   
  
  

}

void MostraTudo( )
{
  char datestring[20]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   char dados[80]; //VARIÁVEL ARMAZENA AS INFORMAÇÕES DE DATA E HORA
   
    /// quando eu descomento dá problema ,não sei pq 
   if (imprime_serial)Serial.print(F(" Dados Salvos "));
 
  if (imprime_sensores)
  {
     RtcDateTime  now = Rtc.GetDateTime(); //VARIÁVEL RECEBE INFORMAÇÕES
        snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             now.Day(), //DIA
             now.Month(), //MÊS
             now.Year(), //ANO
             now.Hour(), //HORA
             now.Minute(), //MINUTOS
             now.Second() ); //SEGUNDOS
        
         char umidadeArt[6];
         dtostrf(umidadeAr, 4, 2, umidadeArt);
         
         char tempt[6];
         dtostrf(temperatura, 4, 2, tempt);
         
         snprintf_P(dados,
             countof(dados),
             PSTR(" UAR %s Temp %s UTerra %3u Lumin %5d"), //FORMATO DE EXIBIÇÃO DAS INFORMAÇÕES
             umidadeArt, //Umidade Ar
             tempt, /// temperatura
             umidadeTerra, //Umidade Terra 
             luminosidade );//Lumin 
             
        Serial.print(datestring); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
        Serial.print(dados); //IMPRIME NO MONITOR SERIAL AS INFORMAÇÕES
        Serial.println(F(" "));
     
  }
  
  }
void SDArquivoExiste()
{
  SdFat sd;
  SdFile root;
  SdFile file;
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }

   // verifica se existe os arquivos 
  if (sd.exists("Folder1")
      || sd.exists("Folder1/file1.txt")
      || sd.exists("Folder1/File2.txt")) {
    Serial.println(F("\n Erro  .\n"));
  }
  
}

void SDCriaPasta()
{
  SdFat sd;
  SdFile root;
  SdFile file;
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }
  // Create a new folder.
  if (!sd.mkdir("Folder1")) {
    Serial.println(F("\n erro criando pasta .\n"));
  }
  Serial.println (F("Created Folder1\n"));
  }

void SDRemoveDir()
{
  SdFat sd;
  SdFile root;
  SdFile file;
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }  
// Remove Folder1.
  if (!sd.rmdir("Folder1")) {
    Serial.println(F("\n erro removendo pasta .\n"));
  }  
}

void SDRemoveFile()
{
   SdFat sd;
  SdFile root;
  SdFile file;
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }
  
  if (!sd.remove(nome_arquivo) ) {
   Serial.println(F("\n erro revomendo .\n"));
  }
  Serial.println(F("\n Removido .\n"));
 }

void SDListaArquivos()
{
  
  
  SdFat sd;
  SdFile root;
  SdFile file;
  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    sd.initErrorHalt();
  }
  
  Serial.println(F("\n Lista  de arquivos no SD.\n"));
  sd.ls(LS_R);

  Serial.println(F("Fim da lista !\n"));

}

void Decisao()
{

  ///ph entre 5,5 e 6  No solo, a dinâmica dos nutrientes e dos elementos tóxicos é governada por diversos 
  // fatores, sendo o pH um dos mais importantes. Além de gerir a disponibilidade dos elemen-
  // tos, o pH afeta a atividade de microrganismos, favorece ou inibe doenças nos cultivos e interfere na habilidade de competição entre diferentes espécies de plantas (MEURER, 2007). Para o morangueiro, o pHH2O considerado adequado está em torno de 6,0, que é a condição em que a cultura apresenta melhor desenvolvimento e em que a maioria dos nutrientes presentes na solução do solo está disponível para a absorção pelas plantas (COMISSÃO DE QUÍMICA E FERTILIDADE DO SOLO - RS/SC, 2004).
  
  

  ///raramente a planta inicia o florescimento quando as temperaturas noturnas são superiores a 15 ºC
  ///A elevação da da temperatura faz, porém, com que a planta permaneça na fase vegetativa, produzindo estolões 
  // continuamente, o que reduz a emissão de flores e, consequentemente, a produção de frutos. 
  // temperaturas médias durante o dia entre 20 ºC e 26 ºC,
  //Pode-se considerar 10 ºC como o limite de temperatura para que ocorra o desenvolvimento normal da planta (VERDIER, 1987).
  //Temperaturas abaixo de 15 ºC podem afetar negativamente o crescimento e a maturação dos frutos, enquanto temperaturas elevadas, principalmente na primavera e no 
  //  verão, podem acelerar a maturação dos frutos, reduzindo seu tamanho e sua firmeza.
  /// Independentemente do fotoperíodo, temperaturas elevadas e constantes entre 28 ºC e 30 ºC inibem a indução floral em 
  // cultivares de dias curtos e de dias neutros 

  /// se a temperatura for maior que 28 graus    
  /// liga a ventoinha  se menor que 10 aquecer 


  /// O fotoperíodo atua na indução da diferenciação do meristema vegetativo para o floral, reciprocamente (ALMEIDA et al., 2009).
  /// Em condições de fotoperíodo curto, há favorecimento à floração, em detrimento da 
  /// inibição da produção de estolhos, independentemente da temperatura. Em dias longos 
  /// (fotoperíodo longo), a resposta é inversa (FILGUEIRA, 2003; RIOS, 2007).
  /// A maioria dos  estudos de indução floral em cultivares de dias curtos aponta como ideais os intervalos 
  /// de fotoperíodos de 8 horas a 12 horas, 
  // quanto maior for o comprimento do dia, menor será a temperatura necessária para que ocorra 
 //  a indução floral. De uma forma prática, à medida que o inverno se aproxima, os dias tornam-
 //  -se mais curtos e a temperatura declina, estimulando a floração e a frutificação.  Já durante o 
 // verão, o fotoperíodo alonga-se e a temperatura eleva-se, favorecendo a emissão de estolhos, 
 // a produção de estolões, na maioria das variedades, tem início quando o comprimento do dia 
 //  é maior que 12 horas, e as temperaturas estão acima de 22 ºC 

  
  /// se a iluminacao diaria for menor que 8 horas ligar a lampada até chegar a 8 horas 

  
  /// se for maior que 12 ligar um led avisando para retirar do sol 
  
  
  
  /// se a umidade da terra for menor que 400 
  /// rega o solo 
    
  /// regar no max 3 x por dia 
  
  
  
  
  
  
  
 }

void loop() {




  /// se a iluminacao for insuficiente, parar de monitorar e fornecer iluminacao
  /// parar de iluminar e colher dados
  /// voltar a iluminar se necessario
  /// calcular o total de luz que a planta recebeu no dia

  // power =5;


  /// ligar a lampada e desligar as leituras enquanto usa a lampada
  //

 
if (Monitorar()) /// 7 -> 18 true  18-> 7h false 
  {
    /// Rotina de monitoramento 
    detachInterrupt(0);
    //SDListaArquivos();
    UmidadeAreTemperatura();
    Iluminacao();
    UmidadeTerra();
    //MostraTudo();
    SalvaTudo();
    
  }
 else 
 {
    /// Rotina de manutencao 
    Serial.println("Manutencao iniciada");
      IniciaManutencao();
     //LigaLampada(1);
     //power=0;
  }

  //delay(30000);  /// 30 s
  delay(300000);  /// 300 s
  //delay(2000);  /// 2 s


}
