///     Jogo da Velha 3D 
///     Colégio Galdino do Valle Filho - Nova Friburgo 
///     

//// Controle XBOX 
  #include <XBOXUSB.h>  
  // Satisfy the IDE, which needs to see the include statment in the ino too.
  #ifdef dobogusinclude
  #include <spi4teensy3.h>
  #endif
  #include <SPI.h>
  USB Usb;
  XBOXUSB Xbox(&Usb);
//// Controle XBOX 


////////////////////////////////
//CONSTRUÇÃO DA MATRIZ DE ON/OFF para validacao da jogada 
///////////////////////////////// 
    int Validacao[54];
   
    
////////////////////////////////
/// Variaveis globais do programa 
/////////////
int vez=0;           ///    de quem eh a vez 
int pos=44;           ///    posicao inicial do cursor 
int camada_jogada=0; /// 
char confirma;        //// tecla de confirmacao 
char tp ;            /// tecla pressionada 
int jogada_valida=0; /// verifica se a jogadaevalida

void setup()
{

    Serial.begin(9600); //INICIALIZA A SERIAL
    
    
    //// Inicializacao xbox 
    #if !defined(__MIPSEL__)
      while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
    #endif
      if (Usb.Init() == -1) {
        Serial.print(("\r\nOSC did not start"));
        while (1); //halt
      }
      Serial.print(("\r\nXBOX USB Library Started"));
    //// Fim Inicializacao xbox 

    
    //// Inicializacao dos Pinos 
      for (int i = 2 ; i < 54 ; i++ )
        pinMode(i, OUTPUT);    /// 23 vermelho 
    ////  

   /// Inicializacao Jogo 
   Reinicia(); 

    
    /// TODO: acender um led para indicar de quem eh a jogada 
    /// 
    ////
    
    
}
 
void loop()
{
    Navegacao(); 
    /// VerificaVencedor();  // verificar se o cubo esta todo aceso sem vencedor 
    
  
    delay(1);
}



void Navegacao()
{
  ////  Comandos do Controle xbox  TODO : Validar as entradas 
    Usb.Task(); /// inicializa tarefa usb  
    //  Navegacao 
    if (Xbox.getButtonClick(RIGHT))
    { 
        pos += 2 ; 
    } 
    
    if (Xbox.getButtonClick(UP))   
    {  
      pos -= 6 ; 
    }
    
    if (Xbox.getButtonClick(LEFT)) 
    {  
      pos -= 2 ; 
    }
    if (Xbox.getButtonClick(DOWN)) 
    {  
       pos -= 6 ; 
    } 

    if (pos < 0 ) {pos = 0; }/// tratamento de valores invalidos 
    if ( pos > 53) {pos = 53; }/// tratamento de valores invalidos 
    
    
    // confirma jogada  
     if (Xbox.getButtonClick(Y)) 
     {
       Valida_Jogada();/// validar a jogada 
     }  


      /// Botao para reiniciar o jogo 

      /// botao para apagar o cubo 

      if (Xbox.getButtonClick(R2)) 
     {
       Apaga_Leds(); 
      
     }  
     
     if (Xbox.getButtonPress(R1)) 
     {
       Pisca_Led(pos); /// 
     }  

     if (Xbox.getButtonPress(L1)) 
     {
       Restaura_Leds();
     }  

      
      //// Botao para voltar jogada 


      

}

void Valida_Jogada()
{
  
           if (J(vez)) 
           {
              if ( Validacao[pos] == 3 && Validacao[pos+1]==3  ) /// se ninguem jogou nesta posicao no verm e no azul  
                {
                   Validacao[pos] = 0;  /// joga o vermelho 
                   vez++ ; /// passa a vez 
                   digitalWrite(pos,HIGH); //// Marcar o Led como Aceso    
                   Serial.println(pos);
                }else 
                {
                  Serial.println(pos);
                  }
                
              
           }
           else 
           {
              if ( Validacao[pos] == 3 && Validacao[pos-1]==3  ) /// se ninguem jogou nesta posicao no verm e no azul  
              {
                  Validacao[pos] = 1; /// joga o azul nesta posicao 
                  vez++ ; /// passa a vez 
                  digitalWrite(pos,HIGH); //// Marcar o Led como Aceso    
                  Serial.println(pos);
              }
           }
  
}

