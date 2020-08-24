void setup() {
  // put your setup code here, to run once:
for (int i = 1 ; i < 54 ; i++)
{
   pinMode(i, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
  
}

 pinMode(A7, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
 pinMode(A9, OUTPUT); //Declara que o pino 11 do arduino é de Saída. Vai mandar dados, energia...
}

void loop() {
  // put your main code here, to run repeatedly:

    
  //Pisca_Led(1); /// 
  //digitalWrite(1,HIGH); delay(300);digitalWrite(1, LOW); 
  //digitalWrite(2,HIGH); delay(300); digitalWrite(2,LOW); 
  //digitalWrite(3,HIGH); delay(300); digitalWrite(3,LOW); 
  //digitalWrite(4,HIGH); delay(300);digitalWrite(4,LOW); 
  for (int i = 1 ; i < 54 ; i++)
{
  if (i%2!=0){ 
     digitalWrite(i,LOW);   
    if (i==7) digitalWrite(A7,LOW);   
    if (i==9) digitalWrite(A9,LOW);   
    //if (i==6) digitalWrite(A8,LOW);   
  }
 else {
   digitalWrite(i,HIGH);  
   if (i==7) digitalWrite(A7,HIGH);   
   if (i==9) digitalWrite(A9,HIGH);   
   //if (i==6) digitalWrite(A8,HIGH);   
 
  }
}
  
  
  
  
      
/*
for (int i = 1 ; i < 3 ; i++)
{

  //if (i%2!=0)
  {
      if (i==7){
         digitalWrite(A7, HIGH); //delay(50);  digitalWrite(A7,LOW); 
       }
       else {digitalWrite(i, HIGH) ; delay(400);  digitalWrite(i,LOW);
       }
  }
}

*/

 //delay(500);  digitalWrite(A7,LOW); 
  //delay(500);  digitalWrite(i,LOW);

  delay(1);
}



void Pisca_Led(int led )
{
      digitalWrite(led, HIGH); delay(500);  digitalWrite(led,LOW); 
}
