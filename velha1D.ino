/*
Adafruit Arduino - Lesson 3. RGB LED
*/
 #include <Keypad.h> //INCLUSÃO DE BIBLIOTECA
 const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
////////////////////////////////
//CONSTRUÇÃO DA MATRIZ DE ON/OFF para validacao da jogada 
///////////////////////////////// 
int matriz_onoffPar[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0},
  
};

int matriz_onoffImPar[3][3] = {
  {0,0,0},
  {0,0,0},
  {0,0,0},

};

int vez=0;           ///    de quem eh a vez 
int pos_jogada=0;    /// 
int camada_jogada=0; /// 
char confirma;        //// tecla de confirmacao 
char tp ;            /// tecla pressionada 
int jogada_valida=0; /// verifica se a jogadaevalida

byte PinosqtdLinhas[qtdLinhas] = {A3, A4, A5, A6}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {A8, A9, A10,A11}; //PINOS UTILIZADOS PELAS COLUNAS





//INICIALIZAÇÃO DO TECLADO
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 


void setup()
{

  
    pinMode(50, OUTPUT);    /// 23 vermelho 
    pinMode(51, OUTPUT);    /// 23 vermelho 

    pinMode(48, OUTPUT);    /// 23 vermelho 
    pinMode(49, OUTPUT);    /// 23 vermelho 

    pinMode(47, OUTPUT);    /// 23 vermelho 
    pinMode(46, OUTPUT);    /// 23 vermelho 
///////////////////////////
    pinMode(42, OUTPUT);    /// 23 vermelho 
    pinMode(43, OUTPUT);    /// 23 vermelho 

    pinMode(40, OUTPUT);    /// 23 vermelho 
    pinMode(41, OUTPUT);    /// 23 vermelho 

    pinMode(38, OUTPUT);    /// 23 vermelho 
    pinMode(39, OUTPUT);    /// 23 vermelho 
///////////////////////////

    pinMode(34, OUTPUT);    /// 23 vermelho 
    pinMode(35, OUTPUT);    /// 23 vermelho 

    pinMode(32, OUTPUT);    /// 23 vermelho 
    pinMode(33, OUTPUT);    /// 23 vermelho 

    pinMode(30, OUTPUT);    /// 23 vermelho 
    pinMode(31, OUTPUT);    /// 23 vermelho 


////teclado 
Serial.begin(9600); //INICIALIZA A SERIAL
Serial.println("Aperte uma tecla..."); //IMPRIME O TEXTO NO MONITOR SERIAL
Serial.println(); //QUEBRA UMA LINHA NO MONITOR SERIAL

/// acender um led para indicar de quem eh a jogada 

    
}
 
//if (tecla_pressionada)
 // { //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
 //   Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
 //   Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
 // }


void loop()
{
  
 

  //////////////////////////////
  /// loop da selecao de teclas 
  /////////////////////////////
  while (confirma != '*'  ) 
  {
    confirma = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA;
    while (tp == NO_KEY) 
    {
      tp = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA;
    }
  } 
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




void Reinicia()
{
   // Serial.println("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
  //  Serial.println(tp); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
   // Serial.println(confirma); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  //  Serial.println("Vez"); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
 //   Serial.println(vez); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
    tp=NO_KEY;
    confirma=NO_KEY;
}



    
  



 
void Testa_Leds()
{


  digitalWrite(50, HIGH); delay(300);  digitalWrite(50,LOW);
  digitalWrite(51, HIGH); delay(300);  digitalWrite(51,LOW);
  
  digitalWrite(48, HIGH); delay(300);  digitalWrite(48,LOW);
  digitalWrite(49, HIGH); delay(300);  digitalWrite(49,LOW);

  digitalWrite(46, HIGH); delay(300);  digitalWrite(46,LOW);
  digitalWrite(47, HIGH); delay(300);  digitalWrite(47,LOW);
  ////////////////////////////////////
   digitalWrite(42, HIGH); delay(300);  digitalWrite(42,LOW);
  digitalWrite(43, HIGH); delay(300);  digitalWrite(43,LOW);
  
  digitalWrite(40, HIGH); delay(300);  digitalWrite(40,LOW);
  digitalWrite(41, HIGH); delay(300);  digitalWrite(41,LOW);

  digitalWrite(38, HIGH); delay(300);  digitalWrite(38,LOW);
  digitalWrite(39, HIGH); delay(300);  digitalWrite(39,LOW);
  
    ////////////////////////////////////

   digitalWrite(34, HIGH); delay(300);  digitalWrite(34,LOW);
  digitalWrite(35, HIGH); delay(300);  digitalWrite(35,LOW);
  
  digitalWrite(32, HIGH); delay(300);  digitalWrite(32,LOW);
  digitalWrite(33, HIGH); delay(300);  digitalWrite(33,LOW);

  digitalWrite(30, HIGH); delay(300);  digitalWrite(30,LOW);
  digitalWrite(31, HIGH); delay(300);  digitalWrite(31,LOW);

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