//// Retorna 0 se vez do vermelhro 
//// Retorna 1 se vez do azul 
int J(int ent)
{
  if ((ent%2)==0) 
    return 0; 
  else 
    return 1; 
    
 }

  //////////////////////////////
  /// loop da selecao de teclas 
  /////////////////////////////
  void Reinicia()
{
   // Serial.println("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
  //  Serial.println(tp); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
   // Serial.println(confirma); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  //  Serial.println("Vez"); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
 //   Serial.println(vez); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
 
 
 /// Inicializacao vetor  validacao 
     for (int i=0;i<54;i++)
    {
       Validacao[i]= 3 ; /// 3 = led desligado 
       digitalWrite(pos,LOW); //// Marcar os leds como apagados     
    }
  
}


void Testa_Leds()
{
  for (int i=0; i<54 ;  i++ ){
  digitalWrite(i, HIGH); delay(300);  digitalWrite(50,LOW); 
  }
}

void Apaga_Leds()
{
  for (int i=0; i<54 ;  i++ ){
       digitalWrite(i, HIGH); delay(300);  digitalWrite(50,LOW); 
  }
}

void Restaura_Leds()
{
  for (int i=0; i<54 ;  i++ )
  {      
    if (Validacao[i]!=3 ) digitalWrite(i, HIGH);  
  }
}

void Pisca_Led(int led )
{
      digitalWrite(led, HIGH); delay(300);  digitalWrite(led,LOW); 
}

void Testa_Tabuleiro()
{
  
}

void Testa_Vitoria( )
{
      /// linha   
      /// coluna 
      /// diagonais 
      /// colunas 
      /// diagonais 

      /// teste por camadas ? 
       
     //  Reinicia_Jogo(); 
}


