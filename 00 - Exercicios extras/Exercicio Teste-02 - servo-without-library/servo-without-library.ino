/*
   Aula 67 - Funções para Controle de Servo Motor sem utilização da biblioteca servo.h
    
   Autor: Eng. Wagner Rambo  Data: Maio de 2016
*/
 
// --- Mapeamento de Hardware ---
#define servo1 9 //servo1 ligado no pino digital 33
 
 
// --- Protótipo das Funções Auxialiares ---
void servo0graus();
void servo90graus();
void servo180graus();
 
 
// --- Configurações Iniciais ---
void setup()
{
   pinMode(servo1, OUTPUT); //saída para o servo1
} //end setup
 
// --- Loop Infinito ---
void loop()
{
  for(char i=0;i<100;i++) servo0graus();    //move o servo para a posição 0º por 2 segundos
   
 for(char i=0;i<100;i++) servo90graus();    //move o servo para a posição 90º por 2 segundos
 
  for(char i=0;i<100;i++) servo180graus();    //move o servo para a posição 180º por 2 segundos
   
  //for(char i=0;i<100;i++) servo90graus();    //move o servo para a posição 90º por 2 segundos
} //end loop
 
// --- Desenvolvimento das Funções Auxialiares ---
 
void servo0graus()              //Posiciona o servo em 0 graus
{
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(600);      //0.6ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<32;i++)delayMicroseconds(600);
                               // 20ms = 20000us
                               // 20000us - 600us = 19400us
                               // 19400/600 = ~~32
} //end servo0graus
 
void servo90graus()             //Posiciona o servo em 90 graus
{
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(2000);     //1.5ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<12;i++)delayMicroseconds(2000);
                               // 20ms = 20000us
                               // 20000us - 1500us = 18500us
                               // 18500/1500 = ~~12 
} //end servo0graus
 
void servo180graus()             //Posiciona o servo em 180 graus
{
   digitalWrite(servo1, HIGH);  //pulso do servo
   delayMicroseconds(2400);     //2.4ms
   digitalWrite(servo1, LOW);   //completa periodo do servo
   for(int i=0;i<7;i++)delayMicroseconds(2400);
                               // 20ms = 20000us
                               // 20000us - 2400us = 17600us
                               // 17600/2400 = ~~7
} //end servo0graus
