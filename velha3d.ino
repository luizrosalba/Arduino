///     Jogo da Velha 3D 
///     Luiz Fernando Rosalba Sousa -  Nova Friburgo 
///     IV SIimpósio Nacional da Formação do Professor de MAtemática

//// Teclado Membrana
#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <Avr/Power.H>
#endif

// porta de cada painel
#define PINN1 13
#define PINN2 12
#define PINN3 A5
#define PINN4 7

//Parametros: Numero De Leds, Pino De Ligacao
Adafruit_NeoPixel Strip1=Adafruit_NeoPixel(16,PINN1,NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip2=Adafruit_NeoPixel(16,PINN2,NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip3=Adafruit_NeoPixel(16,PINN3,NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel Strip4=Adafruit_NeoPixel(16,PINN4,NEO_GRB + NEO_KHZ800);



const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte PinosqtdLinhas[qtdLinhas] = {3, 4, 5, 6}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {8, 9, 10,11}; //PINOS UTILIZADOS PELAS COLUNAS

////////////////////////////////
//CONSTRUÇÃO DA MATRIZ DE ON/OFF para validacao da jogada 
///////////////////////////////// 
    
    
    int Validacao[65];

    
//INICIALIZAÇÃO DO TECLADO
Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);    
  
////////////////////////////////
/// Variaveis globais do programa 
/////////////
int vez=0;           ///    de quem eh a vez 
int coordenada=0;
char x='0',
     y='0',
     z='0';
char tcant='0';

char tp ;            /// tecla pressionada 
int jogada =0 ; 

void setup()
{
  
  Serial.begin(9600); //INICIALIZA A SERIAL
 
  Strip1.begin();
  Strip1.show();

  Strip2.begin();
  Strip2.show();

  Strip3.begin();
  Strip3.show();
  
  Strip4.begin();
  Strip4.show();

    //// Inicializacao dos Pinos 
     // for (int i = 2 ; i < 14 ; i++ )
     //   pinMode(i, OUTPUT);    /// 23 vermelho 
    ////  

   /// Inicializacao Jogo 
   Reinicia(); 

    
    /// TODO: acender um led para indicar de quem eh a jogada 
    /// 
    ////
    Strip1.setBrightness(20);
    Strip2.setBrightness(20);
    Strip3.setBrightness(20);
    Strip4.setBrightness(20);
    ApagaTudo();
}

 
void loop()
{

    //PiscaLinha(33,34,35,36,0);
    //PiscaLinha(49,50,51,52,0);
    
    char tecla_pressionada = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA
    
    
    /// Imprime de quem eh a vez 
    //  if (Vez(jogada) == 0)
    //    Serial.println("Jogada Vermelho");
    //  else 
    //    Serial.println("Jogada Azul");
    
       if (tecla_pressionada)
        {
          tcant=tecla_pressionada; 
          
          if (tecla_pressionada=='*' && tcant=='*') {coordenada=4; Reinicia(); }
          if (coordenada==2) {z = tecla_pressionada; coordenada++; ImprimeJogada();} /// coordenada z 
          if (coordenada==1) {y = tecla_pressionada; coordenada++;} /// coordenada y 
          if (coordenada==0) {x = tecla_pressionada; coordenada++;} /// coordenada x 
          
        }
        
        if (coordenada==3) /// terminou de dar as coordenadas da jogada Verificar validade da jogadas
          {
            
              if (Verifica_Jogada_Valida(x,y,z)==true) /// se a jogada eh valida 
              {
                
                int n=ACtoI(x,y,z); 
                /// marca a matriz com a cor do jogador 
                Validacao[n]=Vez(jogada); 
                /// acende o led na cor do jogador 
                AcendeLed(n,Vez(jogada));
                /// passa a jogada 
                jogada++;
                
                
              }else {
              Serial.println("Jogada Inválida Repita sua Jogada ");
              /// pisca led com cor falso (fazer) 
              
              /// nao passa jogada 
                
              }
              coordenada=0; /// pede a proxima jogada     
          }

          if (coordenada==4)
          {
            coordenada=0;  
          }
   
    int venc=VerificaVencedor();
    
    if (venc!=2) 
    {
      Serial.println("Vencedor"); 
      Serial.println(venc);  
      Reinicia();
    }  // verificar se o cubo esta todo aceso sem vencedor 
    

    
    //
    

    
    


  // TestaLed();

   
   delay(10);
}

void ImprimeJogada()
{
  Serial.print("Jogada: ");  Serial.print(x); Serial.print(" ");  Serial.print(y);  Serial.print(" ");  Serial.print(z); Serial.println();
  
  }

void AcendeLed(int n, int vez)
{

 int fita = ((n-1)/16)+1; /// diz qual andar 
 //Serial.println("fita ");
 //Serial.println(fita); 
 



  if (fita==1)
  {
   int pos = n ; 
   if (vez==0)  Strip1.setPixelColor(Pos_painel_led(pos)-1, Strip1.Color(100, 0, 0));
   else Strip1.setPixelColor(Pos_painel_led(pos)-1, Strip1.Color(0, 0, 100));
   
   Strip1.show();
  }

  if (fita==2)
  {
   int pos = n-16 ;
   if (vez==0)  Strip2.setPixelColor(Pos_painel_led(pos)-1, Strip2.Color(100, 0, 0));
   else Strip2.setPixelColor(Pos_painel_led(pos)-1, Strip2.Color(0, 0, 100));
   Strip2.show();
  }
   
  if (fita==3)
  {
   int pos = n-32;
   if (vez==0)  Strip3.setPixelColor(Pos_painel_led(pos)-1, Strip3.Color(100, 0, 0));
   else Strip3.setPixelColor(Pos_painel_led(pos)-1, Strip3.Color(0, 0, 100));
   Strip3.show();
  }
  
  if (fita==4)
  {
   int pos = n-48;
   if (vez==0)  Strip4.setPixelColor(Pos_painel_led(pos)-1, Strip4.Color(100, 0, 0));
   else Strip4.setPixelColor(Pos_painel_led(pos)-1, Strip4.Color(0, 0, 100));
   Strip4.show();
  }

  if (fita<1 || fita >4)
  {
    Serial.print(" Erro de fita");   
  }
  //Serial.print("n "); 
  //Serial.println(n); 
}


void ApagaLed(int n)
{

 int fita = ((n-1)/16)+1; /// diz qual andar 
 //Serial.println("fita ");
 //Serial.println(fita); 
 
  if (fita==1)
  {
   int pos = n ; 
   Strip1.setPixelColor(Pos_painel_led(pos)-1, Strip1.Color(0, 0, 0));
    
   Strip1.show();
  }

  if (fita==2)
  {
   int pos = n-16 ;
   Strip2.setPixelColor(Pos_painel_led(pos)-1, Strip2.Color(0, 0, 0));
   Strip2.show();
  }
   
  if (fita==3)
  {
   int pos = n-32;
   Strip3.setPixelColor(Pos_painel_led(pos)-1, Strip3.Color(0, 0, 0));
   
   Strip3.show();
  }
  
  if (fita==4)
  {
   int pos = n-48;
   Strip4.setPixelColor(Pos_painel_led(pos)-1, Strip4.Color(0, 0, 0));
  
   Strip4.show();
  }

  if (fita<1 || fita >4)
  {
    Serial.print(" Erro de fita");   
  }
  //Serial.print("n "); 
  //Serial.println(n); 
}

void ApagaTudo()
{
   for (int I = 0; I < Strip1.numPixels(); I++) 
   {
      Strip1.setPixelColor(I, Strip1.Color(0, 0, 0));
      Strip1.show();
   }

   for (int I = 0; I < Strip2.numPixels(); I++) 
   {
      Strip2.setPixelColor(I, Strip2.Color(0, 0, 0));
      Strip2.show();
   }

   for (int I = 0; I < Strip3.numPixels(); I++) 
   {
      Strip3.setPixelColor(I, Strip3.Color(0, 0, 0));
      Strip3.show();
   }

   for (int I = 0; I < Strip4.numPixels(); I++) 
   {
      Strip4.setPixelColor(I, Strip4.Color(0, 0, 0));
      Strip4.show();
   }
   
}

int Pos_painel_led (int ent) // retorna a indexação do painel de led 
{

if (ent ==1)return 4;
if (ent ==2)return 3;
if (ent ==3)return 2;
if (ent ==4)return 1;

if (ent ==9)return 12;
if (ent ==10)return 11;
if (ent ==11)return 10;
if (ent ==12)return 9;

return ent; 
 
}
 void TestaLed()
 {
   
  for (int I = 1; I <= Strip1.numPixels(); I++) 
   {
           
      Strip1.setPixelColor(Pos_painel_led(I)-1, Strip1.Color(200, 0, 0)); /// vermelho
      Strip1.show();
      delay(100);
   }


   for (int I = 1; I <= Strip2.numPixels(); I++) 
   {
      Strip2.setPixelColor(Pos_painel_led(I)-1, Strip2.Color(0,200,0)); /// verde
      Strip2.show();
       delay(100);
   }

   for (int I = 1; I <= Strip3.numPixels(); I++) 
   {
      Strip3.setPixelColor(Pos_painel_led(I)-1, Strip3.Color(0,0,200)); /// azul 
      Strip3.show();
       delay(100);
   }

    for (int I = 1; I <= Strip4.numPixels(); I++) 
   {
      Strip4.setPixelColor(Pos_painel_led(I)-1, Strip4.Color(200, 200, 150)); /// branco
      Strip4.show();
       delay(100);
   }
  
 }

int ACtoI (char ix , char iy , char iz)
{

int xi= (ix)-'0';
int yi= (iy)-'0';
int zi= (iz)-'0';

int n =((xi-1)*4 + yi +(zi-1)*4*4);
return (n);
}


int AItoI (int xi , int yi , int zi)
{
int n =((xi-1)*4 + yi +(zi-1)*4*4);
return (n);
}



bool Verifica_Jogada_Valida( char ix , char iy , char iz)
{
    int xi= (ix)-'0';
    int yi= (iy)-'0';
    int zi= (iz)-'0';
    int n = AItoI(xi,yi,zi);
   /// Serial.print(n);
    
    if (n>64 || n<1) {Serial.println("Jogada Fora do Intervalo do Cubo");return false; }
    
    if (xi>4 || yi>4 || zi>4)  {Serial.println("Coordenadas Devem ser menores que 4");return false; }
    if (xi<1 || yi<1 || zi<1)  {Serial.println("Coordenadas não podem ser menores que 1");return false; }

    /// verificar letras 
    
    if (Validacao[n]==3) return true; /// vazio 
    if (Validacao[n]==0) {Serial.println("Vermelho já jogou nessa posicao");return false; } /// vermelho
    if (Validacao[n]==1) {Serial.println("Azul já jogou nessa posicao");return false; }   /// azul 

    return false; 
    
  
}

//// Retorna 0 se vez do vermelhro 
//// Retorna 1 se vez do azul 
int Vez(int ent)
{
  if ((ent%2)==0) 
    return 0; /// vermelho
  else 
    return 1;  /// azul 
    
 }

  //////////////////////////////
  /// loop da selecao de teclas 
  /////////////////////////////
  void Reinicia()
{
   vez=0; /// vermelhos reiniciam 
   jogada=0; /// vermelhos jogam 
   coordenada=0;
   tcant='0';
 /// Inicializacao vetor  validacao 
    for (int i=0;i<=64;i++)
    {
       Validacao[i]= 3 ; /// 3 = posicao nao jogada 
                         /// 0 = jogada vermelho
                         /// 1 = jogada azul
    }                      

  
    ApagaTudo();
  
}


void ItoA(int pos,int &saida_fita, int &saida_M)
{
  if (pos>=1 && pos <=16)
  {
    saida_fita =1 ; 
    saida_M= pos;  
  }

  if (pos>=17 && pos <=32)
  {
    saida_fita =2 ; 
    saida_M= (pos-16);  
  }
  if (pos>=33 && pos <=48)
  {
    saida_fita =3 ; 
    saida_M= (pos-32);  
  }
  if (pos>=49 && pos <=64)
  {
    saida_fita =4 ; 
    saida_M= (pos-48);  
  }
  
}

void PiscaLinha (int pos1 , int pos2 ,int pos3 ,int pos4 , int venc)
{

    int tempopisca=500;
    /*
     Serial.println(pos1);
      Serial.println(pos2);
      Serial.println(pos3);
      Serial.println(pos4);
      Serial.println(" ");
*/
      
for (int i=1;i<=5;i++)// numero de piscadas 
  {

   
      ApagaLed(pos1);
      ApagaLed(pos2);
      ApagaLed(pos3);
      ApagaLed(pos4);
      delay(tempopisca);
      AcendeLed(pos1,venc);
      AcendeLed(pos2,venc);
      AcendeLed(pos3,venc);
      AcendeLed(pos4,venc);
      delay(tempopisca);
     
      
  }
  
  
  
  
} 
/// 0 = vencedor vermelhor 
/// 1 = vencedor azul 
/// 2 = nenhum vencedor 

int  VerificaVencedor()
{
      int a, bb,c,d;
      /// linhas   
      for (int i=1; i<=61 ; i=i+4) /// cada linha 
      {
          a=i; bb=i+1;c=i+2;d=i+3;
          
          if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
          if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      }
      /// coluna 
       for (int i=1; i<=52 ; i=i+1) /// cada linha 
      {
          if (i==5) i=17; /// confere 1,2 ,3 ,4 pula do 5 para 17 
          if (i==21) i=33; ///confere 17,18,19,20 pula do 21 para 31 
          if (i==37) i=49; ///confere 33,34,35,36 pula do 37 para 0 49
                            /// confere 49,50,51,52 e finaliza no 53

          a=i; bb=i+4;c=i+8;d=i+12;       
                
          if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
          if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      }
      /// verticais  
      for (int i=1; i<16 ; i=i+1) /// cada coluna vertical 
      {
           a=i; bb=i+16;c=i+32;d=i+48;     
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      //////Cruz no eixo decrescente 
      for (int i=1; i<=49 ; i=i+16) /// cada andar tem duas cruz 
      {
           a=i; bb=i+5;c=i+10;d=i+15;     
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      for (int i=4; i<=52 ; i=i+16) /// cada andar tem duas cruz 
      {
           a=i; bb=i+3;c=i+6;d=i+9;     
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      
      // diagonais só as bordas podem. Os cantos podem diagonal , e duas laterais  
      
      for (int i=1; i<=4 ; i++) ////// diagonal paralela ao eixo y cima 
      {
            a=i; bb=i+20;c=i+40;d=i+60; 
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
       } 
      
      /// diagonal paralela ao eixo y baixo 
       for (int i=13; i<=16 ; i++) ////// diagonal paralela ao eixo y Baixo 
      {
            a=i; bb=i+12;c=i+24;d=i+36; 
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      
      /// diagonal paralela ao eixo x esquerda 
       for (int i=1; i<=13 ; i=i+4) ////// diagonal paralela ao eixo x esquerda 
      {
            a=i; bb=i+17;c=i+34;d=i+51; 
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      
      /// diagonal paralela ao eixo x direita
      
      for (int i=4; i<=16 ; i=i+4) ////// diagonal paralela ao eixo x direita 
      {
           a=i; bb=i+15;c=i+30;d=i+45; 
           if (Validacao[a]==0 && Validacao[bb]==0 && Validacao[c]==0 && Validacao[d]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
           if (Validacao[a]==1 && Validacao[bb]==1 && Validacao[c]==1 && Validacao[d]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      } 
      
      
      /// diagonal principal
       a=1; bb=22;c=43;d=64; 
       if (Validacao[1]==0 && Validacao[22]==0 && Validacao[43]==0 && Validacao[64]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
       if (Validacao[1]==1 && Validacao[22]==1 && Validacao[43]==1 && Validacao[64]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
       a=4; bb=23;c=42;d=61; 
       if (Validacao[4]==0 && Validacao[23]==0 && Validacao[42]==0 && Validacao[61]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
       if (Validacao[4]==1 && Validacao[23]==1 && Validacao[42]==1 && Validacao[61]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
        a=16; bb=27;c=38;d=49; 
       if (Validacao[16]==0 && Validacao[27]==0 && Validacao[38]==0 && Validacao[49]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
       if (Validacao[16]==1 && Validacao[27]==1 && Validacao[38]==1 && Validacao[49]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 
      a=13; bb=26;c=39;d=52; 
      if (Validacao[13]==0 && Validacao[26]==0 && Validacao[39]==0 && Validacao[52]==0 ) { PiscaLinha(a,bb,c,d,0); return 0;} 
      if (Validacao[13]==1 && Validacao[26]==1 && Validacao[39]==1 && Validacao[52]==1 ) { PiscaLinha(a,bb,c,d,1); return 1;} 


      


      
return 2; /// nenhum vencedor 
    
}





void desliga (int pos , uint32_t cor)
{
  Strip1.setPixelColor(pos, Strip1.Color(0, 0, 0));
  Strip1.show();
}