/*
  
  //////////////////////////
  
  ///////////////////////////
  //   Verifica a jogada 
  /////////////////////////
  if (tp && confirma=='*' ) 
  {
    TestaJogada(tp,vez);  ///verificar se a jogada eh valida 
    Reinicia();
    Testa_Tabuleiro(); /// verifica se alguem ganhou 
  }
  //////////////////////////////



 
}




void TestaJogada(int ent , int jog )
{
   Serial.print("vez: "); //IMPRIME O TEXTO NO MONITOR SERIAL
   Serial.println(jo); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
   Serial.print("ent: "); //IMPRIME O TEXTO NO MONITOR SERIAL
   Serial.println(ent); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA

  
  /// buzzer ? 
  if ( vez%2  ) /// jogada par 
  {
       if (matriz_onoffPar[][] == 0 )  /// jogada valida 
       {
            matriz_onoffPar[][] =1 ; 
            Serial.println("alto");
            vez ++; 
        } 
       else 
       {
        
        }
       
  
  }
  else /// jogada válida 
  {
       if (matriz_onoffImPar[][] == 0 )  /// jogada valida 
       {
            matriz_onoffImPar[][] = 1 ;
            Serial.println("alto");
            vez ++; 
        } 
       else 
       {
        
        }
  }

    
  
}







    
  



 





int MAPA(char ent , int vez)
{
  int par =(vez%2) ; 
 // Serial.println("par : "); //IMPRIME O TEXTO NO MONITOR SERIAL
 // Serial.println(par); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  if (ent=='1')
  {
    if (par) 
      return 50;  
    else 
      return 51; 
  }

 if (ent=='2')
  {
    if (par) 
      return 48;  
    else 
      return 49; 
  }

if (ent=='3')
  {
    if (par) 
      return 46;  
    else 
      return 47; 
  }

  
if (ent=='4')
  {
    if (par) 
      return 42;  
    else 
      return 43; 
  }

  if (ent=='5')
  {
    if (par) 
      return 40;  
    else 
      return 41; 
  }


  if (ent=='6')
  {
    if (par) 
      return 38;  
    else 
      return 39; 
  }

  if (ent=='7')
  {
    if (par) 
      return 34;  
    else 
      return 35; 
  }


if (ent=='8')
  {
    if (par) 
      return 32;  
    else 
      return 33; 
  }


  if (ent=='9')
  {
    if (par) 
      return 30;  
    else 
      return 31; 
  }

  
  
}
void Testa_Tabuleiro()
{
  
  /// Linhas
  Testa_Vitoria(50,48,46); 
  Testa_Vitoria(51,49,47); 
 
  Testa_Vitoria(42,40,38); 
  Testa_Vitoria(43,41,39); 
  
  Testa_Vitoria(34,32,30); 
  Testa_Vitoria(35,33,31); 

  /// colunas
  Testa_Vitoria(50,42,34); 
  Testa_Vitoria(51,43,35); 
  
  Testa_Vitoria(48,40,32); 
  Testa_Vitoria(49,41,33); 
  
  Testa_Vitoria(46,38,30); 
  Testa_Vitoria(47,39,31); 

  // diagonais 
  Testa_Vitoria(50,40,30); 
  Testa_Vitoria(51,41,31); 

  Testa_Vitoria(34,40,46); 
  Testa_Vitoria(35,41,47); 

}

void Testa_Vitoria(int A,int B,int C )
{
  if ( (digitalRead(A)==HIGH)   && (digitalRead(B)==HIGH) && (digitalRead(C)==HIGH)  )
  {
        Pisca(A,B,C); 
        Serial.println("Vencedor : "); //IMPRIME O TEXTO NO MONITOR SERIAL
        Serial.println(A); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
        Serial.println(B); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
        Serial.println(C); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
        
       Reinicia_Jogo(); 
  }
  
}
void Reinicia_Jogo()
{
   digitalWrite(50,LOW);
 digitalWrite(51,LOW);
  
   digitalWrite(48,LOW);
  digitalWrite(49,LOW);

  digitalWrite(46,LOW);
  digitalWrite(47,LOW);
  ////////////////////////////////////
   digitalWrite(42,LOW);
  digitalWrite(43,LOW);
  
 digitalWrite(40,LOW);
   digitalWrite(41,LOW);

   digitalWrite(38,LOW);
  digitalWrite(39,LOW);
  
    ////////////////////////////////////

  digitalWrite(34,LOW);
  digitalWrite(35,LOW);
  
  digitalWrite(32,LOW);
  digitalWrite(33,LOW);

  digitalWrite(30,LOW);
  digitalWrite(31,LOW);
  
  ////////////reinicia vez 
  /////
  vez=0;
  
  /////////////////////
  //// reinicia matrizes onoff
  /////////////

  
}

void Pisca(int A,int B,int C)
{
   /// pisca  linha 
        digitalWrite(A, LOW); 
        digitalWrite(B, LOW);   
        digitalWrite(C, LOW); 
        delay(500);
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        delay(500);     
        
        digitalWrite(A, LOW); 
        digitalWrite(B, LOW);   
        digitalWrite(C, LOW); 
        delay(500);
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        delay(500);     

        digitalWrite(A, LOW); 
        digitalWrite(B, LOW);   
        digitalWrite(C, LOW); 
        delay(500);
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        delay(500);     

        digitalWrite(A, LOW); 
        digitalWrite(B, LOW);   
        digitalWrite(C, LOW); 
        delay(500);
        digitalWrite(A,HIGH);
        digitalWrite(B,HIGH);
        digitalWrite(C,HIGH);
        delay(500);     

        
}
*/
